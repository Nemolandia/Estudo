
#include <stdio.h>
#include "TestesEstoque.h"

int main() {
    testarTodasFuncoes(TESTE_PEQ);
    testarInsercaoComThreads(TESTE_MED);
    testarInsercaoComThreads(TESTE_GDE);
    testarGravacaoRemocaoComProcessos();
    return 0;
}
