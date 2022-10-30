// Прототипы функции для работы с каталогами

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <iostream>
#include <cstdlib>
#include <grp.h>

using namespace std;
class Catalog{
// указатель на системную файловую
// структуру для записей в каталоге (список файлов)
   struct dirent* dirrec;
// дескриптор каталога
   DIR * dir;
   unsigned int numbersf;
// массив имен файлов
   string names[100];
public:
// конструкторы
   Catalog();
   Catalog(char *);
// деструктор
   ~Catalog();
// открыть каталог
   unsigned char dopen(char*);
// получить имя файла из списка (по номеру)
   string getFile(int);
// проверить есть ли файл в каталоге
   int isExFile(char*);
// получить атрибуты доступа к файлу, если он есть
// -1, если файла не, остальное как в mod_t
   int getMode();
// печать содержимого файла, если он есть
// 0 - OK, 1 - нет доступа, -1 нет файла
   int catF(char *);
// удалить файл
   int delF(char*);
// закрыть каталог
   bool dclose();
// получить количество файлов.
   int getNumbers();
// Напечать список файлов с указание их атрибутов, размера и владельца,
//  а также времени создания
   void list();
};
