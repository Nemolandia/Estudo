// programa que troca o valor entre dois inteiros (usando função!!!)
#include<stdio.h>

void troca(int *p_a, int *p_b);

int main(){
	int a = 2;
	int b = 3;
	troca(&a,&b);
	printf("Valor de a = %d e valor de b = %d", a,b);
	return 0;
}

void troca(int *p_a, int *p_b){
	int auxiliar;
	auxiliar = *p_a;
	*p_a = *p_b;
	*p_b = auxiliar;
}
