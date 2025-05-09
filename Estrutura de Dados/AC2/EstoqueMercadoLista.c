#include "EstoqueMercadoLista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Aloca memória para um novo item
Item* alocarItem()
{
    Item *novoItem = (Item*) malloc(sizeof(Item));

    if (novoItem == NULL)
    {
        printf("Erro: falha ao alocar memoria para item.\n");
        exit(1);
    }//if
    novoItem->prox = NULL;
    return novoItem;
}//alocarItem

// Libera toda a lista
void liberarLista(Item *lista)
{
    Item *atual = lista;
    Item *proxItem;

    while (atual != NULL)
    {
        proxItem = atual->prox;
        free(atual);
        atual = proxItem;
    }//while
}//liberarLista

// Compara por vencimento (usado no qsort se necessário)
int compararPorVencimento(const void *a, const void *b)
{
    return ((Item *)a)->vencimento - ((Item *)b)->vencimento;
}// compararPorVencimento

// Conta itens num arquivo binário
int contarItensNoArquivo(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    int contador = 0;
    Item itemLido;

    if (arquivo == NULL)
    {
        return 0;
    }//if

    while (fread(&itemLido, sizeof(Item), 1, arquivo) == 1)
    {
        contador++;
    }//while

    fclose(arquivo);
    return contador;
}// contarItensNoArquivo

// Remove itens com vencimento 0
void removerItensVencidos(const char *nomeArquivo)
{
    FILE *arquivoOriginal = fopen(nomeArquivo, "r");
    FILE *arquivoTemp = fopen("temp.txt", "w");
    Item item;

    if (arquivoOriginal == NULL || arquivoTemp == NULL)
    {
        printf("Erro ao abrir arquivos para remover vencidos.\n");
        return;
    }

    while (fscanf(arquivoOriginal, "%49[^;];%19[^;];%d;%9[^\n]\n", item.nome, item.tipo, &item.vencimento, item.setor) == 4)
    {
        if (item.vencimento > 0)
        {
            fprintf(arquivoTemp, "%s;%s;%d;%s\n", item.nome, item.tipo, item.vencimento, item.setor);
        }
    }

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    remove(nomeArquivo);
    rename("temp.txt", nomeArquivo);
}// removerItensVencidos

// Mostra conteúdo de um arquivo
void mostrarArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb");
    Item item;

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }

    printf("Conteudo do arquivo %s:\n", nomeArquivo);
    while (fscanf(arquivo, "%49[^;];%19[^;];%d;%9[^\n]\n", item.nome, item.tipo, &item.vencimento, item.setor) == 4) {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }

    fclose(arquivo);
}

// Carrega itens da ListaItens para uma lista dinâmica
Item* carregarItensDaLista(int *quantidadeLida) {
    FILE *arquivo = fopen("ListaItens", "rb");
    Item *inicio = NULL;
    Item *fim = NULL;
    Item temp;
    *quantidadeLida = 0;

    if (arquivo == NULL) {
        return NULL;
    }

    while (fread(&temp, sizeof(Item), 1, arquivo) == 1 && *quantidadeLida < MAX_ITENS_INSERIR) {
        Item *novo = alocarItem();
        *novo = temp;
        novo->prox = NULL;

        if (inicio == NULL) {
            inicio = novo;
        } else {
            fim->prox = novo;
        }

        fim = novo;
        (*quantidadeLida)++;
    }

    fclose(arquivo);
    return inicio;
}

// Organiza e grava itens por tipo
void organizarEGravarItens(Item *listaItens) {
    Item *atual = listaItens;
    FILE *arquivo;
    const char *nomesArquivos[5] = {
        "ListaFrutasLista", "ListaBebidasLista", "ListaDocesLista", "ListaSalgadosLista", "ListaEnlatadosLista"
    };

    while (atual != NULL)
    {
        if (atual->vencimento == 0)
        {
            atual = atual->prox;
            continue;
        }//if

        const char *nomeArquivo = NULL;

        if (strcmp(atual->tipo, "fruta") == 0)
        {
            nomeArquivo = nomesArquivos[0];
        }//if
        else if (strcmp(atual->tipo, "bebida") == 0)
        {
             nomeArquivo = nomesArquivos[1];
        }//else if
        else if (strcmp(atual->tipo, "doce") == 0)
        {
            nomeArquivo = nomesArquivos[2];
        }//else if
        else if (strcmp(atual->tipo, "salgado") == 0)
        {
            nomeArquivo = nomesArquivos[3];
        }//else if
        else if (strcmp(atual->tipo, "enlatado") == 0)
        {
            nomeArquivo = nomesArquivos[4];
        }//else if

        if (nomeArquivo != NULL)
        {
            int quantidadeAtual = contarItensNoArquivo(nomeArquivo);

            if (quantidadeAtual >= MAX_ESTOQUE)
            {
                printf("Estoque cheio para %s. Item %s nao adicionado.\n", atual->tipo, atual->nome);
            }//if
            else
            {
                arquivo = fopen(nomeArquivo, "a");
                if (arquivo != NULL)
                {
                    fprintf(arquivo, "%s;%s;%d;%s\n", atual->nome, atual->tipo, atual->vencimento, atual->setor);
                    fclose(arquivo);
                }//if
                else
                {
                    printf("Erro ao abrir arquivo %s.\n", nomeArquivo);
                }//else
            }//else
        }//if

        atual = atual->prox;
    }//while
}// organizarEGravarItens

// Cria a ListaItens automaticamente se não existir
void criarListaItensSeNaoExistir()
{
    FILE *arquivo = fopen("ListaItens", "rb");
    Item item;

    if (arquivo != NULL)
    {
        fclose(arquivo);
        return;
    }

    arquivo = fopen("ListaItens", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao criar ListaItens.\n");
        return;
    }

    srand(time(NULL));

    const char *tipos[5] = {"fruta", "bebida", "doce", "salgado", "enlatado"};
    int contadores[5] = {0};  // contador para cada tipo

    for (int i = 0; i < MAX_ITENS_INSERIR; i++)
    {
        int tipoIndex = i % 5;
        contadores[tipoIndex]++; // incrementa o contador daquele tipo

        strcpy(item.tipo, tipos[tipoIndex]);
        sprintf(item.nome, "%s_%d", tipos[tipoIndex], contadores[tipoIndex]);  // nome específico por tipo
        item.vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);
        sprintf(item.setor, "Setor %c", 'A' + tipoIndex);

        fwrite(&item, sizeof(Item), 1, arquivo);
    }

    fclose(arquivo);
}//criarListaItensSeNaoExistir