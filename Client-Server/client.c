#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include "mes.h"
#include <string.h>

int main()
{
    Message privet;
    Message primi;
    key_t key;
    int mesid;
    int len, n;
    int compare;

    if ((key = ftok("server", 'A')) < 0) {
        printf("Can't get key\n");
        exit(1);
    }

    // Очередь уже создана, получаем
    // дескриптор
    if ((mesid = msgget(key, PERM | IPC_CREAT)) == -1) {
        printf("Can't get message's queue\n");
        exit(1);
    }

    // Создаем сообщение для посылки
    privet.type = 1L;
    primi.type = 2L;
    
        // отсылаем сообщение (сервер его ждет)
        while (fgets(privet.buf, MAXBUF, stdin) != NULL) {
            len = strlen(privet.buf);
            /* признак конца строки удаляем */
            if (privet.buf[len - 1] == '\n')
                privet.buf[len - 1] = '\0';
            if (msgsnd(mesid, &privet, len + 1, 0) == -1) /* +1 для '\0' */
                perror("msgsnd");
        }

        // чтение из очереди сообщений
        // если сообщений в очереди нет, программа в ожидании
        // сообщение должен послать клиент
       // while (msgrcv(mesid, &primi, sizeof(primi.buf), 0, 0) != -1) {

          //  if (msgrcv(mesid, &primi, sizeof(primi.buf), 0, 0) == -1) {
            //    perror("msgrcv");
              //  exit(1);
           // }

           // compare = strcmp(primi.buf, "end");
           // if (compare == 0)
             //   continue;

         //   printf("\"%s\"\n", primi.buf);

    // Удалаем очередь сообщений когда не нужна
    // сервер может и не успеть прочитать сообщение
    
    if (msgctl(mesid, IPC_RMID, 0) < 0) {
        printf("Can't delete queue\n");
        exit(1);
        
    return 0;
}
}
