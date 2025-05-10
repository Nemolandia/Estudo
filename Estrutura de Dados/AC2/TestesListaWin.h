
#ifndef TESTES_LISTA_WIN_H
#define TESTES_LISTA_WIN_H

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#include <windows.h>
#include <psapi.h>

#include "EstoqueMercadoLista.h"

#define TESTE_PEQ 1000
#define TESTE_MED 50000
#define TESTE_GDE 100000
#define THREADS 4

typedef struct {
    Item **lista;
    Item *itens;
    int inicio;
    int fim;
    HANDLE mutex;
} ThreadArgs;

DWORD tempoAtualMs();
DWORD getMemoryUsageKB();
void registrarLog(const char *mensagem);
void gerarItens(Item *buffer, int quantidade);
DWORD WINAPI inserirLote(LPVOID arg);
void testarInsercaoComThreads(int totalItens);
void testarGravacaoRemocaoComProcessos();
void testarTodasFuncoes(int qtd);

#endif
