/*
  Programa: Exercícios com Ponteiros em C
  Descrição: Este programa implementa uma série de funções utilizando ponteiros para manipulação de variáveis, vetores e strings.
               São abordadas operações como troca de valores, soma de vetores, cópia de strings, entre outras.
  Autor: Jeovanni Conservani Silva
  Data da última modificação: 22/02/2025
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1) Função que troca os valores de dois inteiros
void troca(int *a, int *b) {
   
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

// 2) Função para calcular a soma dos elementos de um vetor
int somaVetor(int *vet, int n) {
   
    int soma = 0;

    for (int i = 0; i < n; i++) {
        soma += vet[i];
    }
    return soma;
}

// 3) Função que copia uma string para outra
void copiaString(char *dest, char *orig) {

    while (*orig != '\0') {
        *dest = *orig;
        dest++;
        orig++;
    }
    *dest = '\0';
}

// 4) Função que encontra o menor valor em um vetor
int menorElemento(int *vet, int n) {

    int menor = vet[0];

    for (int i = 1; i < n; i++) {
        if (vet[i] < menor) {
            menor = vet[i];
        }
    }
    return menor;
}

// 5) Função que aloca dinamicamente um vetor e o inicializa com um valor específico
int *alocaVetor(int n, int valor) {

    int *vet = (int *) malloc(n * sizeof(int));
    if (!vet) {
        fprintf(stderr, "Falha ao alocar memória\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        vet[i] = valor;
    }
    return vet;
}

// 6) Função que inverte a ordem dos elementos de um vetor
void inverteVetor(int *vet, int n) {

    int temp;

    for (int i = 0; i < n / 2; i++) {
        temp = vet[i];
        vet[i] = vet[n - i - 1];
        vet[n - i - 1] = temp;
    }
}

// 7) Função que conta quantas vogais existem em uma string
int contaVogais(char *str) {

    int count = 0;
    char c;

    while (*str != '\0') {
        c = *str;
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U') {
            count++;
        }
        str++;
    }
    return count;
}

// 8) Função que concatena duas strings
void concatenaString(char *dest, char *orig) {
   
    while (*dest != '\0') {
        dest++;
    }
    while (*orig != '\0') {
        *dest = *orig;
        dest++;
        orig++;
    }
    *dest = '\0';
}

// 9) Função que busca um número em um vetor e retorna seu índice
int buscaNumero(int *vet, int n, int num) {

    for (int i = 0; i < n; i++) {
        if (vet[i] == num) {
            return i;
        }
    }
    return -1;
}

// 10) Função que copia um vetor para um novo vetor alocado dinamicamente
int *copiaVetor(int *vet, int n) {

    int *novoVetor = (int *) malloc(n * sizeof(int));
   
    if (!novoVetor) {
        fprintf(stderr, "Falha ao alocar memória\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        novoVetor[i] = vet[i];
    }
    return novoVetor;
}

int main() {
    printf("Funções implementadas. Testes podem ser adicionados conforme necessário.\n");
    return 0;
}