/**************************************************************************************************
 * Nome: Cabecalho do TAD - Lista Dinâmica para Estoque de Supermercado
 * Descrição: Cabecalho do TAD que define a estrutura de dados e as funções para manipulação da Lista Dinâmica.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 09/05/2025
 *************************************************************************************************/

#ifndef MERCADO_H
#define MERCADO_H

#define MAX_ITENS_INSERIR 500       // Quantidade de itens a serem inseridos por vez
#define MAX_ESTOQUE 500             // Quantidade máxima de itens em cada arquivo de estoque

// Estrutura que representa um item no mercado
typedef struct Item
{
    char nome[50];    // Nome do item
    char tipo[20];    // Tipo do item (fruta, bebida, doce, salgado, enlatado)
    int vencimento;    // Vencimento em dias (0 = vencido)
    char setor[10];   // Setor onde o item estará (Setor A, Setor B, etc.)
    struct Item *prox;  // Ponteiro para o próximo item (lista dinâmica)
} Item;

// Funções principais
Item* alocarItem();
void liberarLista(Item *lista);
int compararPorVencimento(const void *a, const void *b);
int contarItensNoArquivo(const char *nomeArquivo);
void removerItensVencidos(const char *nomeArquivo);
void mostrarArquivo(const char *nomeArquivo);
Item* carregarItensDaLista(int *quantidadeLida);
void organizarEGravarItens(Item *listaItens);
void criarListaItensSeNaoExistir();

#endif // MERCADO_H