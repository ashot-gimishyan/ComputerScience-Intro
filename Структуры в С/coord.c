// Задача 3
// координаты точки
// Ashot Gimishyan | MIPT

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float x, y;
} Coord;

void move(float deltaX, float deltaY, Coord* point);

int main()
{
    Coord* point = (Coord*)malloc(sizeof(Coord));
    point->x = 1.0;
    point->y = 2.0;

    move(1.0, 2.0, point);
    printf("%.f %.f\n", point->x, point->y);
}

void move(float deltaX, float deltaY, Coord* point)
{
    point->x = point->x + deltaX;
    point->y = point->y + deltaY;
}

