#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "lista_estatica.h"
#include "pilha_estatica.h"

// Kevin Suzuki Scavassin
// -Documentação Aplicação InfixaPosfixa.c-
// Esta aplicação tem o intuito de ler uma expressão infixa e a transformar em uma expressão posfixa

// Nesta Aplicação possui as seguintes funções:
// HierarquiaOperadoress: Faz a leitura dos operandos
// TransformaExpressao: Faz a leitura das expressões Infixas e as interpreta, separando os operadores e operandos para sair a expressão posfixa
// Main: Onde é guardado as expressões que serão transformadas e faz a chamada das funções

//Função para definir a prioridade dos operaradores em que serão lidas na expressão
int HierarquiaOperadores(char operador) {
    if (operador == '+' || operador == '-'){
		return 1;
	}
    else if (operador == '*' || operador == '/') {
    	return 2;	
	} 
    else {
    	return 0;	
	} 
}

//Função para realizar a transformação da expressão infixa definida no main para a expressão posfixa 
int TransformaExpressao(char *ExpressaoInicial, Lista *ExpressaoTransformada) {
    Pilha operadores;
    cria_pilha(&operadores);
    cria(ExpressaoTransformada);
    
for (int i = 0; ExpressaoInicial[i] != '\0'; i++) {
    char operando = ExpressaoInicial[i];
    
    //Verificação para ignorar espaços
    if (isspace(operando)) {
        continue;
    }
	
	//Verificação para inserir na expressão transformada se o operando for uma letra maiúscula
    if (operando >= 'a' && operando <= 'z') {
        insere_fim(ExpressaoTransformada, operando);
    }
    
    
    //Verificação para inserir na pilha se for um parênteses "aberto"
    else if (operando == '(') {
		insere_pilha(&operadores, operando);
    }
    
    //Verificação para inserir na pilha se for um parênteses "fechado"
    else if (operando == ')') {
        while (!pilha_vazia(&operadores) && elem_topo(&operadores) != '(') {
            insere_fim(ExpressaoTransformada, remove_pilha(&operadores));
        }
        remove_pilha(&operadores);
    }
    
    //Verificação para caso seja um operador, seguirá a hierarquia definida dos operadores para resolver a expressão
    else if (operando == '+' || operando == '-' || operando == '*' || operando == '/' ) {
        while (!pilha_vazia(&operadores) && HierarquiaOperadores(elem_topo(&operadores)) >= HierarquiaOperadores(operando)) {
            insere_fim(ExpressaoTransformada, remove_pilha(&operadores));
        }
        insere_pilha(&operadores, operando);
    }
    
	else {
    	printf("ERRO\n\n");
    	return 0;
	}
}

	while (!pilha_vazia(&operadores)) {
    insere_fim(ExpressaoTransformada, remove_pilha(&operadores));
	}

	while (!pilha_vazia(&operadores)) {
        insere_fim(ExpressaoTransformada, remove_pilha(&operadores));
	}
	return 1;
}
//Onde é feita as chamadas das funções da aplicação
int main() {
    char ExpressaoTeste[100];
    int resposta;

    do {
        printf("Digite a expressao infixa que deseja transformar: ");
        fgets(ExpressaoTeste, sizeof(ExpressaoTeste), stdin);

        if (ExpressaoTeste[strlen(ExpressaoTeste) - 1] == '\n') {
            ExpressaoTeste[strlen(ExpressaoTeste) - 1] = '\0';
        }

        Lista ExpressaoTransformada;
        if(TransformaExpressao(ExpressaoTeste, &ExpressaoTransformada)){
	        printf("Expressao inserida transformada: ");
	        exibe(&ExpressaoTransformada);
	        printf("\n");
		}
		
        printf("Deseja transformar outra expressao? \n 1- Sim \n 2- Nao \nR.: ");
        scanf(" %i", &resposta); 
        fflush(stdin);
    } while (resposta == 1);
    
    return 0;
}
