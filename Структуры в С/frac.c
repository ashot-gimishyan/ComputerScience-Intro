// Операции с дробями
// Ashot Gimishyan | MIPT

#include <stdio.h>
#include <stdlib.h>

// Описание структуры дробь
typedef struct Dr {
    char sign;    // знак дроби
    int int_part; // целая часть
    int num;      // числитель
    int denum;    // знаменатель
} Drob;


void inputDrob(Drob* a);
void printDrob(Drob a);

Drob sum(Drob a, Drob b);
Drob diff(Drob a, Drob b);
Drob mult(Drob a, Drob b);
Drob division(Drob a, Drob b);
void printAsDecimal(Drob a);


int main()
{
    Drob a;
    inputDrob(&a);
    printDrob(a);
}

void inputDrob(Drob* a)
{
    char x, y, z; // ловить мусор ( / )
    scanf("%c %d %c %d %c %d %c", &(a->sign), &(a->int_part), &x, &(a->num), &y, &(a->denum), &z);
}

void printDrob(Drob a)
{
    printf("%c%d(%d/%d)\n", a.sign, a.int_part, a.num, a.denum);
}

