/*Elabore uma função que aloque dinamicamente um vetor de inteiros e o inicialize
com um valor específico. A função recebe o tamanho do vetor e o valor de inicialização
e retorna um ponteiro para o vetor criado. O protótipo a seguir deve ser utilizado: int
*alocaVetor(int n, int valor); */

#include <stdio.h>
#include <stdlib.h>

int *alocaVetor(int n, int valor)
{
  int i;
  if (n <= 0)
  {
    printf("Erro: tamanho do vetor inválido!\n");
    return NULL;
  }

  int *vetor = (int *)malloc(n * sizeof(int));

  if (vetor == NULL)
  {
    printf("Erro ao alocar memória!\n");
    return NULL;
  }

  for (i = 0; i < n; i++)
  {
    vetor[i] = valor;
  }

  return vetor;
}

int main()
{
  int n, valor, i;

  printf("Digite o tamanho do vetor: ");
  scanf("%d", &n);

  printf("Digite o valor de inicialização: ");
  scanf("%d", &valor);

  int *vetor = alocaVetor(n, valor);
  if (vetor == NULL)
  {
    return 1;
  }

  printf("Vetor alocado e inicializado:\n");
  for (i = 0; i < n; i++)
  {
    printf("%d ", vetor[i]);
  }
  printf("\n");

  free(vetor);

  return 0;
}
