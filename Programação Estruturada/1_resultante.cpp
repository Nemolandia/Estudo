//soma de 2 vetores A e B - resultado C
#include <stdio.h>
#include <stdlib.h>

void leitura(int *pLeitura,int q);
void resultante(int *pa,int *pb,int *pc,int q);
void imprime(int *pImprime,int q);

main()
{
int a[10],b[10],c[10],qtde;

printf("\nSoma 2 vetores");
do{
  printf("\nQtde de elementos - max 10: ");
  scanf("%i",&qtde);
  }while(qtde<1 || qtde>10);
printf("\nLeitura - Vetor a:");
leitura(a,qtde);
printf("\nLeitura - Vetor b:");
leitura(b,qtde);
resultante(a,b,c,qtde);
system("cls");
printf("\nImprime - Vetor a:");
imprime(a,qtde);
printf("\nImprime - Vetor b:");
imprime(b,qtde);
printf("\nImprime - Vetor c:");
imprime(c,qtde);
}//main

void leitura(int *pLeitura,int q)
{
int i;
for(i=0;i<q;i++,pLeitura++)
  {
  printf("\nvet[%i]= ",i);
  scanf("%i",pLeitura);
  fflush(stdin);
  }//for
}//leitura

void resultante(int *pa,int *pb,int *pc,int q)
{
int i;
for(i=0;i<q;i++,pa++,pb++,pc++)
  *pc=*pa+*pb;
}//resultante
  
void imprime(int *pImprime,int q)
{
int i;
for(i=0;i<q;i++,pImprime++)
  printf("\nvet[%i]= %i",i,*pImprime);
printf("\n\n\n");
system("pause");
}//imprime
