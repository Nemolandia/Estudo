/*
* bag.h - Definição das operações realizadas na sacola
* Autor: Jeovanni Conservani Silva
* Descrição: Este arquivo contém a definição da estrutura de dados Bag e os protótipos das funções
* que implementam as operações básicas para manipulação da sacola, como inicializar, inserir, verificar,
* remover elementos e imprimir o conteúdo da sacola.
*/

#define BAGSIZE 50 // Define o tamanho máximo da sacola

/*
* A estrutura Bag é um tipo de dado que armazena uma coleção de elementos (inteiros) em um vetor.
* A estrutura tem um campo `item[]`, que é um vetor de inteiros de tamanho BAGSIZE, 
* onde os elementos da sacola são armazenados.
* O primeiro elemento do vetor (`item[0]`) é utilizado para armazenar o número de itens presentes na sacola,
* ou seja, o tamanho atual da sacola.
*/
typedef struct Bag
{
    int item[BAGSIZE]; // Array de inteiros para armazenar os itens da sacola
} Bag;


void init (Bag *bagInit);
/*
* Função: init
* Descrição: Inicializa a sacola, configurando o número de itens (item[0]) como 0.
* Isto significa que a sacola começa vazia quando esta função é chamada.
* Parâmetros:
*     - bagInit: Ponteiro para uma instância da estrutura Bag que será inicializada.
* Retorno: Nenhum. Apenas modifica o estado da sacola `b`.
*/

int size (Bag *bagSize);
/*
* Função: size
* Descrição: Retorna o número de elementos atualmente presentes na sacola.
* Como o primeiro item do vetor `item[0]` armazena a quantidade de itens, essa função simplesmente retorna
* o valor armazenado em `item[0]`.
* Parâmetros:
*     - bagSize: Ponteiro para uma instância da estrutura Bag.
* Retorno:
*     - O número de elementos armazenados na sacola.
*/

int insert (Bag *bagInsert, int elementoInsert);
/*
* Função: insert
* Descrição: Insere um novo elemento na sacola, se houver espaço. A sacola tem capacidade máxima definida
* pela constante BAGSIZE. Se a sacola já estiver cheia, a inserção não será realizada.
* Parâmetros:
*     - bagInsert: Ponteiro para a instância da estrutura Bag.
*     - elementoInsert: O elemento (inteiro) a ser inserido na sacola.
* Retorno:
*     - 1 se a inserção foi bem-sucedida (isto é, se houver espaço na sacola).
*     - 0 se a sacola estiver cheia e a inserção não for possível.
*/

int check (Bag *bagCheck, int elementoCheck);
/*
* Função: check
* Descrição: Verifica se um determinado elemento (inteiro) está presente na sacola.
* A função percorre todos os itens armazenados na sacola (no vetor `item[]`) e verifica se o elemento
* procurado está entre eles. 
* Parâmetros:
*     - bagCheck: Ponteiro para a instância da estrutura Bag.
*     - elementoCheck: O elemento a ser verificado.
* Retorno:
*     - 1 se o elemento foi encontrado na sacola.
*     - 0 se o elemento não foi encontrado.
*/

int delete (Bag *bagDelete, int elementoDelete);
/*
* Função: delete
* Descrição: Remove um determinado elemento da sacola, se ele estiver presente.
* A função percorre a sacola e, quando encontra o elemento a ser removido, desloca todos os elementos
* subsequentes para "fechar" o espaço deixado pelo elemento removido. Após isso, o número de itens na sacola
* (armazanado em `item[0]`) é decrementado.
* Parâmetros:
*     - bagDelete: Ponteiro para a instância da estrutura Bag.
*     - elementoDelete: O elemento a ser removido da sacola.
* Retorno:
*     - 1 se o elemento foi removido com sucesso.
*     - 0 se o elemento não foi encontrado na sacola.
*/

void printall (Bag *bagPrintall);
/*
* Função: printall
* Descrição: Imprime todos os elementos presentes na sacola. Ela percorre o vetor `item[]` e imprime
* cada elemento armazenado na sacola. O número de elementos na sacola é determinado pelo valor de `item[0]`.
* Parâmetros:
*     - bagPrintall: Ponteiro para a instância da estrutura Bag.
* Retorno: Nenhum. A função apenas imprime os elementos.
*/
