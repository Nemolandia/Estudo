#ifndef MERCADO_H
#define MERCADO_H

#define MAX_ITENS_INSERIR 500       // Quantidade de itens a serem inseridos por vez
#define MAX_ESTOQUE 450             // Quantidade máxima de itens em cada arquivo de estoque

// Estrutura que representa um item no mercado
typedef struct
{
    char nome[50];       // Nome do item
    char tipo[20];       // Tipo do item (fruta, bebida, doce, salgado, enlatado)
    int vencimento;      // Vencimento em dias (0 = vencido)
    char setor[10];      // Setor onde o item estará (Setor A, Setor B, etc.)
} Item;

// Função para alocar memória para os itens
Item* alocarItens(int quantidade);

// Função para comparar itens por vencimento (ordem crescente)
int compararPorVencimento(const void *a, const void *b);

// Função para contar quantos itens há em um arquivo
int contarItensNoArquivo(const char *nomeArquivo);

// Função para remover itens vencidos de um arquivo
void removerItensVencidos(const char *nomeArquivo);

// Função para mostrar o conteúdo de um arquivo
void mostrarArquivo(const char *nomeArquivo);

// Função para carregar os itens do arquivo ListaItens
void carregarItensDaLista(Item **listaItens, int *quantidadeLida);

// Função para organizar os itens e gravá-los nos arquivos correspondentes
void organizarEGravarItens(Item *listaItens, int quantidadeLida);

// Função para criar a lista de itens automaticamente, se o arquivo não existir
void criarListaItensSeNaoExistir();

#endif // MERCADO_H