/*Método de Lagrange
Autor: Jeovanni Conservani Silva
RA: 190691*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float lagrange(float *x, float *fx, int n, float valorCalcular);

int main()
{
    int grau, i, pontos;
    float valorCalcular, resultado;
    char resp;
    float *x, *fx;

    printf("Digite o grau da funcao que deseja obter: ");
    scanf("%d", &grau);

    pontos = grau + 1;
    x = (float *)malloc(pontos * sizeof(float));
    fx = (float *)malloc(pontos * sizeof(float));

    if (x == NULL || fx == NULL)
    {
        printf("Erro na alocacao de memoria!\n");
        return 1;
    }

    for (i = 0; i < pontos; i++)
    {
        printf("Digite o valor de x[%d]: ", i);
        scanf("%f", &x[i]);
        printf("Digite o valor de f(x[%d]): ", i);
        scanf("%f", &fx[i]);
    }

    do
    {
        printf("\nDigite o valor que deseja calcular: ");
        scanf("%f", &valorCalcular);
        
        resultado = lagrange(x, fx, pontos, valorCalcular);
        printf("\nO valor interpolado em %.2f eh %.5f\n", valorCalcular, resultado);
        
        printf("Deseja calcular outro valor (s/n)? ");
        scanf(" %c", &resp);
    } while (resp == 's' || resp == 'S');

    free(x);
    free(fx);
    return 0;
}

// Função para calcular a interpolação de Lagrange
float lagrange(float *x, float *fx, int n, float valorCalcular)
{
    float Px, Li;
    int i, j;
    
    Px = 0;
    
    for (i = 0; i < n; i++)
    {
        Li = 1;
        
        for (j = 0; j < n; j++)
        {
            if (i != j)
            {
                Li *= (valorCalcular - x[j]) / (x[i] - x[j]);
            }
        }
        
        Px += Li * fx[i];
    }
    
    return Px;
}