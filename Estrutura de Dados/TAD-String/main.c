// main.c
/*
*	por: Henrique Seiji Kuroiwa (RA: 236060)
*	curso: Engenharia de Computacao - 5 semestre - 2025s1
*/

#include <stdio.h>
#include "texto.h"

int main()
{
	texto texto1, texto2;
	
	iniciaString(&texto1);
	iniciaString(&texto2);
	
	printf("Digite um texto: ");
	insereString(&texto1);
	
	printf("Digite outro texto: ");
	insereString(&texto2);
	
	printf("\nQuantidade de caracteres:");
	printf("\nTexto 1: %d", calculaTamanho(&texto1));
	printf("\nTexto 2: %d", calculaTamanho(&texto2));
	
	printf("\n\nComparacao de textos:");
	if(comparaString(&texto1, &texto2))
		printf("\nO Texto 1 e o Texto 2 sao diferentes!");
	else
		printf("\nO Texto 1 e o Texto 2 sao iguais!");
		
	printf("\n\nTextos invertidos:");
	inverteString(&texto1);
	inverteString(&texto2);
	printf("\n");
	imprimeString(&texto1);
	printf("\n");
	imprimeString(&texto2);
	
	return 0;
}
