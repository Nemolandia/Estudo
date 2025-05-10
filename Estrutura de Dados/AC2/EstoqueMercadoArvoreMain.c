/*****************************************************************************
 * Nome: Aplicação estoque de supermercado feito em C com árvore binária de busca
 * Descrição: Essa aplicação tem como objetivo gerenciar o estoque de um supermercado,
 *          utilizando uma árvore binária de busca para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Da Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 09/05/2025
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoArvore.h"

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