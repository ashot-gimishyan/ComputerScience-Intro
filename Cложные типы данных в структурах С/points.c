// Компьютерные технологии
// Moscow Institute of Physics and Technology
// Ashot Gimishyan
// Язык Си

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//структура, описывающая координаты точки на плоскости
typedef struct Crd {
    int x;
    int y;
} Coord;

// Вычисляет квадрат расстояния между точками
int sizePoint(Coord a, Coord b);

// Структура для хранения квадрата расстояния между точками:
typedef struct {
    int* m; // динамический массив для хранения всех расстояний
    int n; // количество расстояний
} Distances;

// Заполнение структуры для хранения квадрата расстояний:
Distances sizeFill(Coord* points, int n)
{ // n - количество точек

    Distances ds;
    ds.m = (int*)calloc(n, sizeof(int)); // - память для int
    ds.n = n; // - количество расстояний

    int i, j, dist;
    int index = 0;
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            dist = sizePoint(points[i], points[j]);
            *(ds.m + index) = dist;
            index++;
        }
    }

    return ds;
};

// Печать всех расстояний:
void printD(Distances d)
{

    int i;
    for (i = 0; i < d.n; i++) {
        printf("%d\n", *(d.m + i));
    }
};

// Поиск минимального расстояния:
int minDistance(Distances ds)
{

    int min = *(ds.m);
    int i;
    for (i = 1; i < ds.n; i++) {
        if (*(ds.m + i) < min)
            min = *(ds.m + i);
    }

    return min;
};

// Пример использования этих функций
int main()
{

    Coord points[3];
    int i, x, y;

    Distances ds;

    // Прочитать значения координат
    for (i = 0; i < 3; i++) {
        scanf("%d%d", &x, &y);
        points[i].x = x;
        points[i].y = y;
    }

    // Заполнение структуры расстояний:
    ds = sizeFill(points, 3);

    // печать всех расстояний:
    printD(ds);

    // минимальное из квадратов расстояний
    int min_dist = minDistance(ds);

    printf("Min dist = %d\n", min_dist);
}

int sizePoint(Coord a, Coord b)
{
    return pow(a.x - b.x, 2) + pow(a.y - b.y, 2);
}
