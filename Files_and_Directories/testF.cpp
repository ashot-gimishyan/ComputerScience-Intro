// Проверка работы программы
// включиить заголовочный файл
#include "sysfile.h"

int main(int argc, char** argv)
{
    /*
    // создается объект типа  SystemFile
    // работает коструктор
    SystemFile file1;
    // функция openf() возвращает значение errno,
    // полученное в процессе создания или открытия файла
    if (file1.openf(argv[1])) {
        perror("не открывается никак");
        exit(1);
    }

    //  печать информации о файле
    file1.about();
    // объект C++ string
    //  string s;
    // получить строку с консоли
    //  cin>>s;
    // c_str() - функция string возвращает указатель на
    // C-строку (массив символов с окончанием '\0'
    // length() - возвращает размер строки в символах
    //  file.writef((void*)s.c_str(),s.length()*sizeof(char));

    // напечатать имя владельца
    string owname = file1.getUser();
    cout << owname << endl;

    // права доступа
    mode_t prava = file1.getMode();
    cout << "Права доступа " << prava << endl;

    // get the size of this file
    long ssize = file1.getSize();
    cout << "Размер " << ssize << endl;
*/
    // третий аргумент
    // второй файл
    // только прочитать
    SystemFile file2;
    if (file2.openf(argv[1])) {
        perror("не открывается никак");
        exit(1);
    }

/*
    // количетсво записей файла
    file2.numbersOfRecord(argv[2], 1);

    // откуда = argv[1]
    // куда = argv[1]
    file2.copy(argv[1], argv[2]);

    */

    file2.deletef(argv[1]);
    // close files
    //file1.closef();
    //file2.closef();

    return 0;
}
