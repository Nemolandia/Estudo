/**************************************************************************************************
 * Nome: TAD - Árvore Binária de Busca (ABB) para Estoque de Supermercado
 * Descrição: Essa TAD foi criada com o objetivo de gerenciar o estoque de um supermercado,
 *          utilizando uma árvore binária de busca para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 09/05/2025
 *************************************************************************************************/

#include "EstoqueMercadoArvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void criarArvore(Arvore *raiz) {
    *raiz = NULL;
}
// Cria a árvore vazia
// Aloca memória para um novo nó e inicializa os campos
No* alocarNo(Item item) {
    No* novo = (No*)malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro ao alocar memoria para no.\n");
        exit(1);
    }
    // Inicializa o nó com os dados do item
    novo->item = item;
    novo->esq = novo->dir = NULL;
    return novo;
}
// Aloca memória para um novo nó e inicializa os campos
// Libera a memória da árvore recursivamente

void liberarArvore(Arvore raiz) {
    if (raiz != NULL) {
        liberarArvore(raiz->esq);
        liberarArvore(raiz->dir);
        free(raiz);
    }
}

void inserirItem(Arvore *raiz, Item item) {
    if (*raiz == NULL) {
        *raiz = alocarNo(item);
    } else {
        if (strcmp(item.nome, (*raiz)->item.nome) < 0) // Compara os nomes dos itens
            inserirItem(&(*raiz)->esq, item); // Insere na subárvore esquerda
        else
            inserirItem(&(*raiz)->dir, item); // Insere na subárvore direita
    }
}

void mostrarArvore(Arvore raiz) {
    if (raiz != NULL) {
        mostrarArvore(raiz->esq); // Mostra a subárvore esquerda
        printf("Nome: %s \n Tipo: %s \n Vencimento: %d \n Setor: %s\n",
               raiz->item.nome, raiz->item.tipo, raiz->item.vencimento, raiz->item.setor);
        mostrarArvore(raiz->dir); // Mostra a subárvore direita
    }
}

void organizarEGravarArvore(Arvore raiz) {
    const char *nomesArquivos[5] = {
        "ListaFrutasArvore", "ListaBebidasArvore", "ListaDocesArvore", "ListaSalgadosArvore", "ListaEnlatadosArvore"
    };
    if (raiz == NULL)
        return;
    organizarEGravarArvore(raiz->esq);
    // Verifica se o item tem vencimento maior que 0
    // e grava no arquivo correspondente
    if (raiz->item.vencimento > 0) {
        const char *nomeArquivo = NULL;
        // Verifica o tipo do item e define o nome do arquivo
        // Se o tipo não for encontrado, não grava
        if (strcmp(raiz->item.tipo, "fruta") == 0) nomeArquivo = nomesArquivos[0];
        else if (strcmp(raiz->item.tipo, "bebida") == 0) nomeArquivo = nomesArquivos[1];
        else if (strcmp(raiz->item.tipo, "doce") == 0) nomeArquivo = nomesArquivos[2];
        else if (strcmp(raiz->item.tipo, "salgado") == 0) nomeArquivo = nomesArquivos[3];
        else if (strcmp(raiz->item.tipo, "enlatado") == 0) nomeArquivo = nomesArquivos[4];
        if (nomeArquivo != NULL) {
            FILE *arquivo = fopen(nomeArquivo, "a"); // Modo de texto para anexar
            if (arquivo == NULL) {
                printf("Erro ao abrir o arquivo %s para gravacao.\n", nomeArquivo);
            } else {
                // Gravando os dados no formato legível como texto
                fprintf(arquivo, "Nome: %s \n Tipo: %s \n Vencimento: %d \n Setor: %s\n",
                        raiz->item.nome, raiz->item.tipo, raiz->item.vencimento, raiz->item.setor);
                fclose(arquivo); // Fecha o arquivo após a gravação
                printf("Gravado: %s em %s\n", raiz->item.nome, nomeArquivo); // Mensagem de confirmação
            }
        }
    }
    organizarEGravarArvore(raiz->dir); // Chama a função recursivamente para a subárvore direita
}

void removerItensVencidosArvore(const char *nomeArquivo) {
    FILE *arquivoOriginal = fopen(nomeArquivo, "rb"); // Modo binário para leitura
    FILE *arquivoTemp = fopen("temp", "wb"); // Modo binário para escrita
    Item item;
    if (arquivoOriginal == NULL || arquivoTemp == NULL) {
        printf("Erro ao abrir arquivos para remocao.\n");
        return;
    }
    while (fread(&item, sizeof(Item), 1, arquivoOriginal) == 1) {
        if (item.vencimento > 0) {
            fwrite(&item, sizeof(Item), 1, arquivoTemp); // Grava apenas itens não vencidos
        }
    }
    fclose(arquivoOriginal); // Fecha o arquivo original
    fclose(arquivoTemp); // Fecha o arquivo temporário
    remove(nomeArquivo); // Remove o arquivo original
    rename("temp", nomeArquivo); // Renomeia o arquivo temporário para o nome original
}

int contarItensNoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "rb"); // Modo binário para leitura
    if (arquivo == NULL) return 0; // Retorna 0 se o arquivo não existir
    int contador = 0;
    Item item;
    while (fread(&item, sizeof(Item), 1, arquivo) == 1) { // Lê os itens do arquivo
        contador++; // Incrementa o contador para cada item lido
    }
    fclose(arquivo);
    return contador;
}

Arvore carregarItensEmArvore(int *quantidadeLida) {
    FILE *arquivo = fopen("ListaItens", "rb"); // Modo binário para leitura
    if (arquivo == NULL) return NULL; // Retorna NULL se o arquivo não existir
    Arvore raiz = NULL;
    Item item; // Variável para armazenar o item lido
    *quantidadeLida = 0;
    // Lê os itens do arquivo e insere na árvore enquanto não atingir o limite
    // de itens a serem lidos ou o final do arquivo
    while (fread(&item, sizeof(Item), 1, arquivo) == 1 && *quantidadeLida < MAX_ITENS_INSERIR) {
        inserirItem(&raiz, item);
        (*quantidadeLida)++; 
    }
    fclose(arquivo);
    return raiz;
}

void criarListaItensSeNaoExistir() {
    FILE *arquivo = fopen("ListaItens", "rb"); // Modo binário para leitura
    if (arquivo != NULL) {
        fclose(arquivo); // Se o arquivo já existir, não faz nada
        return;
    }
    arquivo = fopen("ListaItens", "wb"); // Modo binário para escrita
    if (arquivo == NULL) {
        printf("Erro ao criar ListaItens.\n"); // Se não conseguir criar o arquivo, exibe mensagem de erro
        return;
    }
    Item item;
    const char *tipos[5] = {"fruta", "bebida", "doce", "salgado", "enlatado"}; // Tipos de itens
    srand(time(NULL));
    for (int i = 0; i < MAX_ITENS_INSERIR; i++) {
        // Preenche os campos do item com dados aleatórios
        int tipoIndex = i % 5;
        strcpy(item.tipo, tipos[tipoIndex]);
        sprintf(item.nome, "Item_%d", i + 1);
        item.vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30); // Vencimento aleatório entre 1 e 30, ou 0 para vencido
        sprintf(item.setor, "Setor %c", 'A' + tipoIndex);
        fwrite(&item, sizeof(Item), 1, arquivo); // Grava o item no arquivo
    }
    fclose(arquivo);
}

void mostrarConteudoArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r"); // Modo de texto para leitura
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomeArquivo); // Se não conseguir abrir o arquivo, exibe mensagem de erro
        return;
    }
    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) { // Lê linha por linha do arquivo
        printf("%s", linha); // Exibe a linha lida
    }
    fclose(arquivo); // Fecha o arquivo após a leitura
}