/*Exercício Lista_dupla_execucao.c: Implementação das operações realizadas na Lista_dupla.h
Autor:Jeovanni Conservani Silva
RA: 190691*/

#include "Lista_dupla.h"
#include <stdio.h>
#include <stdlib.h>

//Aloca espaço de memória para a lista
No_lista aloca()
{
    No_lista *novo = (No_lista*)malloc(sizeof(No_lista));

    if(novo == NULL)
    {
        printf ("Sem espaço de memoria");
        exit(1);
    }
}

//Cria uma lsita vazia
void cria(Lista *p_l)
{
    *p_l = NULL;
}

//Mostra se a lista está vazia
int vazia (Lista *p_l)
{
    return (*p_l == NULL);
}//cria

//Insere um novo Nó no início da lista
void insere_inicio (Lista *p_l, elem_t e)
{
    No_lista *novo = aloca();

    novo->info = e;
    novo->prox = *p_l;
    *p_l = novo;
    novo->ant = NULL;
}//insere_inicio

//Insere um novo Nó no fim da lista
void insere_fim (Lista *p_l, elem_t e)
{
    No_lista *novo = aloca();
    No_lista *aux = *p_l;

    novo->info = e;
    novo->prox = NULL;
    novo->ant = aux;

    if (*p_l == NULL)
    {
        *p_l = novo;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novo;
    }
}//insere_fim

//Insere na lista a informação em ordem crescente
int insere_ordenado (Lista *p_l, elem_t e)
{
    No_lista *novo = aloca();
    No_lista *aux = *p_l;
    novo->info = e;

    //Caso a lista esteja vazia ou o elemento de início for maior que o elemento a ser inserido
    if (*p_l == NULL || (*p_l)->info >= e)
    {
        novo->prox = *p_l;
        novo->ant = NULL;
        if (*p_l != NULL) 
        {
            (*p_l)->ant = novo;
        }
        *p_l = novo;
        return 1;
    }

    //Se não for o caso do início, então percorre a lista
    while (aux->prox != NULL && aux->prox->info < e)
    {
        aux = aux->prox;
    }

    //Verifica se o valor já está na lista
    if (aux->info == e)
    {
        free(novo);
        return 0;
    }

    novo->prox = aux->prox;
    novo->ant = aux;

    if (aux->prox != NULL)
    {
        aux->prox->ant = novo;
    }

    aux->prox = novo;
    return 1;
}//insere_ordenado

//verifica se a lista está vazia e se eiste algum par desordenado
int ordenada (Lista *p_l)
{
    No_lista *aux = *p_l;

    if (*p_l == NULL || (*p_l)->prox == NULL)
    {
        printf("Lista vazia ou com um único elemento.\n");
        return 1;

    while (aux->prox != NULL)
    {
        if (aux->info > aux->prox->info)
        {
            printf("Par desordenado encontrado\n");
            return 0;
        }
        aux = aux->prox;
    }

    printf("Lista devidamente ordenada\n");
    return 1;
}//ordenada

//troca os valores na lista para ordena-la caso esteja em ordem errada e informa se a lista está vazia
void ordena(Lista *p_l)
{
    No_lista *i, *j;
    elem_t aux;

    if (*p_l == NULL || (*p_l)->prox == NULL)
    {
        printf("Lista vazia ou com um único elemento. Nada a ordenar.\n");
        return;
    }

    for (i = *p_l; i != NULL; i = i->prox)
    {
        for (j = i->prox; j != NULL; j = j->prox)
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

//remove o primeiro elemento da lista
int remove_inicio(Lista *p_l, elem_t *p_e)
{
    No_lista *aux_remove = *p_l;

    if (*p_l == NULL)
    {
        printf("Lista Vazia\n");
        return 0;
    }

    *p_e = aux_remove->info;
    *p_l = aux_remove->prox;

    if (*p_l != NULL)
    {
        (*p_l)->ant = NULL;
    }

    free(aux_remove);
    return 1;
}//remove_inicio

//remove o último elemento da lista
int remove_fim(Lista *p_l, elem_t *p_e)
{
    No_lista *aux = *p_l;

    if (*p_l == NULL)
    {
        printf("Lista Vazia\n");
        return 0;
    }

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
        *p_l = NULL; //Caso a lista tenha um único elemento
    }

    free(aux);
    return 1;
}//remove_fim

//remove um valor específico da lista
int remove_valor(Lista *p_l, elem_t e)
{
    No_lista *aux = *p_l;

    while (aux != NULL && aux->info != e)
    {
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        return 0; //Elemento não encontrado
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

void inverte(Lista *p_l)
{
    No_lista *aux = *p_l;
    No_lista *aux_b = NULL;

    if (*p_l == NULL)
    {
        printf("Lista vazia.\n");
        return;
    }

    //Inverte os ponteiros de cada nó
    while (aux != NULL)
    {
        aux_b = aux->prox;
        aux->prox = aux->ant;
        aux->ant = aux_b;
        aux = aux->ant; //Como os ponteiros foram invertidos, agora aux->ant aponta para o próximo nó
    }

    //Atualiza o início da lista
    if (aux_b != NULL)
    {
        *p_l = aux_b->ant; //O último nó será o novo início da lista
    }
}//inverte

void libera(Lista *p_l)
{
    No_lista *aux = *p_l;
    No_lista *temp;

    //Percorre a lista e libera os nós um por um
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    //Depois de liberar todos os nós, a lista deve ser nula
    *p_l = NULL;
}//libera

//Exibe o conteúdo da lista
void exibe(Lista *p_l)
{
    No_lista *aux = *p_l;
    
    if (*p_l == NULL) {
        printf("Lista vazia.\n");
        return;
    }

    printf("Conteúdo da lista: ");
    
    // Percorre a lista e imprime os valores dos nós
    while (aux != NULL)
    {
        printf("%d ", aux->info);
        aux = aux->prox;
    }
    printf("\n");
}//exibe