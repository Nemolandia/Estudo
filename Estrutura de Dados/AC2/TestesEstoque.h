
#ifndef TESTES_ESTOQUE_H
#define TESTES_ESTOQUE_H

#include "EstoqueMercadoArvore.h"

#define TESTE_PEQ 1000
#define TESTE_MED 50000
#define TESTE_GDE 100000
#define THREADS 4

typedef struct {
    Arvore *raiz;
    Item *itens;
    int inicio;
    int fim;
    pthread_mutex_t *mutex;
} ThreadArgs;

long tempoAtualMs();
pid_t get_tid();
void registrarLog(const char *mensagem);
void gerarItens(Item *buffer, int quantidade);
void *inserirLote(void *arg);
void testarInsercaoComThreads(int totalItens);
void testarGravacaoRemocaoComProcessos();
void testarTodasFuncoes(int qtd);

#endif
