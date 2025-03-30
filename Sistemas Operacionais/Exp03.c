#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void preencher_matriz(float m[2][2], float a)
{
    a *= M_PI / 180.0;
    m[0][0] = cos(a); m[0][1] = -sin(a);
    m[1][0] = sin(a); m[1][1] = cos(a);
}

void experiment3()
{
    float m[2][2], a;

    printf("Ângulo: ");
    scanf("%f", &a);

    preencher_matriz(m, a);

    printf("Matriz:\n%f %f\n%f %f\n", m[0][0], m[0][1], m[1][0], m[1][1]);
}