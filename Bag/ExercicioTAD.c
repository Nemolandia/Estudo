/*
* ExercícioTAD.c - Implementação das operações realizadas na sacola (TAD Bag)
* Autor: Jeovanni Conservani Silva
*/

#include <stdio.h>
#include "strings.h"

int main ()
{
    // Inicializa as strings para teste
    char s1[50], s2[50];  // Definindo o tamanho das strings para segurança
    int comparacao;

    // Atribuindo valores às strings
    s1[0] = 'E'; s1[1] = 'u'; s1[2] = ' '; s1[3] = 's'; s1[4] = 'o'; s1[5] = 'u'; s1[6] = ' '; s1[7] = 'G'; s1[8] = 'a'; s1[9] = 'm'; s1[10] = 'e'; s1[11] = 'r'; s1[12] = '!'; s1[13] = '\0'; 
    s2[0] = 'E'; s2[1] = 'u'; s2[2] = ' '; s2[3] = 's'; s2[4] = 'o'; s2[5] = 'u'; s2[6] = ' '; s2[7] = 'O'; s2[8] = 't'; s2[9] = 'a'; s2[10] = 'k'; s2[11] = 'u'; s2[12] = '!'; s2[13] = '\0';

    // Exibe o tamanho da primeira string
    printf("Tamanho de s1: %d\n", string_tamanho(s1));

    // Compara as duas primeiras strings e exibe o resultado
    comparacao = string_comparar(s1, s2);
    printf("Comparação entre s1 e s2: %d\n", comparacao);

    // Inverte a primeira string e exibe o resultado
    string_inverter(s1);
    printf("s1 invertida: %s\n", s1);

    return 0;  // Finaliza o programa
}

// Função para calcular o tamanho da string
// A função percorre a string até encontrar o caractere de término '\0',
// contando a quantidade de caracteres.
// Parâmetro: str - ponteiro para a string a ser medida
// Retorna: o número de caracteres na string
int string_tamanho (const char *str)
{
    int tamanho;  // Declaração explícita da variável

    tamanho = 0;  // Inicializa a variável de contagem de caracteres
    // Percorre a string até encontrar o '\0' (fim da string)
    while (str[tamanho] != '\0') {
        tamanho++;  // Incrementa o contador
    }
    return tamanho;  // Retorna o tamanho da string
}

// Função para comparar duas strings lexicograficamente
// A função compara os caracteres de duas strings até encontrar
// uma diferença ou até o final de ambas as strings.
// Parâmetros:
//     str1 - primeira string a ser comparada
//     str2 - segunda string a ser comparada
// Retorna:
//     0 se as strings são iguais,
//     valor negativo se str1 < str2,
//     valor positivo se str1 > str2
int string_comparar (const char *str1, const char *str2)
{
    int i;  // Declaração explícita da variável de índice
    
    i = 0;  // Inicializa o índice
    // Compara os caracteres das duas strings
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        if (str1[i] != str2[i])
        {
            // Se houver diferença, retorna a diferença entre os caracteres
            return str1[i] - str2[i];
        }
        i++;  // Incrementa o índice
    }
    // Se uma das strings terminar antes, retorna a diferença entre os caracteres de término
    return str1[i] - str2[i];
}

// Função para inverter uma string
// A função inverte os caracteres de uma string diretamente, sem criar uma cópia.
// Parâmetro: str - ponteiro para a string que será invertida
void string_inverter (char *str)
{
    int tamanho, i;  // Declaração explícita de variáveis
    char temp;  // Variável auxiliar para troca de caracteres
    
    tamanho = string_tamanho(str);  // Obtém o tamanho da string
    i = 0;  // Inicializa o índice para percorrer a metade da string
    // Troca os caracteres na primeira metade com os da segunda metade
    while (i < tamanho / 2)
    {
        temp = str[i];  // Armazena o caractere temporariamente
        str[i] = str[tamanho - i - 1];  // Troca com o caractere simetricamente oposto
        str[tamanho - i - 1] = temp;  // Coloca o caractere armazenado na posição oposta
        i++;  // Incrementa o índice
    }
}