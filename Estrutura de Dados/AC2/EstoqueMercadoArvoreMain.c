#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoArvore.c"

int main() {
    Arvore estoque;
    int quantidadeLida;

    // Cria a lista de itens se não existir
    criarListaItensSeNaoExistir();

    // Carrega os itens da lista para a árvore
    estoque = carregarItensEmArvore(&quantidadeLida);
    if (quantidadeLida == 0) {
        printf("Nenhum item foi carregado da ListaItens.\n");
        return 1;
    } else {
        printf("Total de itens carregados: %d\n", quantidadeLida);
    }

    // Mostra a árvore
    printf("\n--- Itens na Árvore ---\n");
    mostrarArvore(estoque);

    // Organiza e grava os itens nos arquivos binários
    organizarEGravarArvore(estoque);

    const char *arquivos[5] = {
        "ListaFrutasArvore",
        "ListaBebidasArvore",
        "ListaDocesArvore",
        "ListaSalgadosArvore",
        "ListaEnlatadosArvore"
    };

    // Remove itens vencidos
    for (int i = 0; i < 5; i++) {
        removerItensVencidosArvore(arquivos[i]);
    }

    // Mostra o conteúdo de cada arquivo
    printf("\n--- Conteúdo dos Arquivos ---\n");
    for (int i = 0; i < 5; i++) {
        printf("\nConteúdo de %s:\n", arquivos[i]);
        mostrarConteudoArquivo(arquivos[i]);
    }

    liberarArvore(estoque);
    return 0;
}