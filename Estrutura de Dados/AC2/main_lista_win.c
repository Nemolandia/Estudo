
#include <stdio.h>
#include "TestesListaWin.c"

int main() {
    testarTodasFuncoes(TESTE_PEQ);
    testarInsercaoComThreads(TESTE_MED);
    testarInsercaoComThreads(TESTE_GDE);
    testarGravacaoRemocaoComProcessos();
    return 0;
}