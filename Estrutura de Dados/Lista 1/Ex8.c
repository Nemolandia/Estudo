/*Implemente uma função para concatenar duas strings. A segunda string deve ser
anexada ao final da primeira. Utilize o seguinte protótipo: void concatenaString(char
*dest, char *orig); */

#include <stdio.h>

void concatenaString(char *dest, char *orig)
{
  while (*dest != '\0')
  {
    dest++;
  }

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
  char str1[100], str2[50];

  printf("Digite a primeira string: ");
  fgets(str1, sizeof(str1), stdin);
  printf("Digite a segunda string: ");
  fgets(str2, sizeof(str2), stdin);

  str1[strcspn(str1, "\n")] = '\0';
  str2[strcspn(str2, "\n")] = '\0';

  concatenaString(str1, str2);

  printf("String concatenada: %s\n", str1);

  return 0;
}
