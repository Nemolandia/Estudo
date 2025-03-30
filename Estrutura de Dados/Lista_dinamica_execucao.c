/*Execução da lista dinâmica para a materia de Estrutura de dados;
Autor: Jeovanni Conservani Silva;
RA: 190691.*/

#include <stdio.h>
#include <stdlib.h>
#include "Lista_dinamica.h"

No_lista *aloca_memoria()
{
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista));

    if (novo == NULL) {
        printf("Memoria insuficiente!\n");
        exit(1);
    }
    return novo;
}

void cria(Lista *p_l)
{
    *p_l = NULL;
}

int vazia(Lista *p_l)
{
    return (*p_l == NULL);
}

void insere_inicio(Lista *p_l, elem_t e)
{
    No_lista *novo = aloca_memoria();
    novo->info = e; //Atribui o valor ao novo nó
    novo->prox = *p_l; //O novo nó aponta para o nó que antes estava no início
    *p_l = novo; //A lista agora começa no novo nó
}

void insere_fim(Lista *p_l, elem_t e)
{
    No_lista *novo = aloca_memoria();
    novo->info = e; //Atribui o valor ao novo nó
    novo->prox = NULL; //O novo nó não tem próximo (será o último nó)

    if (*p_l == NULL)
    {
        *p_l = novo; //Se a lista estiver vazia, o novo nó é o primeiro da lista
    } 
    else
    {
        No_lista *temp = *p_l;

        while (temp->prox != NULL)
        {
            temp = temp->prox; //Encontra o último nó
        }
        temp->prox = novo; //Aponta o último nó para o novo nó
    }
}

int insere_ordenado(Lista *p_l, elem_t e)
{
    No_lista *novo = aloca_memoria();
    novo->info = e; // Atribui o valor ao novo nó

    // Caso a lista esteja vazia ou o novo elemento deva ir para o início
    if (*p_l == NULL || (*p_l)->info >= e)
    {
        novo->prox = *p_l;
        *p_l = novo; // A lista agora começa no novo nó
        return 1;
    }

    // Caso o elemento deva ser inserido após algum nó
    No_lista *temp = *p_l;

    while (temp->prox != NULL && temp->prox->info < e)
    {
        temp = temp->prox; // Percorre a lista até encontrar a posição correta
    }

    if (temp->prox != NULL && temp->prox->info == e)
    {
        free(novo); // Se o elemento já existe, não insere e libera a memória
        return 0;
    }

    novo->prox = temp->prox;
    temp->prox = novo; // Insere o novo nó na posição correta
    return 1;
}

int ordenada(Lista *p_l)
{
    if (*p_l == NULL || (*p_l)->prox == NULL)
    {
        return 1; // Lista vazia ou com um único elemento está ordenada
    }

    No_lista *temp = *p_l;

    while (temp->prox != NULL)
    {
        if (temp->info > temp->prox->info)
        {
            return 0; // Se encontrar um par desordenado, retorna 0
        }
        temp = temp->prox;
    }
    return 1; // Se percorreu toda a lista e não encontrou desordem, retorna 1
}

void ordena(Lista *p_l)
{
    if (*p_l == NULL || (*p_l)->prox == NULL)
    {
        return; // Lista vazia ou com um único elemento não precisa ser ordenada
    }

    No_lista *i, *j;
    elem_t temp;

    for (i = *p_l; i != NULL; i = i->prox)
    {
        for (j = i->prox; j != NULL; j = j->prox)
        {
            if (i->info > j->info)
            {
                // Troca os valores de i e j
                temp = i->info;
                i->info = j->info;
                j->info = temp;
            }
        }
    }
}

int remove_inicio(Lista *p_l, elem_t *p_e)
{
    if (vazia(p_l))
    {
        return 0; // Se a lista estiver vazia, não há o que remover
    }

    No_lista *temp = *p_l;
    *p_e = temp->info; // Armazena o valor do elemento a ser removido
    *p_l = temp->prox; // A lista agora começa no próximo nó
    free(temp); // Libera a memória do nó removido

    return 1;
}

int remove_fim(Lista *p_l, elem_t *p_e)
{
    if (vazia(p_l))
    {
        return 0; // Se a lista estiver vazia, não há o que remover
    }

    No_lista *temp = *p_l;

    if (temp->prox == NULL)
    { // Se a lista tem apenas um elemento
        *p_e = temp->info;
        *p_l = NULL; // A lista ficará vazia
        free(temp);
        return 1;
    }

    // Caso a lista tenha mais de um elemento
    while (temp->prox->prox != NULL)
    {
        temp = temp->prox; // Encontra o penúltimo nó
    }

    No_lista *ultimo = temp->prox;
    *p_e = ultimo->info;
    temp->prox = NULL; // O penúltimo nó agora será o último
    free(ultimo); // Libera a memória do último nó

    return 1;
}

int remove_valor(Lista *p_l, elem_t e)
{
    No_lista *temp = *p_l, *ant = NULL;

    // Percorre a lista até encontrar o valor
    while (temp != NULL && temp->info != e)
    {
        ant = temp;
        temp = temp->prox;
    }

    if (temp == NULL)
    {
        return 0; // Valor não encontrado
    }

    if (ant == NULL)
    { // Se for o primeiro nó
        *p_l = temp->prox;
    } else { // Se for um nó intermediário ou final
        ant->prox = temp->prox;
    }

    free(temp); // Libera a memória do nó removido
    return 1;
}

void inverte(Lista *p_l)
{
    No_lista *ant = NULL, *atual = *p_l, *prox = NULL;

    while (atual != NULL)
    {
        prox = atual->prox; // Salva o próximo nó
        atual->prox = ant; // Inverte o ponteiro do nó
        ant = atual; // O nó atual se torna o anterior para o próximo nó
        atual = prox; // Avança para o próximo nó
    }

    *p_l = ant; // O último nó se torna o primeiro da lista
}