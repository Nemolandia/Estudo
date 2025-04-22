/*Execução da lista dinâmica para AC2 de estoque de mercado;
Autor: Jeovanni Conservani Silva;
RA: 190691.*/

#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoLista.h"

No_lista *aloca_memoria()
{
    No_lista *novo = (No_lista *)malloc(sizeof(No_lista));

    if (novo == NULL) {
        printf("Memoria insuficiente!\n");
        exit(1);
    }
    return novo;
}//aloca

void cria(Lista *p_l)
{
    *p_l = NULL;
}//cria

int vazia(Lista *p_l)
{
    return (*p_l == NULL);
}//vazia

void insere_inicio(Lista *p_l, elem_t e)
{
    No_lista *novo = aloca_memoria();
    novo->info = e; //Atribui o valor ao novo nó
    novo->prox = *p_l; //O novo nó aponta para o nó que antes estava no início
    *p_l = novo; //A lista agora começa no novo nó
}//insere_inicio

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
        No_lista *aux = *p_l;

        while (aux->prox != NULL)
        {
            aux = aux->prox; //Encontra o último nó
        }
        aux->prox = novo; //Aponta o último nó para o novo nó
    }
}//insere_fim

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
    No_lista *aux = *p_l;

    while (aux->prox != NULL && aux->prox->info < e)
    {
        aux = aux->prox; // Percorre a lista até encontrar a posição correta
    }

    if (aux->prox != NULL && aux->prox->info == e)
    {
        free(novo); // Se o elemento já existe, não insere e libera a memória
        return 0;
    }

    novo->prox = aux->prox;
    aux->prox = novo; // Insere o novo nó na posição correta
    return 1;
}//insere_ordenado

int ordenada(Lista *p_l)
{
    if (*p_l == NULL || (*p_l)->prox == NULL)
    {
        return 1; // Lista vazia ou com um único elemento está ordenada
    }

    No_lista *aux = *p_l;

    while (aux->prox != NULL)
    {
        if (aux->info > aux->prox->info)
        {
            return 0; // Se encontrar um par desordenado, retorna 0
        }
        aux = aux->prox;
    }
    return 1; // Se percorreu toda a lista e não encontrou desordem, retorna 1
}//ordenada

void ordena(Lista *p_l)
{
    if (*p_l == NULL || (*p_l)->prox == NULL)
    {
        return; // Lista vazia ou com um único elemento não precisa ser ordenada
    }

    No_lista *i, *j;
    elem_t aux;

    for (i = *p_l; i != NULL; i = i->prox)
    {
        for (j = i->prox; j != NULL; j = j->prox)
        {
            if (i->info > j->info)
            {
                // Troca os valores de i e j
                aux = i->info;
                i->info = j->info;
                j->info = aux;
            }
        }
    }
}//ordena

int remove_inicio(Lista *p_l, elem_t *p_e)
{
    if (vazia(p_l))
    {
        return 0; // Se a lista estiver vazia, não há o que remover
    }

    No_lista *aux = *p_l;
    *p_e = aux->info; // Armazena o valor do elemento a ser removido
    *p_l = aux->prox; // A lista agora começa no próximo nó
    free(aux); // Libera a memória do nó removido

    return 1;
}//remove_inicio

int remove_fim(Lista *p_l, elem_t *p_e)
{
    if (vazia(p_l))
    {
        return 0; // Se a lista estiver vazia, não há o que remover
    }

    No_lista *aux = *p_l;

    if (aux->prox == NULL)
    { // Se a lista tem apenas um elemento
        *p_e = aux->info;
        *p_l = NULL; // A lista ficará vazia
        free(aux);
        return 1;
    }

    // Caso a lista tenha mais de um elemento
    while (aux->prox->prox != NULL)
    {
        aux = aux->prox; // Encontra o penúltimo nó
    }

    No_lista *ultimo = aux->prox;
    *p_e = ultimo->info;
    aux->prox = NULL; // O penúltimo nó agora será o último
    free(ultimo); // Libera a memória do último nó

    return 1;
}//remove_fim

int remove_valor(Lista *p_l, elem_t e)
{
    No_lista *aux = *p_l, *ant = NULL;

    // Percorre a lista até encontrar o valor
    while (aux != NULL && aux->info != e)
    {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL)
    {
        return 0; // Valor não encontrado
    }

    if (ant == NULL)
    { // Se for o primeiro nó
        *p_l = aux->prox;
    } else { // Se for um nó intermediário ou final
        ant->prox = aux->prox;
    }

    free(aux); // Libera a memória do nó removido
    return 1;
}//remove_valor

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
}//inverte

void salvar_em_arquivo(Lista *p_l, const char *nome_arquivo)
{
    FILE *arquivo = fopen(Lista_mercadoria, "w");

    No_lista *aux = *p_l;

    if (arquivo == NULL)
    {
        printf("ERRO - Arquivo inexistente\n");
        return;
    }

    if (vazia(p_l))
    {
        printf("Lista vazia, nada a salvar.\n");
        fclose(arquivo); // Fecha o arquivo se a lista estiver vazia
        return; // Retorna para não tentar salvar uma lista vazia
    }

    while (aux != NULL)
    {
        fprintf(arquivo, "%i\n", aux->info); // Salva o valor do nó no arquivo
        aux = aux->prox;
    }
    fclose(arquivo); // Fecha o arquivo após salvar os dados
}//salvar_em_arquivo

void carregar_do_arquivo(Lista *p_l, const char *nome_arquivo)
{
    FILE *arquivo = fopen(Lista_mercadoria, "r");

    elem_t item;

    if (arquivo == NULL)
    {
        printf"ERRO - Arquivo inexistente\n");
        return; // Retorna se o arquivo não puder ser aberto
    }

    while (fscanf(arquivo, "%i", &item) == 1)
    {
        insere_fim (p_l, item); // Insere o item no final da lista
    }
    fclose(arquivo); // Fecha o arquivo após carregar os dados
}//carregar_do_arquivo