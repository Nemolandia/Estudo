
#include <stdio.h>
#include "TestesEstoqueArvore.c"

int main() {
    testarTodasFuncoes(TESTE_PEQ);
    testarInsercaoComThreads(TESTE_MED);
    testarInsercaoComThreads(TESTE_GDE);
    return 0;
}
