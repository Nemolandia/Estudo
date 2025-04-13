/*Isolamento de Raízes – Método da Dicotomia ou Bissecção
Autor: Jeovanni Conservani Silva
RA: 190691*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
Dicas:
        Potencia: pow(base, expoente)
        Arredondar para cima: ceil(valor)
        Modulo/ValorAbsoluto: fabs(valor)
*/
float CalculaValorK(float a, float b, float erro);
float funcaoX(float ponto, float multi[], int grau);
void ImprimirCabecalhoTabela();
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);
void aloca (int *ponteiroAloca, int tam);

void dicotomia(float a, float b, float erro, float multi[], int grau);

int main()
{
    int i, grau, *ponteiroMain = NULL;
    float multi[7], tamMain = 0, erro = 0, a, b, k;

    aloca(&ponteiroMain, tamMain);

    printf("Informe o grau da funcao (2 a 6): ");
    scanf("%i", &grau);

    for(i = grau; i >= 0; i--)
    {
        printf("Informe o fator multiplicador de x^%i(%c): ", i, 65+(grau-i));
        scanf("%f", &multi[i]);
    }

    printf("\nA funcao recebida foi: ");
    for(i=grau; i>=0; i--)
    {
        if(i==0)
            printf("%.2f = 0", multi[i]);
        else
            printf("%.2fx^%i + ", multi[i], i);
    }

    printf("\n\n");
    system("pause");
    printf("\n\n");

    printf("Resultado: %f %f %f\n", funcaoX(0, multi, grau), funcaoX(1, multi, grau), funcaoX(2, multi, grau));
    system("pause");

    printf("\nInforme o valor de A: ");
    scanf("%f", &a);
    printf("\nInforme o valor de B: ");
    scanf("%f", &b);
    printf("\nInforme o valor do erro: ");
    scanf("%f", &erro);

	//Verificar se no intervalo [A, B] existe zero de funcao
    if(funcaoX(a, multi, grau)*funcaoX(b, multi, grau) >= 0)
    {
        printf("\nIntervalo [%.2f, %.2f] nao possui zero de funcao.\n", a, b);
    }

	//Se existir encontar o valor de K
	k = CalculaValorK(a, b, erro);
    printf ("\nValor de k: %f\n", k);

    //Exibindo o cabecalho
    ImprimirCabecalhoTabela();

        //Implementacao da DICOTOMIA
            dicotomia(a, b, k, multi, grau);
            
        //Exibindo os valores na tabela
        ImprimirTabela(1, 2, 3, 4, 5, 6, 7, '+', '-');

    system("pause");
}

void aloca (int *ponteiroAloca, int tam)
{
    if((*ponteiroAloca=(int*)realloc(*ponteiroAloca, tam*sizeof(int)))==NULL)
    exit(1);
}

//Realiza o calculo do K (numero de passo)
float CalculaValorK(float a, float b, float erro)
{
    float fValorK;

    //Realizar o calculo do valor do K
    fValorK = (log10(b-a) - log10(erro))/(log10(2));


    return ceil(fValorK);
}

//Funcao que realiza o calculo em em determinado ponto
float funcaoX(float ponto, float multi[], int grau)
{
    int i;
    float resultado = 0;

    for (i=0; i<=grau; i++)
    {
        resultado = resultado + multi[i]*pow(ponto, i);
    }

    return resultado;
}

//Imprimindo o cabecalho
void ImprimirCabecalhoTabela()
{
    printf("I |\ta\t|\tb\t|\tm\t|\tf(a)\t|\tf(b)\t|\tf(m)\t|fa*fm\t|fm*fb\t|\n");
    printf("--+-------------+---------------+---------------+---------------+---------------+---------------+-------+-------+\n");
}

//Imprimindo a tabela com os valores
void ImprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB)
{
	printf("%i |%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%.5f\t|%c\t|%c\t|\n", iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
}

void dicotomia(float a, float b, float erro, float multi[], int grau)
{
    float fA, fB, fM, m;
    char fAfM, fMfB;
    int iteracao = 1;

    while ((b - a)/2 > erro)
    {
        m = (a + b)/2;
        fA = funcaoX(a, multi, grau);
        fB = funcaoX(b, multi, grau);
        fM = funcaoX(m, multi, grau);

        if (fAfM > 0)
        {
            fAfM = '+';
        }
        else
        {
            fAfM = '-';
        }

        if (fMfB > 0)
        {
            fMfB = '+';
        }
        else
        {
            fMfB = '-';
        }

        if (fA*fM > 0)
        {
            a = m;
        }
        else
        {
            b = m;
        }

        iteracao++;
    }
    ImprimirTabela(iteracao, a, b, m, fA, fB, fM, fAfM, fMfB);
}