/*Desenvolva uma função para inverter a ordem dos elementos de um vetor. O vetor
deve ser modificado diretamente, sem criar uma cópia auxiliar. A assinatura da função
deve ser: void inverteVetor(int *vet, int n); */

#include <stdio.h>

void inverteVetor(int *vet, int n)
{
  int i, temp;
  for (i = 0; i < n / 2; i++)
  {
    temp = vet[i];
    vet[i] = vet[n - i - 1];
    vet[n - i - 1] = temp;
  }
}

int main()
{
  int n, i;

  printf("Digite o tamanho do vetor: ");
  scanf("%d", &n);

  int vet[n];

  printf("Digite os elementos do vetor:\n");
  for (i = 0; i < n; i++)
  {
    scanf("%d", &vet[i]);
  }

  inverteVetor(vet, n);

  printf("Vetor invertido:\n");
  for (i = 0; i < n; i++)
  {
    printf("%d ", vet[i]);
  }
  printf("\n");

  return 0;
}
