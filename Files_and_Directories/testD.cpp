// Отладка написанных функции
// Проверка работы программы

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <errno.h>
#include "sysdir.h"

int main(int argc, char** argv)
{
  Catalog ctlg;
  int res = ctlg.dopen(argv[1]);
  if (res == 0)
    printf("%s\n", "Отлично, каталог открылся!");

  //ctlg.getNumbers();
  ctlg.list();
  // ctlg.catF(argv[2]);
  //ctlg.delF(argv[2]);
  // ctlg.getMode();

  /*
  int ex_res = ctlg.isExFile(argv[1]);
  if (ex_res == 1)
    printf("%s\n", "Файл существует");
  else
    printf("%s\n", "Файл не найден");
*/

  if (ctlg.dclose())
    printf("%s\n", "Каталог успешно закрыт!");

  return 0;
}
