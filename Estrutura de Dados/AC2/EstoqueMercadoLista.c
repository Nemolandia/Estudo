#include "EstoqueMercadoLista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Função para alocar memória para um vetor de itens
Item* alocarItens(int quantidade)
{
    Item *itens = (Item*) malloc(sizeof(Item) * quantidade);
    
    if (itens == NULL)
    {
        printf("Erro: Falha ao alocar memoria para %d itens.\n", quantidade);
        exit(1); // Saída forçada caso não seja possível alocar memória
    }//if
    
    return itens;
}//alocarItens

// Função de comparação para ordenar itens por vencimento (menor para maior)
int compararPorVencimento(const void *a, const void *b)
{
    return ((Item *)a)->vencimento - ((Item *)b)->vencimento;
}//compararPorVencimento

// Função para contar quantos itens tem em um arquivo
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
}//contarItensNoArquivo

// Função para remover itens vencidos (vencimento == 0)
void removerItensVencidos(const char *nomeArquivo)
{
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb");
    FILE *arquivoTemp = fopen("temp.bin", "wb");
    Item itemAtual;

    if (arquivoOriginal == NULL || arquivoTemp == NULL)
    {
        return;
    }//if

    while (fread(&itemAtual, sizeof(Item), 1, arquivoOriginal) == 1)
    {
        if (itemAtual.vencimento > 0)
        {
            fwrite(&itemAtual, sizeof(Item), 1, arquivoTemp);
        }//if
    }//while

    fclose(arquivoOriginal);
    fclose(arquivoTemp);

    remove(nomeArquivo);
    rename("temp.bin", nomeArquivo);
}//removerItensVencidos

// Função para mostrar o conteúdo de um arquivo
void mostrarArquivo(const char *nomeArquivo)
{
    FILE *arquivo = fopen(nomeArquivo, "rb");
    Item item;

    if (arquivo == NULL)
    {
        printf("Arquivo %s nao encontrado.\n", nomeArquivo);
        return;
    }//if

    printf("Conteudo do arquivo %s:\n", nomeArquivo);

    while (fread(&item, sizeof(Item), 1, arquivo) == 1)
    {
        printf("Nome: %s | Tipo: %s | Vencimento: %d | Setor: %s\n",
               item.nome, item.tipo, item.vencimento, item.setor);
    }//while
    fclose(arquivo);
}//mostrarArquivo

// Função para carregar os itens da ListaItens
void carregarItensDaLista(Item **listaItens, int *quantidadeLida)
{
    FILE *arquivo = fopen("ListaItens", "rb");

    if (arquivo == NULL)
    {
        *listaItens = NULL;
        *quantidadeLida = 0;
        return;
    }//if

    *listaItens = alocarItens(MAX_ITENS_INSERIR);

    *quantidadeLida = fread(*listaItens, sizeof(Item), MAX_ITENS_INSERIR, arquivo);

    fclose(arquivo);
}//carregarItensDaLista

// Função para organizar e gravar os itens no arquivo correto de acordo com o tipo
void organizarEGravarItens(Item *listaItens, int quantidadeLida)
{
    int indiceItem;
    int quantidadeAtualNoArquivo;
    FILE *arquivoDestino;
    const char *nomeArquivos[5] = {"ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados"};
    const char *nomeArquivoDestino;

    qsort(listaItens, quantidadeLida, sizeof(Item), compararPorVencimento);

    for (indiceItem = 0; indiceItem < quantidadeLida; indiceItem++)
    {
        if (listaItens[indiceItem].vencimento == 0)
        {
            continue;
        }//if

        nomeArquivoDestino = NULL;
        if (strcmp(listaItens[indiceItem].tipo, "fruta") == 0)
        {
            nomeArquivoDestino = nomeArquivos[0];
        }//if
        else if (strcmp(listaItens[indiceItem].tipo, "bebida") == 0)
        {
            nomeArquivoDestino = nomeArquivos[1];
        }//else if
        else if (strcmp(listaItens[indiceItem].tipo, "doce") == 0)
        {
            nomeArquivoDestino = nomeArquivos[2];
        }//else if
        else if (strcmp(listaItens[indiceItem].tipo, "salgado") == 0)
        {
            nomeArquivoDestino = nomeArquivos[3];
        }//else if
        else if (strcmp(listaItens[indiceItem].tipo, "enlatado") == 0)
        {
            nomeArquivoDestino = nomeArquivos[4];
        }//else if

        if (nomeArquivoDestino == NULL)
        {
            continue; // Se não encontrar o tipo correto, passa para o próximo item
        }//if

        quantidadeAtualNoArquivo = contarItensNoArquivo(nomeArquivoDestino);

        if (quantidadeAtualNoArquivo >= MAX_ESTOQUE)
        {
            printf("Estoque cheio para tipo %s (%s). Não há espaço para mais itens.\n", listaItens[indiceItem].tipo, nomeArquivoDestino);
            continue;
        }//if

        arquivoDestino = fopen(nomeArquivoDestino, "ab");

        if (arquivoDestino == NULL)
        {
            printf("Erro ao abrir o arquivo %s para escrita.\n", nomeArquivoDestino);
            continue;
        }//if

        if (fwrite(&listaItens[indiceItem], sizeof(Item), 1, arquivoDestino) != 1)
        {
            printf("Erro ao gravar item no arquivo %s.\n", nomeArquivoDestino);
            fclose(arquivoDestino);
            continue;
        }//if

        fclose(arquivoDestino);
    }//for
}//organizarEGravarItens

// Função para criar a lista de itens automaticamente caso nao exista
void criarListaItensSeNaoExistir()
{
    FILE *arquivo;
    int i;
    Item novoItem;

    arquivo = fopen("ListaItens", "rb");
    
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

    // Gerando itens com nomes aleatórios e vencimentos entre 1 e 30 dias
    for (i = 0; i < MAX_ITENS_INSERIR; i++)
    {
        int tipo = i % 5;

        switch (tipo)
        {
            case 0:
                strcpy(novoItem.tipo, "fruta");
                break;
            case 1:
                strcpy(novoItem.tipo, "bebida");
                break;
            case 2:
                strcpy(novoItem.tipo, "doce");
                break;
            case 3:
                strcpy(novoItem.tipo, "salgado");
                break;
            case 4:
                strcpy(novoItem.tipo, "enlatado");
                break;
        }//switch
        
        sprintf(novoItem.nome, "Item_%d_%d", tipo, i + 1); // Nome aleatório no formato Item_tipo_indice
        novoItem.vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);  // Vencimento entre 1 e 30 dias, com alguns itens vencendo
        sprintf(novoItem.setor, "Setor %c", 'A' + tipo);  // Setor baseado no tipo

        fwrite(&novoItem, sizeof(Item), 1, arquivo);
    }//for

    fclose(arquivo);
}//criarListaItensSeNaoExistir