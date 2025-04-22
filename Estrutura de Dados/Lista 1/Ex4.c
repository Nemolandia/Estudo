/*Crie uma função capaz de encontrar o menor valor em um vetor de inteiros. A
função recebe um vetor e seu tamanho como entrada e retorna o menor número
encontrado. Utilize este protótipo: int menorElemento(int *vet, int n); */

#include <stdio.h>
#include <stdlib.h>

int menorElemento(int *vet, int n)
{
  int menor = *vet, i;

  for (i = 1; i < n; i++)
  {
    if (*(vet + i) < menor)
    {
      menor = *(vet + i);
    }
  }
  return menor;
}

int main()
{
  int n, i, menor;

  do
  {
    printf("Digite a quantidade de elementos do vetor: ");
    scanf("%d", &n);

    if (n <= 0)
    {
      printf("Tamanho do vetor inválido!\n");
    }
  } while (n <= 0);

  int *vetor = (int *)malloc(n * sizeof(int));

  if (vetor == NULL)
  {
    printf("Erro ao alocar memória!\n");
    return 1;
  }

  printf("Digite os %d elementos do vetor:\n", n);
  for (i = 0; i < n; i++)
  {
    scanf("%d", &vetor[i]);
  }

  menor = menorElemento(vetor, n);
  printf("O menor elemento do vetor é: %d\n", menor);

  free(vetor);

  return 0;
}
