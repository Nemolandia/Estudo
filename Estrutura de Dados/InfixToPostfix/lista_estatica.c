/*
 * Programa: lista_estatica.c
 * Descrição: Este programa implementa uma lista estática com operações básicas como
 *            inserção, remoção, ordenação e exibição de elementos.
 * Autor: Victor Kenji Umezu
 * RA: 235289
 * Data da última modificação: 13/03/2025
 */

#include <stdio.h>
#include "lista_estatica.h"

/* Inicializa uma lista */
void cria(Lista *p_l) {
    p_l->tam = 0; // Inicializa o tamanho da lista como 0 (lista vazia)
}

/* Verifica se a lista está vazia ou não */
int vazia(Lista *p_l) {
    return (p_l->tam == 0); // Retorna 1 se a lista estiver vazia, 0 caso contrário
}

/* Insere um elemento no início da lista */
void insere_inicio(Lista *p_l, elem_t e) {
    if (p_l->tam == MAX) { // Verifica se a lista está cheia
        printf("Erro: Lista cheia!\n");
        return;
    }

    for (int i = p_l->tam; i > 0; i--) { // Desloca todos os elementos para a direita
        p_l->vet[i] = p_l->vet[i - 1];
    }

    p_l->vet[0] = e; // Insere o novo elemento no início
    p_l->tam++; // Incrementa o tamanho da lista
}

/* Insere um elemento no final da lista */
void insere_fim(Lista *p_l, elem_t e) {
    if (p_l->tam == MAX) { // Verifica se a lista está cheia
        printf("Erro: Lista cheia!\n");
        return;
    }

    p_l->vet[p_l->tam] = e; // Insere o novo elemento no final
    p_l->tam++; // Incrementa o tamanho da lista
}

/* Insere um elemento na lista de maneira ordenada.
   Retorna 0 caso o elemento já exista na lista.
   Assume que a lista está ordenada */
int insere_ordenado(Lista *p_l, elem_t e) {
    if (p_l->tam == MAX) { // Verifica se a lista está cheia
        printf("Erro: Lista cheia!\n");
        return 0;
    }

    int i;
    for (i = 0; i < p_l->tam; i++) { // Percorre a lista para verificar se o elemento já existe
        if (p_l->vet[i] == e) {
            return 0; // Retorna 0 se o elemento já existir
        }
        if (p_l->vet[i] > e) { // Encontra a posição correta para inserir o elemento
            break;
        }
    }

    for (int j = p_l->tam; j > i; j--) { // Desloca os elementos para a direita
        p_l->vet[j] = p_l->vet[j - 1];
    }

    p_l->vet[i] = e; // Insere o novo elemento na posição correta
    p_l->tam++; // Incrementa o tamanho da lista

    return 1; // Retorna 1 indicando que a inserção foi bem-sucedida
}

/* Verifica se a lista está ordenada */
int ordenada(Lista *p_l) {
    for (int i = 0; i < p_l->tam - 1; i++) { // Percorre a lista
        if (p_l->vet[i] > p_l->vet[i + 1]) { // Verifica se o próximo elemento é menor
            return 0; // Retorna 0 se a lista não estiver ordenada
        }
    }
    return 1; // Retorna 1 se a lista estiver ordenada
}

/* Ordena a lista */
void ordena(Lista *p_l) {
    // Implementação de uma ordenação simples (ex: Bubble Sort)
    elem_t temp;
    for (int i = 0; i < p_l->tam - 1; i++) {
        for (int j = 0; j < p_l->tam - i - 1; j++) {
            if (p_l->vet[j] > p_l->vet[j + 1]) { // Troca os valores se estiverem fora de ordem
                temp = p_l->vet[j];
                p_l->vet[j] = p_l->vet[j + 1];
                p_l->vet[j + 1] = temp;
            }
        }
    }
}

/* Remove o elemento que está no início da lista.
   Retorna 0 caso a lista esteja vazia */
int remove_inicio(Lista *p_l, elem_t *p_e) {
    if (vazia(p_l)) { // Verifica se a lista está vazia
        return 0; // Retorna 0 se a lista estiver vazia
    }

    *p_e = p_l->vet[0]; // Armazena o valor do elemento a ser removido

    for (int i = 0; i < p_l->tam - 1; i++) { // Desloca todos os elementos para a esquerda
        p_l->vet[i] = p_l->vet[i + 1];
    }

    p_l->tam--; // Decrementa o tamanho da lista

    return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
}

/* Remove o elemento que está no final da lista.
   Retorna 0 caso a lista esteja vazia */
int remove_fim(Lista *p_l, elem_t *p_e) {
    if (vazia(p_l)) { // Verifica se a lista está vazia
        return 0; // Retorna 0 se a lista estiver vazia
    }

    *p_e = p_l->vet[p_l->tam - 1]; // Armazena o valor do elemento a ser removido
    p_l->tam--; // Decrementa o tamanho da lista

    return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
}

/* Remove o número de valor e.
   Retorna 0 caso este número não tenha sido encontrado */
int remove_valor(Lista *p_l, elem_t e) {
    int pos = -1;

    for (int i = 0; i < p_l->tam; i++) { // Percorre a lista para encontrar o elemento
        if (p_l->vet[i] == e) {
            pos = i; // Armazena a posição do elemento
            break;
        }
    }

    if (pos == -1) { // Se o elemento não foi encontrado
        return 0; // Retorna 0 indicando que o elemento não foi encontrado
    }

    for (int i = pos; i < p_l->tam - 1; i++) { // Desloca os elementos para a esquerda
        p_l->vet[i] = p_l->vet[i + 1];
    }

    p_l->tam--; // Decrementa o tamanho da lista

    return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
}

/* Inverte os elementos de uma lista */
void inverte(Lista *p_l) {
    elem_t temp;
    for (int i = 0; i < p_l->tam / 2; i++) { // Percorre metade da lista
        temp = p_l->vet[i];
        p_l->vet[i] = p_l->vet[p_l->tam - 1 - i]; // Troca os elementos simetricamente
        p_l->vet[p_l->tam - 1 - i] = temp;
    }
}

/* Remove todos os números da lista */
void libera(Lista *p_l) {
    p_l->tam = 0; // Define o tamanho da lista como 0 (lista vazia)
}

/* Exibe o conteúdo da lista */
void exibe(Lista *p_l) {
    for (int i = 0; i < p_l->tam; i++) { // Percorre a lista exibindo cada elemento
        printf("%c ", p_l->vet[i]);
    }
}
