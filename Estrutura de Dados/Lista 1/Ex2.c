/*Desenvolva uma função para calcular a soma dos elementos de um vetor. O vetor
de inteiros e seu tamanho são passados como parâmetros, e a função retorna a soma
de seus valores. Utilize o seguinte protótipo: int somaVetor(int *vet, int n); */

#include <stdio.h>
#include <stdlib.h>

int somaVetor(int *vet, int n)
{
  int soma = 0, i;

  for (i = 0; i < n; i++)
  {
    soma += *(vet + i);
  }

  return soma;
}

int main()
{
  int *vetor, tamanho, i, resultado;

  printf("Digite a quantidade de elementos do vetor: ");
  scanf("%d", &tamanho);

  vetor = (int *)malloc(tamanho * sizeof(int));
  if (vetor == NULL)
  {
    printf("Erro ao alocar memória.\n");
    return 1;
  }

  printf("Digite os %d elementos do vetor:\n", tamanho);
  for (i = 0; i < tamanho; i++)
  {
    printf("Elemento %d: ", i + 1);
    scanf("%d", &vetor[i]);
  }

  resultado = somaVetor(vetor, tamanho);

  printf("Soma dos elementos do vetor: %d\n", resultado);

  free(vetor);

  return 0;
}