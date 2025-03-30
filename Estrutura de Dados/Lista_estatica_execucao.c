/*Execução da lista estática para a materia de Estrutura de dados;
Autor: Jeovanni Conservani Silva;
RA: 190691.*/

#include <stdio.h>
#include <stdlib.h>
#include "Lista_estatica.h"

/* Inicializa a lista, definindo seu tamanho como zero.
 * A lista será representada por um vetor de tamanho fixo (MAX) e um contador de tamanho.*/
void cria(Lista *p_l)
{
    p_l->tam = 0; // Inicializa o tamanho da lista como zero
}

/* Verifica se a lista está vazia.
 * Retorna 1 se a lista estiver vazia (tam == 0), ou 0 caso contrário.*/
int vazia(Lista *p_l)
{
    return (p_l->tam == 0); // Se o tamanho for zero, a lista está vazia
}

/* Insere um elemento no início da lista.
 * Se a lista estiver cheia (tam >= MAX), exibe uma mensagem de erro.
 * Desloca os elementos da lista para a direita para abrir espaço no início.*/
void insere_inicio(Lista *p_l, elem_t e)
{
    if (p_l->tam >= MAX)
    {
        printf("Lista cheia!\n"); // Verifica se há espaço na lista
        return;
    }
    for (int i = p_l->tam; i > 0; i--)
    {
        p_l->vet[i] = p_l->vet[i - 1]; // Desloca os elementos à direita
    }
    p_l->vet[0] = e; // Insere o novo elemento no início
    p_l->tam++; // Aumenta o tamanho da lista
}

/* Insere um elemento no final da lista.
 * Se a lista estiver cheia (tam >= MAX), exibe uma mensagem de erro.*/
void insere_fim(Lista *p_l, elem_t e)
{
    if (p_l->tam >= MAX)
    {
        printf("Lista cheia!\n"); // Verifica se há espaço na lista
        return;
    }
    p_l->vet[p_l->tam] = e; // Insere o elemento no final
    p_l->tam++; // Aumenta o tamanho da lista
}

/* Insere um elemento de forma ordenada na lista.
 * Se o elemento já existir, não é inserido e retorna 0.
 * Se a lista estiver cheia, exibe uma mensagem de erro.
 * Desloca os elementos para abrir espaço na posição correta.*/
int insere_ordenado(Lista *p_l, elem_t e)
{
    if (p_l->tam >= MAX)
    {
        printf("Lista cheia!\n"); // Verifica se há espaço na lista
        return 0;
    }

    int i = 0;

    while (i < p_l->tam && p_l->vet[i] < e)
    {
        i++; // Encontra a posição correta para o elemento
    }

    if (i < p_l->tam && p_l->vet[i] == e)
    {
        return 0; // Se o elemento já existe, não insere
    }

    // Desloca os elementos para abrir espaço
    for (int j = p_l->tam; j > i; j--)
    {
        p_l->vet[j] = p_l->vet[j - 1];
    }

    p_l->vet[i] = e; // Insere o elemento na posição correta
    p_l->tam++; // Aumenta o tamanho da lista
    return 1; // Retorna 1 indicando que o elemento foi inserido
}

/* Verifica se a lista está ordenada em ordem crescente.
 * Retorna 1 se a lista estiver ordenada, ou 0 se estiver desordenada.*/
int ordenada(Lista *p_l)
{
    for (int i = 0; i < p_l->tam - 1; i++)
    {
        if (p_l->vet[i] > p_l->vet[i + 1])
        {
            return 0; // Se encontrar um par de elementos desordenados, retorna 0
        }
    }
    return 1; // Se a lista estiver ordenada, retorna 1
}

/* rdena a lista usando o método de seleção.
 * Ordena a lista em ordem crescente.*/
void ordena(Lista *p_l)
{
    for (int i = 0; i < p_l->tam - 1; i++)
    {
        int min_idx = i;
        for (int j = i + 1; j < p_l->tam; j++)
        {
            if (p_l->vet[j] < p_l->vet[min_idx])
            {
                min_idx = j; // Encontra o índice do menor elemento
            }
        }
        // Troca os elementos
        elem_t temp = p_l->vet[i];
        p_l->vet[i] = p_l->vet[min_idx];
        p_l->vet[min_idx] = temp;
    }
}

/* Remove o primeiro elemento da lista.
 * Se a lista estiver vazia, retorna 0.
 * Se a lista tiver elementos, remove o primeiro e desloca os outros para a esquerda.*/
int remove_inicio(Lista *p_l, elem_t *p_e)
{
    if (vazia(p_l)) return 0; // Verifica se a lista está vazia

    *p_e = p_l->vet[0]; // Armazena o valor do primeiro elemento

    for (int i = 0; i < p_l->tam - 1; i++)
    {
        p_l->vet[i] = p_l->vet[i + 1]; // Desloca os elementos para a esquerda
    }

    p_l->tam--; // Diminui o tamanho da lista
    return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
}

/* Remove o último elemento da lista.
 * Se a lista estiver vazia, retorna 0.
 * Se a lista tiver elementos, remove o último e diminui o tamanho da lista.*/
int remove_fim(Lista *p_l, elem_t *p_e)
{
    if (vazia(p_l)) return 0; // Verifica se a lista está vazia

    *p_e = p_l->vet[p_l->tam - 1]; // Armazena o valor do último elemento
    p_l->tam--; // Diminui o tamanho da lista
    return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
}

/* Remove um elemento específico da lista.
 * Se o elemento não for encontrado, retorna 0.
 * Se a lista estiver vazia, retorna 0.
 * Desloca os elementos após o elemento removido para a esquerda.*/
int remove_valor(Lista *p_l, elem_t e)
{
    int i = 0;

    while (i < p_l->tam && p_l->vet[i] != e)
    {
        i++; // Encontra o índice do elemento
    }

    if (i == p_l->tam) return 0; // Se o elemento não foi encontrado, retorna 0

    for (int j = i; j < p_l->tam - 1; j++)
    {
        p_l->vet[j] = p_l->vet[j + 1]; // Desloca os elementos para a esquerda
    }

    p_l->tam--; // Diminui o tamanho da lista
    return 1; // Retorna 1 indicando que a remoção foi bem-sucedida
}

/* Inverte os elementos da lista.
 * Troca a posição dos elementos, fazendo com que o primeiro elemento se torne o último.*/
void inverte(Lista *p_l)
{
    for (int i = 0; i < p_l->tam / 2; i++)
    {
        elem_t temp = p_l->vet[i];
        p_l->vet[i] = p_l->vet[p_l->tam - i - 1];
        p_l->vet[p_l->tam - i - 1] = temp; // Troca os elementos
    }
}

/* Remove todos os elementos da lista.
 * Zera o contador de tamanho da lista.*/
void libera(Lista *p_l)
{
    p_l->tam = 0; // Zera o contador de tamanho da lista
}

/* Exibe os elementos da lista.
 * Se a lista estiver vazia, exibe uma mensagem informando que está vazia.*/
void exibe(Lista *p_l)
{
    if (vazia(p_l))
    {
        printf("Lista vazia!\n"); // Se a lista estiver vazia, exibe mensagem
        return;
    }

    for (int i = 0; i < p_l->tam; i++)
    {
        printf("%d ", p_l->vet[i]); // Exibe os elementos da lista
    }
}