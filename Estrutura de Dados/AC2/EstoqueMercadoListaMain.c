/*****************************************************************************
 * Nome: Aplicação estoque de supermercado feito em C com Lista Dinâmica
 * Descrição: Essa aplicação tem como objetivo gerenciar o estoque de um supermercado,
 *          utilizando uma Lista Dinâmica para armazenar os itens e suas informações.
 * Autor: Isadora Gesaro Rezende,
          Jeovanni Conservani Silva,
          Khevyn Henrique G. T. Alves,
          Leonardo de Arruda Macedo
 * Data da última modificação: 09/05/2025
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoLista.c"

int main()
{
    Item *listaItens;
    int quantidadeLida;

    criarListaItensSeNaoExistir();
    listaItens = carregarItensDaLista(&quantidadeLida);

    if (quantidadeLida == 0)
    {
        printf("Nenhum item foi carregado da ListaItens.\n");
    }//if
    else
    {
        printf("Itens carregados: %d\n", quantidadeLida);
        organizarEGravarItens(listaItens);
    }//else

    // Mostrar e remover itens vencidos
    const char *arquivos[5] =
    {
        "ListaFrutasLista", "ListaBebidasLista", "ListaDocesLista", "ListaSalgadosLista", "ListaEnlatadosLista"
    };

    for (int i = 0; i < 5; i++)
    {
        mostrarArquivo(arquivos[i]);
        removerItensVencidos(arquivos[i]);
    }//for

    printf("\nApos remocao dos itens vencidos:\n");

    for (int i = 0; i < 5; i++)
    {
        mostrarArquivo(arquivos[i]);
    }//for

    liberarLista(listaItens);
    return 0;
}//main