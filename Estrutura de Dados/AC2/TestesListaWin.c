
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif
#include <windows.h>
#include <psapi.h>

#include "EstoqueMercadoLista.h"
#include "TestesListaWin.h"

DWORD tempoAtualMs() {
    return GetTickCount64();
}

DWORD getMemoryUsageKB() {
    PROCESS_MEMORY_COUNTERS pmc;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc))) {
        return (DWORD)(pmc.WorkingSetSize / 1024);
    }
    return 0;
}

void registrarLog(const char *mensagem) {
    FILE *log = fopen("log_lista_win.txt", "a");
    if (!log) return;

    SYSTEMTIME st;
    GetLocalTime(&st);
    DWORD memKB = getMemoryUsageKB();

    fprintf(log, "[%04d-%02d-%02d %02d:%02d:%02d] PID:%lu | MEM:%lu KB | %s\n",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond,
        GetCurrentProcessId(), memKB, mensagem);

    fclose(log);
}

void gerarItens(Item *buffer, int quantidade) {
    const char *tipos[] = {"fruta", "bebida", "doce", "salgado", "enlatado"};
    srand((unsigned int)time(NULL));
    for (int i = 0; i < quantidade; i++) {
        sprintf(buffer[i].nome, "Item_%06d", i);
        strcpy(buffer[i].tipo, tipos[i % 5]);
        buffer[i].vencimento = (i % 10 == 0) ? 0 : (1 + rand() % 30);
        sprintf(buffer[i].setor, "Setor_%c", 'A' + (i % 5));
        buffer[i].prox = NULL;
    }
}

DWORD WINAPI inserirLote(LPVOID arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    for (int i = args->inicio; i < args->fim; i++) {
        Item *novo = alocarItem();
        *novo = args->itens[i];
        WaitForSingleObject(args->mutex, INFINITE);
        novo->prox = *(args->lista);
        *(args->lista) = novo;
        ReleaseMutex(args->mutex);
    }
    registrarLog("Thread finalizou inserções na lista.");
    return 0;
}

void testarInsercaoComThreads(int totalItens) {
    printf("\n[TESTE] Inserção com Threads (%d itens)\n", totalItens);
    Item *lista = NULL;
    Item *itens = malloc(totalItens * sizeof(Item));
    gerarItens(itens, totalItens);

    HANDLE threads[THREADS];
    ThreadArgs args[THREADS];
    HANDLE mutex = CreateMutex(NULL, FALSE, NULL);

    int porThread = totalItens / THREADS;
    DWORD ini = tempoAtualMs();

    for (int i = 0; i < THREADS; i++) {
        args[i].lista = &lista;
        args[i].itens = itens;
        args[i].inicio = i * porThread;
        args[i].fim = (i == THREADS - 1) ? totalItens : (i + 1) * porThread;
        args[i].mutex = mutex;
        threads[i] = CreateThread(NULL, 0, inserirLote, &args[i], 0, NULL);
    }

    WaitForMultipleObjects(THREADS, threads, TRUE, INFINITE);
    DWORD fim = tempoAtualMs();

    registrarLog("Todas as threads completaram inserção.");
    printf("Inserção completa | Tempo total: %lu ms\n", fim - ini);

    liberarLista(lista);
    free(itens);
    CloseHandle(mutex);
}

void testarGravacaoRemocaoComProcessos() {
    printf("\n[TESTE] Gravação e Remoção com Processos\n");

    STARTUPINFO si;
ZeroMemory(&si, sizeof(si));
si.cb = sizeof(si);
    PROCESS_INFORMATION pi1, pi2;

    if (CreateProcess(NULL, "cmd /c testelista_gravar.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi1)) {
        WaitForSingleObject(pi1.hProcess, INFINITE);
        CloseHandle(pi1.hProcess);
        CloseHandle(pi1.hThread);
    }

    if (CreateProcess(NULL, "cmd /c testelista_remover.exe", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi2)) {
        WaitForSingleObject(pi2.hProcess, INFINITE);
        CloseHandle(pi2.hProcess);
        CloseHandle(pi2.hThread);
    }
}

void testarTodasFuncoes(int qtd) {
    printf("\n========== INICIANDO TESTE FUNCIONAL (%d itens) ==========\n", qtd);
    criarListaItensSeNaoExistir();

    DWORD ini = tempoAtualMs();
    int qtdLida = 0;
    Item *lista = carregarItensDaLista(&qtdLida);
    DWORD fim = tempoAtualMs();
    printf("[carregarItensDaLista] Itens lidos: %d | Tempo: %lu ms\n", qtdLida, fim - ini);

    ini = tempoAtualMs();
    organizarEGravarItens(lista);
    fim = tempoAtualMs();
    printf("[organizarEGravarItens] Tempo: %lu ms\n", fim - ini);

    ini = tempoAtualMs();
    const char *arquivos[] = {"ListaFrutasLista", "ListaBebidasLista", "ListaDocesLista", "ListaSalgadosLista", "ListaEnlatadosLista"};
    for (int i = 0; i < 5; i++) {
        removerItensVencidos(arquivos[i]);
        mostrarArquivo(arquivos[i]);
    }
    fim = tempoAtualMs();
    printf("[Remoção + visualização] Tempo: %lu ms\n", fim - ini);

    liberarLista(lista);
    printf("===========================================================\n");
}