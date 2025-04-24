#include <stdio.h>
#include <stdlib.h>
#include "EstoqueMercadoLista.h"

int main()
{
    // Variáveis para os itens
    Item *listaItens;
    int quantidadeLida;

    // Criar os itens automaticamente, se o arquivo não existir
    criarListaItensSeNaoExistir();

    // Carregar itens do arquivo ListaItens
    carregarItensDaLista(&listaItens, &quantidadeLida);

    // Verificar se algum item foi carregado
    if (quantidadeLida == 0)
    {
        printf("Nenhum item foi carregado da ListaItens.\n");
    }//if
    else
    {
        printf("Itens carregados: %d\n", quantidadeLida);
        
        // Organizar os itens por vencimento e gravá-los nos arquivos correspondentes
        organizarEGravarItens(listaItens, quantidadeLida);
    }//else

    // Mostrar o conteúdo dos arquivos
    mostrarArquivo("ListaFrutas");
    mostrarArquivo("ListaBebidas");
    mostrarArquivo("ListaDoces");
    mostrarArquivo("ListaSalgados");
    mostrarArquivo("ListaEnlatados");

    // Remover itens vencidos de todos os arquivos
    removerItensVencidos("ListaFrutas");
    removerItensVencidos("ListaBebidas");
    removerItensVencidos("ListaDoces");
    removerItensVencidos("ListaSalgados");
    removerItensVencidos("ListaEnlatados");

    // Mostrar o conteúdo após a remoção de itens vencidos
    printf("\nApós a remoção de itens vencidos:\n");
    mostrarArquivo("ListaFrutas");
    mostrarArquivo("ListaBebidas");
    mostrarArquivo("ListaDoces");
    mostrarArquivo("ListaSalgados");
    mostrarArquivo("ListaEnlatados");

    // Liberar memória alocada
    free(listaItens);

    return 0;
}//main