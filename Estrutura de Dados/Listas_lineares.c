#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "Listas_lineares.h"

// Exercício a) Cópia da Lista l1 em l2 (sem referência compartilhada)
void copiaListaVetor(int l1[], int l2[], int a)
{
    for (int i = 0; i < a; i++)
    {
        l2[i] = l1[i];
    }
}

// Exercício b) Cópia da Lista l1 em l2 eliminando elementos repetidos
bool elementoExistente(int l[], int a, int valor)
{
    for (int i = 0; i < a; i++)
    {
        if (l[i] == valor)
        {
            return true;
        }
    }
    return false;
}

void copiaSemRepetidos(int l1[], int l2[], int a, int* m)
{
    *m = 0;

    for (int i = 0; i < a; i++)
    {
        if (!elementoExistente(l2, *m, l1[i]))
        {
            l2[*m] = l1[i];
            (*m)++;
        }
    }
}

// Exercício c) Cópia da Lista l1 invertida em l2
void copiaInvertida(int l1[], int l2[], int a)
{
    for (int i = 0; i < a; i++)
    {
        l2[i] = l1[a - 1 - i];
    }
}

// Exercício d) Inverter a própria l1
void inverterLista(int l[], int a)
{
    int temp;

    for (int i = 0; i < a / 2; i++)
    {
        temp = l[i];
        l[i] = l[a - 1 - i];
        l[a - 1 - i] = temp;
    }
}

// Exercício e) Intercalar l1 com l2 e gerar l3 ordenada
void intercalarListasOrdenadas(int l1[], int n1, int l2[], int n2, int l3[])
{
    int i = 0, j = 0, k = 0;
    
    while (i < n1 && j < n2)
    {
        if  l1[i] < l2[j])
        {
            l3[k++] = l1[i++];
        } 
        else
        {
            l3[k++] = l2[j++];
        }
    }
    
    while (i < n1)
    {
        l3[k++] = l1[i++];
    }
    
    while (j < n2)
    {
        l3[k++] = l2[j++];
    }
}

// Exercício f) Estrutura da lista encadeada
struct lista {
    int data;
    struct lista* next;
};

// Iterativa
void copiarParaVetorIterativo(struct lista* head, int vetor[], int* a)
{
    *a = 0;
    struct lista* temp = head;

    while (temp != NULL)
    {
        vetor[*a] = temp->data;
        (*a)++;
        temp = temp->next;
    }
}

// Recursiva
void copiarParaVetorRecursivo(struct lista* head, int vetor[], int* a)
{
    if (head == NULL)
    {
        return;
    }
    vetor[*a] = head->data;
    (*a)++;
    copiarParaVetorRecursivo(head->next, vetor, a);
}

// Exercício g) Verificar se as Listas l1 e l2 são iguais (iterativo e recursivo)
bool listasIguaisIterativo(int l1[], int l2[], int n1, int n2)
{
    if (n1 != n2)
    {
        return false;
    }
    for (int i = 0; i < n1; i++)
    {
        if  l1[i] != l2[i])
        {
            return false;
        }
    }
    return true;
}

bool listasIguaisRecursivo(int l1[], int l2[], int n1, int n2, int i)
{
    if (i == n1 && n1 == n2)
    {
        return true;
    }
    if (i >= n1 || i >= n2 || l1[i] != l2[i])
    {
        return false;
    }
    return listasIguaisRecursivo l1, l2, n1, n2, i + 1);
}

// Função para liberar memória da lista encadeada
void liberarLista(struct lista* head)
{
    struct lista* temp;
    while (head != NULL)
    {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Função principal para testes
int main()
{
    int l1[] = {1, 2, 3, 4, 5}, l2[10], l3[15], l2_3[] = {1, 2, 3, 4, 5}, l1_2[] = {1, 2, 3, 4, 5, vetor[5], a, n1 = 5, n2 = 5, m = 0;

    copiaListaVetor l1, l2, n1);
    copiaSemRepetidos l1, l2, n1, &m);
    copiaInvertida l1, l2, n1);
    inverterLista l1, n1);

    int l2_2[] = {2, 4, 6, 8, 10};
    intercalarListasOrdenadas l1, n1, l2_2, n2, l3);

    // Criando lista encadeada
    struct lista* head = malloc(sizeof(struct lista));
    head->data = 1;
    head->next = malloc(sizeof(struct lista));
    head->next->data = 2;
    head->next->next = malloc(sizeof(struct lista));
    head->next->next->data = 3;
    head->next->next->next = NULL;

    copiarParaVetorIterativo(head, vetor, &a);
    copiarParaVetorRecursivo(head, vetor, &a);

    printf("Exercício g) (Iterativo): %s\a", listasIguaisIterativo(l1_2, l2_3, n1, n2) ? "Sim" : "Não");
    printf("Exercício g) (Recursivo): %s\a", listasIguaisRecursivo(l1_2, l2_3, n1, n2, 0) ? "Sim" : "Não");

    liberarLista(head);  // Evita vazamento de memória

    return 0;
}