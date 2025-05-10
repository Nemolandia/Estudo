
#ifndef TESTES_ESTOQUE_H
#define TESTES_ESTOQUE_H

#include "EstoqueMercadoArvore.h"

#define TESTE_PEQ 1000
#define TESTE_MED 50000
#define TESTE_GDE 100000
#define THREADS 4
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#include <windows.h>
#include <psapi.h>
#include <pthread.h>

typedef struct {
    Arvore *raiz;
    Item *itens;
    int inicio;
    int fim;
    pthread_mutex_t *mutex;
} ThreadArgs;

long tempoAtualMs();
DWORD get_tid();
void registrarLog(const char *mensagem);
void gerarItens(Item *buffer, int quantidade);
void *inserirLote(void *arg);
void testarInsercaoComThreads(int totalItens);
void testarTodasFuncoes(int qtd);
int contarNos(Arvore raiz);

#endif
