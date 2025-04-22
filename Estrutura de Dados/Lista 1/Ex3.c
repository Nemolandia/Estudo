/*Implemente uma função que copie uma string para outra. Usando ponteiros, a
função deve transferir o conteúdo de uma string para outra. O protótipo a ser seguido
é: void copiaString(char *dest, char *orig); */

#include <stdlib.h>
#include <stdio.h>

void copiaString(char *dest, char *orig)
{
  while (*orig != '\0')
  {
    *dest = *orig;
    dest++;
    orig++;
  }
  *dest = '\0';
}

int main()
{
  char origem[100], destino[100];

  printf("Digite uma string: ");
  fgets(origem, sizeof(origem), stdin);

  copiaString(destino, origem);

  printf("String copiada: %s", destino);

  return 0;
}
