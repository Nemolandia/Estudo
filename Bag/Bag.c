/*
* bag.c - Implementação das operações realizadas na sacola (TAD Bag)
* Autor: Jeovanni Conservani Silva
*/
#include <stdio.h>
#include <stdlib.h>
#include "Bag.h"

/*
* Função principal para testar as operações
*/
int main ()
{
    int aux, numAleatorio, i;
    
    Bag minhaSacola;

    init (&minhaSacola);

    printf ("Tamanho inicial da sacola: %d\n", size(&minhaSacola));

    // Testando inserção de elementos
    insert (&minhaSacola, 5);
    insert (&minhaSacola, 10);
    insert (&minhaSacola, 15);
    insert (&minhaSacola, 20);

    printf ("Tamanho apos insercoes: %d\n", size(&minhaSacola));

    printall (&minhaSacola);

    // Verificando se um elemento está presente
    printf ("Qual elemento deseja encontrar: ");
    scanf ("%d", &aux);

    if (check(&minhaSacola, aux))
    {
        printf ("Elemento %d encontrado na sacola.\n", aux);
    }
    else
    {
        printf ("Elemento %d nao encontrado na sacola.\n", aux);
    }

    // Removendo um elemento
    printf ("Qual elemento deseja remover: ");
    scanf ("%d", &aux);

    delete (&minhaSacola, aux);

    printf ("Tamanho da sacola apos remocao: %d\n", size(&minhaSacola));

    printall (&minhaSacola);

    // Tentando inserir até a sacola ficar cheia
    do
    {
        // Inicializa a geração de números aleatórios
        srand(time(NULL)); // Semente para números aleatórios

        // Inserir números aleatórios na sacola
        for (i = 0; i <= size(&minhaSacola); i++) // Insere números aleatórios até a sacola encher
        {
            numAleatorio = rand() % 100 + 1; // Número aleatório entre 1 e 100
            insert (&minhaSacola, numAleatorio);
            printf("Numeros aleatorios inseridos na sacola: %d\n", numAleatorio); // Exibe o número inserido
        }
    } while (insert (&minhaSacola, &numAleatorio));

    printf ("Tamanho apos tentativas de insercoes: %d\n", size(&minhaSacola));

    printall (&minhaSacola);
}

void init (Bag *bagInit)
{
    bagInit->item[0] = 0; // Inicializa a sacola com um item fictício que representa o número de itens na bag
}

int size (Bag *bagSize)
{
    return bagSize->item[0]; // O primeiro item armazena o número de elementos na sacola
}

int insert (Bag *bagInsert, int elementoInsert)
{
    if (bagInsert->item[0] < BAGSIZE)
    {
        bagInsert->item[bagInsert->item[0] + 1] = elementoInsert; // Coloca o elemento na próxima posição disponível
        bagInsert->item[0]++; // Incrementa o número de itens na sacola
        return 1; // Inserção bem-sucedida
    }
    return 0; // A sacola está cheia
}

int check (Bag *bagCheck, int elementoCheck)
{
    int i;

    for (i = 1; i <= bagCheck->item[0]; i++)
    {
        if (bagCheck->item[i] == elementoCheck)
        {
            return 1; // O elemento foi encontrado
        }
    }
    return 0; // O elemento não foi encontrado
}

int delete(Bag *bagDelete, int elementoDelete)
{
    int i, j;

    for (i = 1; i <= bagDelete->item[0]; i++)
    {
        if (bagDelete->item[i] == elementoDelete)
        {
            // Desloca os itens subsequentes para "fechar o buraco"
            for (j = i; j < bagDelete->item[i]; j++)
            {
                bagDelete->item[j] = bagDelete->item[j + 1];
            }

            bagDelete->item[0]--; // Decrementa o número de itens na sacola
            return 1; // Remoção bem-sucedida
        }
    }
    return 0; // O elemento não foi encontrado
}

void printall(Bag *bagPrintall)
{
    int i;

    printf ("Itens na sacola: ");

    for (i = 1; i <= bagPrintall->item[0]; i++)
    {
        printf ("%d ", bagPrintall->item[i]);
    }
    printf ("\n");
}