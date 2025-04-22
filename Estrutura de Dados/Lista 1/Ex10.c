/*Implemente uma função que copie um vetor para um novo vetor alocado
dinamicamente. O tamanho e o conteúdo do vetor original devem ser preservados. A
função deve seguir o protótipo: int *copiaVetor(int *vet, int n); */

#include <stdio.h>
#include <stdlib.h>

int *copiaVetor(int *vet, int n)
{
  int i;
  int *novoVetor = (int *)malloc(n * sizeof(int));

  if (novoVetor == NULL)
  {
    printf("Erro na alocacao de memoria.\n");
    exit(1);
  }

  for (i = 0; i < n; i++)
  {
    novoVetor[i] = vet[i];
  }

  return novoVetor;
}

int main()
{
  int n, i;

  printf("Digite o tamanho do vetor: ");
  scanf("%d", &n);

  int *vetor = (int *)malloc(n * sizeof(int));

  if (vetor == NULL)
  {
    printf("Erro na alocacao de memoria.\n");
    return 1;
  }

  printf("Digite os elementos do vetor:\n");
  for (i = 0; i < n; i++)
  {
    scanf("%d", &vetor[i]);
  }

  int *copia = copiaVetor(vetor, n);

  printf("Vetor copiado:\n");
  for (i = 0; i < n; i++)
  {
    printf("%d ", copia[i]);
  }
  printf("\n");

  free(vetor);
  free(copia);

  return 0;
}
