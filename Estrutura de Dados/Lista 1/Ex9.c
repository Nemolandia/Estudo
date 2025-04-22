/*Desenvolva uma função que localize a primeira ocorrência de um número em um
vetor. Caso o número esteja presente, a função retorna o índice correspondente; caso
contrário, retorna em -1. O protótipo correto é: int buscaNumero(int *vet, int n, int num); */

#include <stdio.h>

int buscaNumero(int *vet, int n, int num)
{
  int i;
  for (i = 0; i < n; i++)
  {
    if (vet[i] == num)
    {
      return i;
    }
  }
  return -1;
}

int main()
{
  int n, i, num, indice;

  printf("Digite o tamanho do vetor: ");
  scanf("%d", &n);

  int vet[n];

  printf("Digite os elementos do vetor:\n");
  for (i = 0; i < n; i++)
  {
    scanf("%d", &vet[i]);
  }

  printf("Digite o numero a ser buscado: ");
  scanf("%d", &num);

  indice = buscaNumero(vet, n, num);

  if (indice != -1)
  {
    printf("Numero encontrado na posicao: %d\n", indice);
  }
  else
  {
    printf("Numero nao encontrado.\n");
  }

  return 0;
}
