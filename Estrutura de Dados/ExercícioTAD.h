/*
* ExercícioTAD.h - Definição das operações realizadas na sacola
* Autor: Jeovanni Conservani Silva
*/

#define STRINGS_H

int string_tamanho(const char *str);
// Função para calcular o tamanho da string
// Parâmetro: str - ponteiro para a string a ser medida
// Retorna: o número de caracteres na string (sem contar o '\0')

int string_comparar(const char *str1, const char *str2);
// Função para comparar duas strings lexicograficamente
// Parâmetros:
//     str1 - primeira string a ser comparada
//     str2 - segunda string a ser comparada
// Retorna:
//     0 se as strings são iguais,
//     valor negativo se str1 < str2,
//     valor positivo se str1 > str2

void string_inverter(char *str);
// Função para inverter uma string
// Parâmetro: str - ponteiro para a string que será invertida
// Modifica a string original invertendo a ordem dos seus caracteres