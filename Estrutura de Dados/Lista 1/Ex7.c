/*Crie uma função que conte quantas vogais existem em uma string. A função recebe
uma string e retorna o número de caracteres que são vogais (a, e, i, o, u). O protótipo
correto é: int contaVogais(char *str); */

#include <stdio.h>
#include <ctype.h>

int contaVogais(char *str)
{
  int count = 0;
  while (*str != '\0')
  {
    char c = tolower(*str);
    if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
    {
      count++;
    }
    str++;
  }
  return count;
}

int main()
{
  char str[100];

  printf("Digite uma string: ");
  fgets(str, sizeof(str), stdin);

  int numVogais = contaVogais(str);

  printf("Numero de vogais na string: %d\n", numVogais);

  return 0;
}
