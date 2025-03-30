#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void experiment1()
{
    unsigned short x = 44672;

    printf(" Var | Address | Value | Bytes\n");
    printf(" %5s | %p | %d | 0x", "x", (void*)&x, x);

    unsigned char *p = (unsigned char*)&x;

    for (int i = 0; i < sizeof(x); i++)
    {
        printf("%X", p[i]);
    }
    printf("\n");
}