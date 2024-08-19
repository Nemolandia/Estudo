#include<stdio.h>

// programa que recebe e imprime um vetor por meio de função, com passagem de parâmetro por referência
void recebe(int tam, int *p_vetor);
void imprime(int tam, int *p_vetor);

int main()
{
	int vetor[5];
	recebe(5, vetor);
	imprime(5, vetor);
	return 0;
}

void recebe(int tam, int *p_vetor)
{
	int i;
	for(i=0;i<tam;i++,p_vetor++)
	{
		printf("\nVetor[%d] = ", i);
		scanf("%d", p_vetor);
	}
}

void imprime(int tam, int *p_vetor)
{
	int i;
	for(i=0;i<tam;i++,p_vetor++)
	{
		printf("\nVetor[%d] = %d", i, *p_vetor);
	}
}

