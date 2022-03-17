#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x, y;
    float r;
} Circle;

Circle getCircle();
float getSquare(Circle);

int main()
{
    Circle a = getCircle();
    float square = getSquare(a);
    printf("%f\n", square);
}

Circle getCircle()
{
    Circle new;
    scanf("%d %d %f", &(new.x), &(new.y), &(new.r));
    if (new.r == 0.0) {
        printf("NO");
        exit(1);
    }

    return new;
}

float getSquare(Circle a)
{
    float PI = 3.1415926535;
    return PI * (a.r) * (a.r);
}

