// texto.c
/*
*	por: Henrique Seiji Kuroiwa (RA: 236060)
*	curso: Engenharia de Computacao - 5 semestre - 2025s1
*/

#include <stdio.h>
#include <string.h>
#include "texto.h"

// Inicializar ou reiniciar a string
void iniciaString(texto *t)
{
	t->frase[0] = '\0';
}

// Receber a String
void insereString(texto *t)
{	
	gets(t->frase);
}

// Imprimir a String
void imprimeString(texto *t)
{
	printf("%s", t->frase);
}

// Calcular tamanho da string
int calculaTamanho(texto *t)
{
	int i, cont = 0;
	
	for(i = 0; i < 200; i++)
	{
		if(t->frase[i] == '\0') break;
		cont++;
	}
	
	return cont;
}

// Comparar duas strings
int comparaString(texto *t1, texto *t2)
{
	return strcmp(t1->frase, t2->frase);
}

// Inverter string
void inverteString(texto *t)
{
	int i, tam;
	char temp;
	
	tam = calculaTamanho(t);
	
	for(i = 0; i <= (tam/2)-1; i++)
	{
		temp = t->frase[i];
		t->frase[i] = t->frase[tam-1-i];
		t->frase[tam-1-i] = temp;
	}
}
