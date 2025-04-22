/*Crie uma função que troque os valores de dois inteiros entre si. Para isso, a função
deve receber dois ponteiros para inteiros e realizar a troca diretamente na memória.
O protótipo da função é: void troca(int *a, int *b); */

#include <stdlib.h>
#include <stdio.h>

void troca(int *a, int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}

int main()
{
  int x, y;

  printf("Digite dois valores: ");
  scanf("%d %d", &x, &y);

  printf("Antes da troca: x = %d, y = %d\n", x, y);

  troca(&x, &y);

  printf("Depois da troca: x = %d, y = %d\n", x, y);

  return 0;
}
