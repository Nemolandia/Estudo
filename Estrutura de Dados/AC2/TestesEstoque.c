
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include "EstoqueMercadoArvore.h"
#include "TestesEstoque.h"

long tempoAtualMs() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000L + ts.tv_nsec / 1000000L;
}

pid_t get_tid() {
    return syscall(SYS_gettid);
}

void registrarLog(const char *mensagem) {
    FILE *log = fopen("log_teste.txt", "a");
    if (!log) return;

    FILE *mem = fopen("/proc/self/statm", "r");
    long memoria = 0;
    if (mem) {
        fscanf(mem, "%ld", &memoria);
        fclose(mem);
    }

    time_t t = time(NULL);
    struct tm *tmp = localtime(&t);
    char buffer[64];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tmp);

    fprintf(log, "[%s] PID:%d | TID:%ld | MEM:%ld KB | %s\n", buffer, getpid(), (long)get_tid(), memoria * 4, mensagem);
    fclose(log);
}

void gerarItens(Item *buffer, int quantidade) {
    const char *tipos[] = {"fruta", "bebida", "doce", "salgado", "enlatado"};
    srand(time(NULL));
    for (int i = 0; i < quantidade; i++) {
        sprintf(buffer[i].nome, "Produto_%06d", i);
        strcpy(buffer[i].tipo, tipos[i % 5]);
        buffer[i].vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);
        sprintf(buffer[i].setor, "Setor_%c", 'A' + (i % 5));
    }
}

void *inserirLote(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    for (int i = args->inicio; i < args->fim; i++) {
        pthread_mutex_lock(args->mutex);
        inserirItem(args->raiz, args->itens[i]);
        pthread_mutex_unlock(args->mutex);
    }
    registrarLog("Thread finalizou inserções.");
    pthread_exit(NULL);
}

void testarInsercaoComThreads(int totalItens) {
    printf("\n[TESTE] Inserção com Threads (%d itens)\n", totalItens);
    Arvore raiz = NULL;
    Item *itens = malloc(totalItens * sizeof(Item));
    gerarItens(itens, totalItens);

    pthread_t threads[THREADS];
    ThreadArgs args[THREADS];
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    int porThread = totalItens / THREADS;
    long ini = tempoAtualMs();

    for (int i = 0; i < THREADS; i++) {
        args[i].raiz = &raiz;
        args[i].itens = itens;
        args[i].inicio = i * porThread;
        args[i].fim = (i == THREADS - 1) ? totalItens : (i + 1) * porThread;
        args[i].mutex = &mutex;
        pthread_create(&threads[i], NULL, inserirLote, &args[i]);
    }

    for (int i = 0; i < THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    long fim = tempoAtualMs();
    registrarLog("Todas as threads completaram inserção.");

    int totalNodos = contarNos(raiz);
    printf("Inserção completa. Total de nós: %d | Tempo total: %ld ms\n", totalNodos, fim - ini);

    liberarArvore(raiz);
    free(itens);
}

void testarGravacaoRemocaoComProcessos() {
    printf("\n[TESTE] Gravação e Remoção com Processos\n");

    if (fork() == 0) {
        registrarLog("Processo 1: organizando arquivos.");
        int qtd = 0;
        Arvore raiz = carregarItensEmArvore(&qtd);
        organizarEGravarArvore(raiz);
        liberarArvore(raiz);
        registrarLog("Processo 1: finalizado.");
        exit(0);
    }

    wait(NULL);

    if (fork() == 0) {
        registrarLog("Processo 2: removendo vencidos.");
        const char *arquivos[] = {"ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados"};
        for (int i = 0; i < 5; i++) {
            removerItensVencidosArvore(arquivos[i]);
            int qtd = contarItensNoArquivo(arquivos[i]);
            printf("Itens restantes em %s: %d\n", arquivos[i], qtd);
        }
        registrarLog("Processo 2: finalizado.");
        exit(0);
    }

    wait(NULL);
}

void testarTodasFuncoes(int qtd) {
    printf("\n========== INICIANDO TESTE FUNCIONAL (%d itens) ==========\n", qtd);
    criarListaItensSeNaoExistir();

    long ini = tempoAtualMs();
    int qtdLida = 0;
    Arvore raiz = carregarItensEmArvore(&qtdLida);
    long fim = tempoAtualMs();
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
    const char *arquivos[] = {"ListaFrutas", "ListaBebidas", "ListaDoces", "ListaSalgados", "ListaEnlatados"};
    for (int i = 0; i < 5; i++) {
        removerItensVencidosArvore(arquivos[i]);
        int qtd = contarItensNoArquivo(arquivos[i]);
        printf("[removerItensVencidosArvore] %s -> %d itens válidos\n", arquivos[i], qtd);
    }
    fim = tempoAtualMs();
    printf("[Remoção + contagem de arquivos] Tempo: %ld ms\n", fim - ini);

    liberarArvore(raiz);
    printf("===========================================================\n");
}