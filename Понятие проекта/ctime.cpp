#include "timedat.h"
#include <stdlib.h>

// описание конструктора
CTime::CTime(){
  // инициализируем все атрибуты
  // для всех функции класса CTime
  // его атрибуты глобальные
  ctm = 0;
  nanos = 0;
};

// иногда нужно получить копия объекта
// вот для этого такой конструктор
CTime::CTime(const CTime& a){
  ctm = a.ctm;
  nanos = a.nanos;
};

// получение времени через строку
void CTime::getTime(const char* s){
  int day;
  int h;
  int min;
  int sec;

  sscanf(s, "%d:%d:%d:%d.%d", &day,&h,&min,&sec,&nanos);

  // nanos and ctm are global variables for all functions
  ctm = (((day * 24) + h) * 60 + min) * 60 + sec;
};

void CTime::print(){
  int day = ctm / 86400;
  int h = (ctm / 3600) % 24;
  int min  = (ctm /60) % 60;
  int sec = ctm % 60;
  printf("%d %d:%d:%d.%d ", day, h, min, sec, nanos);
};

  // реализация перегрузки операторов
  CTime CTime::operator+(const CTime& a){
    // объект, который будеи возвращен
    CTime tmp;

    // tmp и a - объекты класса CTime
    // функции этого класса имеют доступ
    // ко всем атрибутам и функциям CTime

    tmp.nanos = (nanos + a.nanos) % 1000;
    tmp.ctm = ctm + a.ctm + (nanos + a.nanos) / 1000;

    return tmp;
};

// реализация перегрузки операторов
CTime CTime::operator-(const CTime& a){
  // объект, который будеи возвращен
  CTime tmp;

  tmp.nanos = abs(nanos - a.nanos);
  tmp.ctm = abs(ctm - a.ctm) + (nanos - a.nanos) / 1000;

  return tmp;
};
