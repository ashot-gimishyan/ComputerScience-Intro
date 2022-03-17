// Задача 1
// для типа Time реализовать функцию
// вычитание t1 из t2
// Time sub(Time t1, Time t2);
// Ashot Gimishyan | MIPT

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int h, min, sec;
} Time;

Time Time_sub(Time t1, Time t2);

int main()
{

    Time t1, t2;
    t1.h = 7;
    t1.min = 50;
    t1.sec = 50;

    t2.h = 10;
    t2.min = 50;
    t2.sec = 40;

    Time diff;
    diff = Time_sub(t1, t2);
    printf("%.02d:%.02d:%.02d\n", diff.h, diff.min, diff.sec);
    return 0;
}

Time Time_sub(Time t1, Time t2)
{
    int sec_t1 = t1.h * 3600 + t1.min * 60 + t1.sec;
    int sec_t2 = t2.h * 3600 + t2.min * 60 + t2.sec;

    int tmp = abs(sec_t2 - sec_t1);

    Time cur_time;
    cur_time.h = tmp / 3600;
    cur_time.min = (tmp % 3600) / 60;
    cur_time.sec = tmp % 60;

    return cur_time;
}

