#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

#define PERMS 0666

struct my_msgbuf {
    long type;
    char text[200];
};

int main(int argc, char const* argv[])
{

    struct my_msgbuf buf;
    int msqid;
    key_t key;
    int compare;
    int i = 0;

    if ((key = ftok("msg_s.c", 'A')) == -1) {
        perror("ftok");
        exit(1);
    }

    if ((msqid = msgget(key, PERMS)) == -1) { /* connect to the queue */
        perror("msgget");
        exit(1);
    }
    printf("Начинаю прочитать сообщения...\n");

    while (1) {

        if (msgrcv(msqid, &buf, sizeof(buf.text), 0, 0) == -1) {
            perror("msgrcv");
            exit(1);
        }

        compare = strcmp(buf.text, "end");
        if (compare == 0)
            break;

        printf("Сообщение %i: "
               "\"%s\"\n",
            i, buf.text);
        i++;
    }

   if (msgctl(mesid, IPC_RMID, 0) < 0) {
        printf("Can't delete queue\n");
        exit(1);
        
    return 0;
}
