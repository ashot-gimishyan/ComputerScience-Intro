#include <iostream>
#include <cstdlib>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#define TLimit 315360000
using namespace std;

class CTime{
time_t ctm;
int  nanos;
public:
   CTime();
   CTime( const CTime&);

// для cамостоятельного программирования
// для определения длительности процесса
       void start();
       void stop();

   void getTime(const char*);
   void getTime(time_t,int);
   int operator==(const CTime&);

// для самостоятельного программирования
        int operator>(CTime);
        int operator<(CTime);

   CTime operator+(const CTime&);

// для cамостоятельного программирования
       CTime operator-(const CTime&);
       CTime operator*(float);
       float operator/(const CTime&);
   void print();
};

// Добавили описание класса DataTime
class DataTime{
// структура для времени (системная)
  struct tm tmdat;
// секунды с 1970 г.
  time_t ctm;
//наносекунды
  int  nanos;
public:
// конструктор
   DataTime();
// инициализирующий конструктор
   DataTime(time_t, int);
   DataTime(char *);

// получить дату из строки
   void getData(char*);

// получить текущую дату с заполнением структуры
   void now();

// сравнение двух дат
   int operator==(const DataTime&);


// сложение даты с CTime
   DataTime operator+(const CTime&);

// для cамостоятельного программирования
//вычитание CTime
   DataTime operator-(const CTime&);

// для cамостоятельного программирования
// получить разницу времен
   CTime operator-(const DataTime&);
// печать
   void print();

// для cамостоятельного программирования
// печать с указанием дня недели
// как принято в России
   void print(int);

};
