#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct
{
    unsigned char tipo;
    union { unsigned char u[4]; unsigned int addr; } ip;
    char gw;
} ipv4_t;

int main()
{
    experiment1();
    experiment2();
    experiment3();
    experiment4();
    return 0;
}

void experiment4()
{
    ipv4_t ip;

    printf("IP: ");
    scanf("%hhu %hhu %hhu %hhu", &ip.ip.u[0], &ip.ip.u[1], &ip.ip.u[2], &ip.ip.u[3]);

    printf("Gateway (0/1): ");
    scanf("%hhd", &ip.gw);

    ip.gw = ip.gw ? ~0 : 0;

    printf("IP: 0x%X\nEstrutura: %p\nAddr: %p\nU: %p\nGW: %p\n", ip.ip.addr, (void*)&ip, (void*)&ip.ip.addr, (void*)&ip.ip.u, (void*)&ip.gw);
}