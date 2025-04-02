/*Exercício Lista_dupla_execucao.c: Implementação das operações realizadas na Lista_dupla.h
Autor:Jeovanni Conservani Silva
RA: 190691*/

#include "Lista_dupla.h"
#include <stdio.h>
#include <stdlib.h>

// Aloca um novo nó
No_lista *aloca()
{
    No_lista *novo;
    novo = (No_lista*)malloc(sizeof(No_lista));

    if (novo == NULL)
    {
        printf("Sem espaço de memória\n");
        exit(1);
    }
    return novo;
}//aloca

// Cria uma lista vazia
void cria(Lista *p_l)
{
    *p_l = NULL;
}//cria

// Verifica se a lista está vazia
int vazia(Lista *p_l)
{
    return (*p_l == NULL);
}//vazia

// Insere um novo nó no início
void insere_inicio(Lista *p_l, elem_t e)
{
    No_lista *novo;

    novo = aloca();
    novo->info = e;
    novo->prox = *p_l;
    novo->ant = NULL;

    if (*p_l)
    {
        (*p_l)->ant = novo;
    }
    *p_l = novo;
}//insere_inicio

// Insere um novo nó no fim
void insere_fim(Lista *p_l, elem_t e)
{
    No_lista *novo, *aux;

    novo = aloca();
    novo->info = e;
    novo->prox = NULL;

    if (*p_l == NULL)
    {
        novo->ant = NULL;
        *p_l = novo;
    }
    else
    {
        aux = *p_l;
        while (aux->prox)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    }
}//insere_fim

// Insere um nó ordenado
int insere_ordenado(Lista *p_l, elem_t e)
{
    No_lista *novo, *aux;

    novo = aloca();
    aux = *p_l;
    novo->info = e;

    if (aux == NULL || aux->info >= e)
    {
        novo->prox = aux;
        novo->ant = NULL;

        if (aux)
        {
            aux->ant = novo;
        }
        *p_l = novo;
        return 1;
    }
    while (aux->prox && aux->prox->info < e)
    {
        aux = aux->prox;
    }
    novo->prox = aux->prox;
    novo->ant = aux;

    if (aux->prox)
    {
        aux->prox->ant = novo;
    }
    aux->prox = novo;
    return 1;
}//insere_ordenado

// Verifica se a lista está ordenada
int ordenada(Lista *p_l)
{
    No_lista *aux;

    aux = *p_l;

    while (aux != NULL && aux->prox != NULL)
    {
        if (aux->info > aux->prox->info)
        {
            return 0;
        }
        aux = aux->prox;
    }
    return 1;
}//ordenada

//Ordena a lista
void ordena(Lista *p_l)
{
    No_lista *i, *j;
    elem_t aux;

    for (i = *p_l; i; i = i->prox)
    {
        for (j = i->prox; j; j = j->prox)
        {
            if (i->info > j->info)
            {
                aux = i->info;
                i->info = j->info;
                j->info = aux;
            }
        }
    }
}//ordena

//Remove o primeiro elemento
int remove_inicio(Lista *p_l, elem_t *p_e)
{
    No_lista *aux;

    if (*p_l == NULL)
    {
        return 0;
    }
    aux = *p_l;
    *p_e = aux->info;
    *p_l = aux->prox;

    if (*p_l != NULL)
    {
        (*p_l)->ant = NULL;
    }
    free(aux);
    return 1;
}//remove_inicio

// Remove o último elemento
int remove_fim(Lista *p_l, elem_t *p_e)
{
    No_lista *aux;

    if (*p_l == NULL)
    {
        return 0;
    }
    aux = *p_l;

    while (aux->prox != NULL)
    {
        aux = aux->prox;
    }
    *p_e = aux->info;

    if (aux->ant != NULL)
    {
        aux->ant->prox = NULL;
    }
    else
    {
        *p_l = NULL;
    }
    free(aux);
    return 1;
}//remove_fim

// Remove um elemento específico
int remove_valor(Lista *p_l, elem_t e)
{
    No_lista *aux;

    aux = *p_l;

    while (aux != NULL && aux->info != e)
    {
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        return 0;
    }
    if (aux->ant != NULL)
    {
        aux->ant->prox = aux->prox;
    }
    else
    {
        *p_l = aux->prox;
    }
    if (aux->prox != NULL)
    {
        aux->prox->ant = aux->ant;
    }
    free(aux);
    return 1;
}//remove_valor

// Inverte a lista
void inverte(Lista *p_l)
{
    No_lista *aux, *aux2;

    aux = *p_l;

    while (aux != NULL)
    {
        aux2 = aux->prox;
        aux->prox = aux->ant;
        aux->ant = aux2;
        *p_l = aux;
        aux = aux2;
    }
}//inverte

// Libera a lista
void libera(Lista *p_l)
{
    No_lista *aux;

    while (*p_l != NULL)
    {
        aux = *p_l;
        *p_l = aux->prox;
        free(aux);
    }
}//libera

// Exibe a lista
void exibe(Lista *p_l)
{
    No_lista *aux;

    aux = *p_l;
    while (aux != NULL)
    {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}//exibe