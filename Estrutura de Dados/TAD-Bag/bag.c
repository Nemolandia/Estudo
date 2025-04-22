// Nome: Felipe de Brito Lima
// RA: 236672 Turma:IN2

#include <stdio.h>
#include "bag.h"


// Função para inicializar a sacola (tornar todos os itens 0)
void init(Bag *b) {
    int i;  // Declaração da variável fora do laço
    for (i = 0; i < BAGSIZE; i++) {
        b->item[i] = 0;
    }
}


// Função para contar o número de itens na sacola (não vazios)
int size(Bag *b) {
    int count = 0;
    int i;  // Declaração da variável fora do laço
    for (i = 0; i < BAGSIZE; i++) {
        if (b->item[i] != 0) { // Conta os itens que não são zero
            count++;
        }
    }
    return count;
}


// Função para inserir um item na sacola
int insert(Bag *b, int elem) {
    int i;  // Declaração da variável fora do laço
    for (i = 0; i < BAGSIZE; i++) {
        if (b->item[i] == 0) { // Encontra o primeiro espaço vazio
            b->item[i] = elem;  // Insere o item
            return 1;            // Retorna sucesso
        }
    }
    return 0; // Se não encontrar espaço, retorna falha
}


// Função para verificar se um item está presente na sacola
int check(Bag *b, int elem) {
    int i;  // Declaração da variável fora do laço
    for (i = 0; i < BAGSIZE; i++) {
        if (b->item[i] == elem) {
            return 1; // Se o item for encontrado, retorna 1
        }
    }
    return 0; // Caso contrário, retorna 0
}


// Função para remover um item da sacola
int delete(Bag *b, int elem) {
    int i;  // Declaração da variável antes do loop
    for (i = 0; i < BAGSIZE; i++) {
        if (b->item[i] == elem) {  // Encontrou o item a ser removido
            b->item[i] = 0;         // Marca como vazio
            return 1;               // Retorna sucesso
        }
    }
    return 0;  // Se o item não foi encontrado, retorna falha
}


// Função para imprimir todos os itens da sacola
void printall(Bag *b) {
    printf("Produtos no carrinho: ");
    int first = 1;  // Usado para controlar a formatação (evitar uma vírgula extra no final)
    int i; // Declaração antes do loop

    for (i = 0; i < BAGSIZE; i++) {
        if (b->item[i] != 0) { // Só imprime os produtos não vazios
            if (!first) {
                printf(", ");
            }
            printf("%d", b->item[i]);
            first = 0;  // A partir daqui, já não será o primeiro item
        }
    }
    if (first) {
        printf("Carrinho vazio");
    }
    printf("\n");
}






 
