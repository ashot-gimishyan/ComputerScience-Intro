// принцип First in first out
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define PERMS 0666 // права
#define BUFSIZE 500

typedef struct my_msgbuf {
    long type;
    char text[BUFSIZE];
} mm_buf;


int main(int argc, char const* argv[])
{
    mm_buf buf; // buf типа mm_buf
    int msqid; // дескриптор
    int len; // длина текста
    key_t key; // key_t это int

    // man ftok
    // key_t ftok(const char *pathname, int proj_id);
    if ((key = ftok("msg_s.c", 'A')) == -1) {
        perror("ftok");
        exit(1);
    }

    // создаем очередь сообщений
    if ((msqid = msgget(key, PERMS | IPC_CREAT)) == -1) {
        perror("msgget");
        exit(1);
    }

    printf("Напишите Ваш текст, в конце добавьте end\nпосле чего нажмите ^C для завершения ввода:\n");
    buf.type = 1; // условно сообщение типа 1

    while (fgets(buf.text, BUFSIZE, stdin) != NULL) {
        len = strlen(buf.text);
        /* признак конца строки удаляем */
        if (buf.text[len - 1] == '\n')
            buf.text[len - 1] = '\0';
        if (msgsnd(msqid, &buf, len + 1, 0) == -1) /* +1 для '\0' */
            perror("msgsnd");
    }

    return 0;
}
