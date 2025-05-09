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
    }//if

    while (fscanf(arquivoOriginal, "%49[^;];%19[^;];%d;%9[^\n]\n", item.nome, item.tipo, &item.vencimento, item.setor) == 4)
    {
        if (item.vencimento > 0)
        {
            fprintf(arquivoTemp, "%s;%s;%d;%s\n", item.nome, item.tipo, item.vencimento, item.setor);
        }//if
    }//while

    fclose(arquivoOriginal);
    fclose(arquivoTemp);
    remove(nomeArquivo);
    rename("temp.txt", nomeArquivo);
}// removerItensVencidos

// Mostra conteúdo de um arquivo
void mostrarArquivo(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    Item item;

    if (arquivo == NULL) {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }//if

    printf("Conteudo do arquivo %s:\n", nomeArquivo);
    while (fscanf(arquivo, "%49[^;];%19[^;];%d;%9[^\n]\n", item.nome, item.tipo, &item.vencimento, item.setor) == 4)
    {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }//while

    fclose(arquivo);
}// mostrarArquivo

// Carrega itens da ListaItens para uma lista dinâmica
Item* carregarItensDaLista(int *quantidadeLida)
{
    FILE *arquivo = fopen("ListaItens", "rb");
    Item *inicio = NULL;
    Item *fim = NULL;
    Item temp;
    *quantidadeLida = 0;

    if (arquivo == NULL)
    {
        return NULL;
    }//if

    while (fread(&temp, sizeof(Item), 1, arquivo) == 1 && *quantidadeLida < MAX_ITENS_INSERIR)
    {
        Item *novo = alocarItem();
        *novo = temp;
        novo->prox = NULL;

        if (inicio == NULL)
        {
            inicio = novo;
        }//if
        else
        {
            fim->prox = novo;
        }//else

        fim = novo;
        (*quantidadeLida)++;
    }//while

    fclose(arquivo);
    return inicio;
}// carregarItensDaLista

// Organiza e grava itens por tipo, ordenados por vencimento
void organizarEGravarItens(Item *listaItens) {
    Item *atual = listaItens;
    FILE *arquivo;
    const char *nomesArquivos[5] = {
        "ListaFrutasLista", "ListaBebidasLista", "ListaDocesLista", "ListaSalgadosLista", "ListaEnlatadosLista"
    };

    // Primeiro, contar o número de itens para cada tipo
    int quantidade = 0;

    while (atual != NULL) {
        quantidade++;
        atual = atual->prox;
    }

    // Organize os itens por vencimento
    Item *itensArray = (Item *)malloc(sizeof(Item) * quantidade);
    atual = listaItens;
    int i = 0;
    while (atual != NULL) {
        itensArray[i++] = *atual;
        atual = atual->prox;
    }

    // Ordenar os itens por vencimento
    qsort(itensArray, quantidade, sizeof(Item), compararPorVencimento);

    // Agora, gravar os itens ordenados nos arquivos correspondentes
    for (int j = 0; j < quantidade; j++) {
        Item *item = &itensArray[j];
        
        if (item->vencimento == 0)
            continue; // Não grava itens vencidos

        const char *nomeArquivo = NULL;
        if (strcmp(item->tipo, "fruta") == 0)
            nomeArquivo = nomesArquivos[0];
        else if (strcmp(item->tipo, "bebida") == 0)
            nomeArquivo = nomesArquivos[1];
        else if (strcmp(item->tipo, "doce") == 0)
            nomeArquivo = nomesArquivos[2];
        else if (strcmp(item->tipo, "salgado") == 0)
            nomeArquivo = nomesArquivos[3];
        else if (strcmp(item->tipo, "enlatado") == 0)
            nomeArquivo = nomesArquivos[4];

        if (nomeArquivo != NULL) {
            arquivo = fopen(nomeArquivo, "a");
            if (arquivo != NULL) {
                fprintf(arquivo, "%s;%s;%d;%s\n", item->nome, item->tipo, item->vencimento, item->setor);
                fclose(arquivo);
            } else {
                printf("Erro ao abrir arquivo %s.\n", nomeArquivo);
            }
        }
    }

    // Libere a memória do array de itens temporário
    free(itensArray);
}// organizarEGravarItens

// Cria a ListaItens automaticamente se não existir
void criarListaItensSeNaoExistir()
{
    FILE *arquivo = fopen("ListaItens", "rb");
    Item item;
    int i;

    if (arquivo != NULL)
    {
        fclose(arquivo);
        return;
    }//if

    arquivo = fopen("ListaItens", "wb");

    if (arquivo == NULL)
    {
        printf("Erro ao criar ListaItens.\n");
        return;
    }//if

    srand(time(NULL));

    for (i = 0; i < MAX_ITENS_INSERIR; i++)
    {
        int tipoIndex = i % 5;
        const char *tipos[5] = {"fruta", "bebida", "doce", "salgado", "enlatado"};

        strcpy(item.tipo, tipos[tipoIndex]);
        sprintf(item.nome, "Item_%d", i + 1);
        item.vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);
        sprintf(item.setor, "Setor %c", 'A' + tipoIndex);

        fwrite(&item, sizeof(Item), 1, arquivo);
    }//for

    fclose(arquivo);
}//criarListaItensSeNaoExistir