// Компьютерные технологии
// Moscow Institute of Physics and Technology
// Язык Си

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Crd {
    int x, y;
} Coord;


typedef struct Tr {
    Coord vertices[3];
    int lenSQ[3];
    float square;
} Triangle;


void moveTri(Triangle *tri, int x, int y);
float trian_square(Triangle tri);

float trian_square(Triangle tri)
{
  float Sq = 0.0;
  Sq = 0.5 * (tri.vertices[0].x * (tri.vertices[1].y - tri.vertices[2].y) +
  tri.vertices[1].x * (tri.vertices[2].y - tri.vertices[0].y) +
  tri.vertices[2].x * (tri.vertices[0].y - tri.vertices[1].y));

  return fabs(Sq);
}

void printTriangle(Triangle tri)
{
    int i;
    printf("{");

    for (i = 0; i < 3; i++) {
        printf("(%d,%d)", tri.vertices[i].x, tri.vertices[i].y);
    }
    printf("}");
    printf("%s %f %f %f\n"," Расстояния между точками: ", sqrt(pow(tri.vertices[1].x - tri.vertices[0].x, 2) + pow(tri.vertices[1].y - tri.vertices[0].y, 2)),
    sqrt(pow(tri.vertices[2].x - tri.vertices[1].x, 2) + pow(tri.vertices[2].y - tri.vertices[1].y, 2)),
    sqrt(pow(tri.vertices[2].x - tri.vertices[0].x, 2) + pow(tri.vertices[2].y - tri.vertices[0].y, 2)));


    printf("Площадь треугольника: %.2f\n\n\n", trian_square(tri));
};

// Функция возвращает объект треугольник:
Triangle fillTri_1(Coord* vert)
{

    Triangle tmp;
    int i;

    for (i = 0; i < 3; i++) {
        tmp.vertices[i].x = vert[i].x;
        tmp.vertices[i].y = vert[i].y;
    }

    return tmp;
};

int fillTri2(Triangle* tri, Coord* vert)
{
    int i;

    if (vert == 0)
        return 0;

    if (trian_square(*tri) == 0.0)
    {
      printf("Треугольника не существует\n");
      return 0;
    }

    for (i = 0; i < 3; i++) {

        tri->vertices[i].x = vert[i].x;
        tri->vertices[i].y = vert[i].y;
    }

    return 1;
};

Triangle* createTri(Coord* vert)
{
    int i;
    Triangle* tmp;

    if (vert == 0)
        return 0;

    tmp = (Triangle*)malloc(sizeof(Triangle));

    for (i = 0; i < 3; i++) {
        tmp->vertices[i].x = vert[i].x;
        tmp->vertices[i].y = vert[i].y;
    }

    return tmp;
};

int main()
{

    Coord points[18];
    Triangle tri[3];
    Triangle* ptri;
    int i, x, y;

    for (i = 0; i < 9; i++) {
        scanf("%d%d", &x, &y);
        points[i].x = x;
        points[i].y = y;
    }

    tri[1] = fillTri_1(points);
    printTriangle(tri[1]);

    if (fillTri2(tri, points + 3) == 0) {
        printf("Не получился треугольник!! :(");
        exit(1);
    };
    printTriangle(tri[0]);

    ptri = createTri(points + 6);

    if (ptri == 0) {
        printf("Не получился треугольник!! :(");
        exit(1);
    }

    printTriangle(*ptri);

    free(ptri);
    return 0;
}


// Функция движения треугольника, которая
// перемещает весь треугольник на x по оси x и на y по оси y.

void moveTri(Triangle *tri, int x, int y)
{

  int i;
  for (i = 0; i < 3; i++) {

      tri->vertices[i].x += x;
      tri->vertices[i].y += y;
  }

}
