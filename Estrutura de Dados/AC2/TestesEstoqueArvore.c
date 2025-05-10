#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#include <windows.h>
#include <psapi.h>
#include <pthread.h>
#include <inttypes.h> // para usar %zu com size_t
#include "EstoqueMercadoArvore.h"
#include "TestesEstoqueArvore.h"

long tempoAtualMs() {
    return GetTickCount64();
}

DWORD get_tid() {
    return GetCurrentThreadId();
}

void registrarLog(const char *mensagem) {
    FILE *log;
    PROCESS_MEMORY_COUNTERS memCounters;
    SIZE_T memoria;
    time_t t;
    struct tm *tmp;
    char buffer[64];

    log = fopen("log_teste.txt", "a");
    if (!log) return;

    GetProcessMemoryInfo(GetCurrentProcess(), &memCounters, sizeof(memCounters));
    memoria = memCounters.WorkingSetSize / 1024;

    t = time(NULL);
    tmp = localtime(&t);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tmp);

    fprintf(log, "[%s] PID:%lu | TID:%lu | MEM:%lu KB | %s\n",
            buffer, GetCurrentProcessId(), get_tid(), (unsigned long)memoria, mensagem);
    fclose(log);
}

void gerarItens(Item *buffer, int quantidade) {
    int i;
    const char *tipos[] = {"fruta", "bebida", "doce", "salgado", "enlatado"};
    srand((unsigned int)time(NULL));

    for (i = 0; i < quantidade; i++) {
        sprintf(buffer[i].nome, "Produto_%06d", i);
        strcpy(buffer[i].tipo, tipos[i % 5]);
        buffer[i].vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);
        sprintf(buffer[i].setor, "Setor_%c", 'A' + (i % 5));
    }
}

void *inserirLote(void *arg) {
    ThreadArgs *args;
    int i;

    args = (ThreadArgs *)arg;

    for (i = args->inicio; i < args->fim; i++) {
        pthread_mutex_lock(args->mutex);
        inserirItem(args->raiz, args->itens[i]);
        pthread_mutex_unlock(args->mutex);
    }

    registrarLog("Thread finalizou inserções.");
    return NULL;
}

void testarInsercaoComThreads(int totalItens) {
    Arvore raiz = NULL;
    Item *itens;
    pthread_t threads[THREADS];
    ThreadArgs args[THREADS];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    int i, porThread, totalNodos;
    long ini, fim;

    printf("\n[TESTE] Inserção com Threads (%d itens)\n", totalItens);
    itens = malloc(totalItens * sizeof(Item));
    gerarItens(itens, totalItens);

    porThread = totalItens / THREADS;
    ini = tempoAtualMs();

    for (i = 0; i < THREADS; i++) {
        args[i].raiz = &raiz;
        args[i].itens = itens;
        args[i].inicio = i * porThread;
        args[i].fim = (i == THREADS - 1) ? totalItens : (i + 1) * porThread;
        args[i].mutex = &mutex;
        pthread_create(&threads[i], NULL, inserirLote, &args[i]);
    }

    for (i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    fim = tempoAtualMs();
    registrarLog("Todas as threads completaram inserção.");

    totalNodos = contarNos(raiz);
    printf("Inserção completa. Total de nós: %d | Tempo total: %ld ms\n", totalNodos, fim - ini);

    liberarArvore(raiz);
    free(itens);
}

void testarTodasFuncoes(int qtd) {
    long ini, fim;
    int i, qtdLida, qtdArquivo;
    Arvore raiz;
    const char *arquivos[] = {"ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados"};

    printf("\n========== INICIANDO TESTE FUNCIONAL (%d itens) ==========\n", qtd);
    criarListaItensSeNaoExistir();

    ini = tempoAtualMs();
    qtdLida = 0;
    raiz = carregarItensEmArvore(&qtdLida);
    fim = tempoAtualMs();
    printf("[carregarItensEmArvore] Itens lidos: %d | Tempo: %ld ms\n", qtdLida, fim - ini);

    ini = tempoAtualMs();
    mostrarArvore(raiz);
    fim = tempoAtualMs();
    printf("[mostrarArvore] Tempo: %ld ms\n", fim - ini);

    ini = tempoAtualMs();
    organizarEGravarArvore(raiz);
    fim = tempoAtualMs();
    printf("[organizarEGravarArvore] Tempo: %ld ms\n", fim - ini);

    ini = tempoAtualMs();
    for (i = 0; i < 5; i++) {
        removerItensVencidosArvore(arquivos[i]);
        qtdArquivo = contarItensNoArquivo(arquivos[i]);
        printf("[removerItensVencidosArvore] %s -> %d itens válidos\n", arquivos[i], qtdArquivo);
    }
    fim = tempoAtualMs();
    printf("[Remoção + contagem de arquivos] Tempo: %ld ms\n", fim - ini);

    liberarArvore(raiz);
    printf("===========================================================\n");
}
