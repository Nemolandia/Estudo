#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void experiment2()
{
    float array[16];
    int seed;

    printf("Seed: ");
    scanf("%d", &seed);
    srand(seed);

    for (int i = 0; i < 16; i++)
    {
        array[i] = (float)rand() / RAND_MAX;
    }
    printf("Array: %p\nElem0: %f, %p\nElem2: %f, %p\nElem15: %f, %p\n", (void*)array, array[0], (void*)&array[0], array[2], (void*)&array[2], array[15], (void*)&array[15]);
    printf("Diff: %ld\n", (char*)&array[15] - (char*)&array[0]);
}