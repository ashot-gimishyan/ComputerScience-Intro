// Прототипы функции
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
#include <malloc.h>
#include <iostream>
#include <cstdlib>
#include <sys/sendfile.h>

using namespace std;

class SystemFile {
    // системная структура для информации о пользователе
    struct passwd* result;
    // системная структура для информации о файле
    struct stat sb;
    // файловый дескрипор
    int id;
    // для прав доступа к файлу
    char mod;

public:
    // Конструктор. Вызывается всегда при создании объекта
    SystemFile();
    // Деструктор вызывается всегда, когда должен быть
    // удален объект: при завершении функции, в которой он локальный
    // или при вызове delete
    ~SystemFile();
    // закрытие файла
    bool closef();
    // открытие файла по его имени в каталоге
    unsigned char openf(char*);
    // получить имя владельца файла
    string getUser();
    // получить атрибуты доступа файла
    mode_t getMode();
    // получить имя владельца файла (в байтах)
    long getSize();
    // запись в файл. Передается уаказатель
    // на память для записи и размер (в байтах)
    bool writef(void*, long);

    // Чтение из файла. В память по указателю
    // указаного размера. Память предварительно
    // должна быть ВЫДЕЛЕНА
    bool readf(char*, long);

    // печать общей информации о файле
    void about();

    // получить количество записей в файле,
    // если известен размер записи
    long numbersOfRecord(char*, long);

    // найти f1 и заменить запись на f2 (полное соответствие)
    // только для бинарного файла
    void replace(void* f1, void* f2, size_t sizeRec);

    // найти f1 и удалить (полное соответствие)
    // только для бинарного файла
    // для удаления использовать функцию truncate
    // или ftruncate
    void deletef(char* f1);

    // Копировать текущий файл в файл с именем name
    // Если файла name нет, то мы его создаем (O_CREATE|O_EXCL|O_WRONLY)
    // При ошибки существования файла, просто открываем его с флагами:
    // O_TRANC|O_WRONLY

    void copy(char*, char*);
};
