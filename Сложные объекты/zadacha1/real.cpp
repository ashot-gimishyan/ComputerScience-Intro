#include <string.h>
#include <iostream>
#include "long.h"

/*
 Конструктор по умолчанию.
 Будем считать, что по-умолчанию, число - 0
*/
Arithmetic::Arithmetic()
{
    n = 1;
    _is_negative = false;
    
    // Динамически выделяем память под один элемент.
    digit = new unsigned char[1];
    digit[0] = 0;
    cout << "Constructor\n";
    
};

/*

 Инициализирующий конструктор.
 число задается строкой цифр.
*/
Arithmetic::Arithmetic(const char* s)
{
    
    if (s[0] == '-') {
        _is_negative = true;
        s++;
    }
    else {
        _is_negative = false;
        //  cout << _is_negative << "iss: ";
    }
    int i;
    int len = strlen(s);
    n = (len % 2) ? (len >> 1) + 1 : len >> 1;
    //  cout << "n: " << n << endl;

    // delete[] digit;
    // Выделение памяти под массив
    digit = new unsigned char[n];
    len--;

    // Число записывает "задом-наперед" для вычислений
    for (i = 0; i < n; i++) {
        digit[i] = s[len--] - '0';
        if (len < 0)
            break;
        digit[i] += (s[len--] - '0') * 10;
        
    }
    
};

void Arithmetic::print()
{
    
    int i;
    //  cout<<(*this)._is_negative <<endl;

    if (_is_negative && (int)digit[0] != 0)
        cout << "-";

    for (i = n - 1; i >= 0; i--) {
        cout << (int)digit[i];
    }
    cout << endl;
    
};

/*
  Копирующий конструктор.
При создании объекта можно использовать данные
другого объекта.

Тогда необходимо выделить соответствующую память
и скопировать  данные.
*/
Arithmetic::Arithmetic(const Arithmetic& a)
{
    
    digit = new unsigned char[a.n];
    n = a.n;
    _is_negative = a._is_negative;
    // скопировать: куда откуда сколько
    memcpy(digit, a.digit, sizeof(unsigned char) * n);
    
};

/*
 Деструктор. Во время работы деструктора будут выполняться
инструкции, написанные в нем. То есть освободится динамическая
память, на которую указывает digit.

Деструктор вызыватся: при вызове delete, при завершении функции,
в которой этот объект используется как локальный, при вызове
деструктора объекта, в котором содержится этот объект.
*/
Arithmetic::~Arithmetic()
{
   delete[] digit;
   // delete[] digit;
};

/*
 Перегрузка оператора копирования.

Здесь нужно учесть, что у объекта уже выделена память
под хранение числа. Поэтому ее необходимо освободить
и выделить новую, соответствующего размера
*/
Arithmetic& Arithmetic::operator=(const Arithmetic& a)
{
    
    delete[] digit;
    digit = new unsigned char[a.n];
    n = a.n;
    (*this)._is_negative = a._is_negative;
    cout << "размер: " << sizeof(unsigned char) * n << endl;
    memcpy(digit, a.digit, sizeof(unsigned char) * n);
    return *this;
};

/*
 Присваивание объекта "несоответствующего" типа.
*/
Arithmetic& Arithmetic::operator=(int a)
{
    delete[] digit;
    if (a < 0)
        (*this)._is_negative = true;
    else
        (*this)._is_negative = false;

    // преобразуем число в строку
    string str = to_string(a);
    int i;
    int len = strlen(str.c_str());
    n = (len % 2) ? (len >> 1) + 1 : len >> 1;
    cout << "n: " << n << endl;

    // Выделение памяти под массив
    digit = new unsigned char[n];
    len--;

    // Число записывает "задом-наперед" для вычислений
    for (i = 0; i < n; i++) {
        digit[i] = str[len--] - '0';
        if (len < 0)
            break;
        digit[i] += (str[len--] - '0') * 10;
    }

    return *this;
};

Arithmetic::Arithmetic(int numb)
{
    if (numb < 0)
        _is_negative = true;
    else
        _is_negative = false;

    cout << "Constructor!!!" << endl;
    string str = to_string(numb);
    int i;
    int len = strlen(str.c_str());
    n = (len % 2) ? (len >> 1) + 1 : len >> 1;
    cout << "n: " << n << endl;

    // Выделение памяти под массив
    digit = new unsigned char[n];
    len--;

    // Число записывает "задом-наперед" для вычислений
    for (i = 0; i < n; i++) {
        digit[i] = str[len--] - '0';
        if (len < 0)
            break;
        digit[i] += (str[len--] - '0') * 10;
    }
};

// сложение чисел
Arithmetic Arithmetic::operator+(const Arithmetic& arit)
{
    
    //cout << arit._is_negative;
    if (arit._is_negative && !((*this)._is_negative)) {
        return (*this).operator-(arit);
    }

    if (!arit._is_negative && ((*this)._is_negative)) {
        return (*this).operator-(arit);
    }

    int flag = 0; // флаг переноса из предыдущего разряда
    Arithmetic max_n = (*this).n < (arit.n) ? arit : (*this);
    Arithmetic min_n = (*this).n < (arit.n) ? (*this) : arit;
    for (size_t i = 0; i < max(max_n.n, min_n.n) || flag != 0; ++i) {
        max_n.digit[i] += flag + (i < min_n.n ? min_n.digit[i] : 0);
        //  cout << (*this).digit[i];
        flag = max_n.digit[i] >= 100;
        if (flag != 0) {
            max_n.digit[i] -= 100;
        }
        //  digit = new unsigned char[1];
    }

    if (arit._is_negative && ((*this)._is_negative)) {
        cout << "-";
    }
    return max_n;
};

// вычитание
Arithmetic Arithmetic::operator-(const Arithmetic& arit)
{

    int flag = 0; // перенос из предыдущего разряда

    //cout << arit._is_negative;
    Arithmetic max_n;
    Arithmetic min_n;

    if ((*this).n > (arit.n)) {
        max_n = (*this);
        min_n = arit;
    }
    else {
        max_n = arit; // условно
        min_n = (*this);
    }

    Arithmetic tmp;
    if (max_n.n == min_n.n) // продолжение else
    {
        if ((int)max_n.digit[max_n.n - 1] < (int)min_n.digit[min_n.n - 1]) {
            tmp = max_n;
            max_n = min_n;
            min_n = tmp;
        }
    }

    for (size_t i = 0; i < max(max_n.n, min_n.n) || flag != 0; ++i) {
        max_n.digit[i] -= flag + (i < min_n.n ? min_n.digit[i] : 0);
        //  cout << (*this).digit[i];
        flag = max_n.digit[i] >= 100;
        if (flag != 0) {
            max_n.digit[i] -= 100;
        }
        //  digit = new unsigned char[1];
    }
	
   // delete[] digit;
    return max_n;
};

Arithmetic& Arithmetic::operator+=(const Arithmetic& val)
{
    return * this = (*this + val);
}

//префиксная версия сложения
Arithmetic Arithmetic::operator++()
{
    return (*this += 1);
};

// Сложение с числом.
Arithmetic Arithmetic::operator+(int plus)
{
    int i = 0;
    if (plus < 0) {
        this->_is_negative = true;
        plus = -plus;
    }
    else
        this->_is_negative = false;
    do {
        digit[i] += plus % 100;
        plus /= 100;
        i++;
    } while (plus != 0);
    return (*this);
};


const Arithmetic Arithmetic::operator+()
{
    return Arithmetic(*this);
};

const Arithmetic Arithmetic::operator-()
{
    //  cout << (*this)._is_negative;
    (*this)._is_negative = !(*this)._is_negative;
    //cout << (*this)._is_negative;
    return (*this);
};

Arithmetic& Arithmetic::operator-=(const Arithmetic& val)
{
    return * this = (*this - val);
}

//префиксная версия вычитания
Arithmetic Arithmetic::operator--()
{
    return (*this -= 1);
};

// Сложение с числом.
Arithmetic Arithmetic::operator-(int minus)
{
    int i = 0;
    if (minus < 0) {
        this->_is_negative = true;
        minus = -minus;
    }
    else
        this->_is_negative = false;
    do {
        digit[i] -= minus % 100;
        minus /= 100;
        i++;
    } while (minus != 0);
    return (*this);
};


Arithmetic Arithmetic::operator*(const Arithmetic& b)
{
    Arithmetic res;
    delete[] res.digit;
    res.n = (*this).n + b.n;
    
    res.digit = new unsigned char[res.n];

    if ((*this)._is_negative && !b._is_negative || !(*this)._is_negative && b._is_negative)
    {
      res._is_negative = true;
    }
    else{
      res._is_negative = false;
    }

    for (int i = 0; i < (*this).n; i++)
        for (int j = 0; j < b.n; j++) {
            res.digit[i + j] += ((int)(*this).digit[i] * (int)b.digit[j]) % 100;
            res.digit[i + j + 1] += ((int)(*this).digit[i] * (int)b.digit[j]) / 100;
        }
    for (int i = 0; i < res.n; i++) {
        res.digit[i + 1] += res.digit[i] / 100;
        res.digit[i] %= 100;
    }

    return res;
};

