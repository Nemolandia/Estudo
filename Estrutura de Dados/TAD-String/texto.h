// texto.h
/*
*	por: Henrique Seiji Kuroiwa (RA: 236060)
*	curso: Engenharia de Computacao - 5 semestre - 2025s1
*/

typedef struct texto {
	char frase[200];
} texto;

// Inicializar ou reiniciar a string
void iniciaString(texto *t);

// Receber a String
void insereString(texto *t);

// Imprimir a String
void imprimeString(texto *t);

// Calcular tamanho da string
int calculaTamanho(texto *t);

// Comparar duas strings
int comparaString(texto *t1, texto *t2);

// Inverter string
void inverteString(texto *t);
