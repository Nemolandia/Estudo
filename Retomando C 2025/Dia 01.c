#include <stdio.h>
#include <stdlib.h>

void aloca(int **ponteiroAloca, int tam);

int main()
{
    int *ponteiroPadrao = NULL;

    printf("\nMain - antes de alocar espaco na memoria");
    printf("\nEndereco do ponteiroPadrao: %u - Conteudo do ponteiroPadrao: %u", &ponteiroPadrao, ponteiroPadrao);
    
    aloca(&ponteiroPadrao, 1);
    
    printf("\n\nMain - depois de alocar espaco na memoria\n");
    printf("Endereco do ponteiroPadrao: %u - Conteudo do ponteiroPadrao: %u\n\n", &ponteiroPadrao, ponteiroPadrao);

    system("pause");
}//main

void aloca(int **ponteiroAloca, int tam)
{
    printf("\n\nFuncao - antes de alocar espaco na memoria");
    printf("\nEndereco do ponteiroAloca: %u - Conteudo do ponteiroAloca: %u - Conteudo do ponteiroPadrao", &ponteiroAloca, ponteiroAloca, *ponteiroAloca);

    if((*ponteiroAloca=(int*)realloc(*ponteiroAloca, tam*sizeof(int)))==NULL)
    {
        exit(1);
    }

    printf("\n\nFuncao - depois de alocar espaco na memoria");
    printf("\nEndereco do ponteiroAloca: %u - Conteudo do ponteiroAloca: %u - Conteudo do ponteiroPadrao: %u\n", &ponteiroAloca, ponteiroAloca, *ponteiroAloca);
}//aloca