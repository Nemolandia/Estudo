#include <stdio.h>
#include <stdlib.h>

void aloca(int **p,int tam);
void leitura(int *p);
void mostra_inversa(int *p,int tam);

main()
{
int *ptr=NULL,cont=0;
char op;

do{
   aloca(&ptr,cont+1);
   leitura(ptr+cont);
   cont++;
   printf("\nDeseja continuar <S/N>: ");
   scanf("%c",&op);
   fflush(stdin);
   }while(op!='n' && op!='N');
mostra_inversa(ptr,cont);
system("pause");
}//main

void aloca(int **p,int tam)
{
if((*p=(int*)realloc(*p,tam*sizeof(int)))==NULL)
  exit(1);
}//aloca

void leitura(int *p)
{
printf("\nEndereco: %u - Numero: ",p);
scanf("%i",p);
fflush(stdin);	
}//leitura

void mostra_inversa(int *p,int tam)
{
int i;
p+=tam-1;
for(i=0;i<tam;i++,p--)
  printf("\nEndereco: %u - Numero: %i",p,*p);
}//mostra_inversa






