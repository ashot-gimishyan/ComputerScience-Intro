// Moscow Institute of Physics and Technology
// Computer Science

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct{
  int size1,size2,size3;
}Triangle;

// Устанавливает значения сторон треугольника.
// Если такой треугольник не может существовать, функция
// возвращает 0, если может - 1
int setTri(int a, int b, int c, Triangle* tmp);

// Возвращает периметр треугольника (существование проверять не нужно)
int getPerimetr(Triangle * trABC);

// сравнение двух треугольников, если равны, то возвращается 1, если нет - 0
int cmp(Triangle one, Triangle two);


int main(int argc, char const *argv[]) {

  Triangle * New;
  Triangle * Old;
  int ab, bc, ac;

  scanf("%d %d %d", &ab, &bc, &ac);

  if (setTri(ab,bc,ac, New) == 1)
  {
    printf("Perimetr = %d\n", getPerimetr(New));
  }

  /*
  if ( cmp(New, Old) == 1 )
  {
      printf("%s\n", "Треугольники равны");
  }
  else
  {
    printf("%s\n", "Треугольники не равны");
  }
  */

  return 0;
}


// Устанавливает значения сторон треугольника.
// Если такой треугольник не может существовать, функция
// возвращает 0, если может - 1
int setTri(int a, int b, int c, Triangle* tmp)
{
  if (a + b > c)
  {
    if (a + c > b)
    {
      if (b + c > a)
      {
        tmp -> size1 = a;
        tmp -> size2 = b;
        tmp -> size3 = c;
        return 1;
      }
    }
  }

  printf("%s\n", "Такого треугольника, естественно не существует!");
  return 0;
}

// Возвращает периметр треугольника (существование проверять не нужно)
int getPerimetr(Triangle * trABC)
{
  return trABC -> size1 + trABC -> size2 + trABC -> size3;
}


// сравнение двух треугольников, если равны, то возвращается 1, если нет - 0
int cmp(Triangle one, Triangle two)
{
  if (one.size1 == two.size1)
  {
    if (one.size2 == two.size2)
    {
      if (one.size3 == two.size3)
      {
        return 1;
      }
    }
  }

  // если нет
  return 0;
}
