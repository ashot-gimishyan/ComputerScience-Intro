#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <stdlib.h>
#include <sys/msg.h>
#include "mes.h"
#include <string.h>

int main(){
// сообщение
  Message privet;
  Message primi;
// ключ для создания системного ресурса
  key_t key;
// дескриптор очереди сообщений
  int mesid;
  int compare;
  int len;

  int lng,n;
// получение ключа
// нужно имя заведомо существующего файла
// и символ
  if ((key = ftok( "server", 'A' ) ) < 0 ){
     printf("Can't get key\n");
     exit(1);
  }
// для записи сообщения, его тип
//указывается в структуре
// будем читать и писать тип 1
  privet.type=1L;

// создание очереди сообщений
  if( ( mesid = msgget(key, PERM|IPC_CREAT ) ) < 0 ){
    printf("Can't create message's queue\n");
    exit(1);
  }

while(1)
{
// чтение из очереди сообщений
// если сообщений в очереди нет, программа в ожидании
// сообщение должен послать клиент
    while (msgrcv(mesid, &privet, sizeof(privet.buf), 0, 0) != -1) {

    //    if (msgrcv(mesid, &privet, sizeof(privet.buf), 0, 0) == -1) {
     //       perror("msgrcv");
     //       exit(1);
     //   }

      //  compare = strcmp(privet.buf, "end");
     //   if (compare == 0)
      //      continue;

        printf("\"%s\"\n", privet.buf);
    }
    
    
  // отсылаем сообщение
   // while (fgets(primi.buf, MAXBUF, stdin) != NULL) {
      //  len = strlen(primi.buf);
        /* признак конца строки удаляем */
    //    if (primi.buf[len - 1] == '\n')
    //        primi.buf[len - 1] = '\0';
     //   if (msgsnd(mesid, &primi, len + 1, 0) == -1) /* +1 для '\0' */
     //       perror("msgsnd");
    }
    return 0;
}
