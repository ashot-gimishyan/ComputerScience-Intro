#include <iostream>
#include <cstdlib>

using namespace std;

class Arithmetic {
    unsigned char* digit; // для хранения числа
    int n; // размер числа
    // знак числа
    bool _is_negative;

public:
    Arithmetic(); // конструктор

    // инициализирущий конструктор
    // в строке содержатся только цифры.
    // Предполагается, что на строку символов до вызова
    // конструктора уже выделено достаточное количество памяти и
    // конец строки уже обозначен '\0'
    Arithmetic(const char*);
    /*
  Деструктор. Необходим, чтобы объект
  "умер достойно".
*/
    ~Arithmetic();
    // Копирующий конструктор
    Arithmetic(const Arithmetic&);
    Arithmetic& operator=(const Arithmetic&);
    // Оператор копирования
    Arithmetic& operator=(int n);
    void print();
    const Arithmetic operator-();
    const Arithmetic operator+();
    // Инициализирующий коструктор (числом)
    Arithmetic(int);
    Arithmetic operator+(const Arithmetic&);
    Arithmetic& operator+=(const Arithmetic&);
    Arithmetic& operator-=(const Arithmetic&);
    Arithmetic operator++(); // Инкремент префиксный
    Arithmetic operator--(); // Декремент префиксный
    Arithmetic operator+(int); // Сложение с числом.
    Arithmetic operator-(const Arithmetic&);
    Arithmetic operator-(int);

    Arithmetic operator*(const Arithmetic&);
};
