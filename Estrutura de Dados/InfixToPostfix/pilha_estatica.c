/* 
 * Implementação de pilha utilizando vetor.
 */

#include <stdlib.h>
#include <stdio.h>
#include "pilha_estatica.h"

void cria_pilha(Pilha* ps) {
  ps->topo = -1;
}

int pilha_vazia(Pilha* ps) {
  return (ps->topo == -1); 
}
	  
void insere_pilha(Pilha* ps, elem_t elem) {
  if (ps->topo == MAXPILHA - 1 ) {
    printf("Erro: pilha cheia!\n");
    exit(0);
  }  
  ps->topo++;
  ps->item[ps->topo] = elem;
}

elem_t remove_pilha(Pilha* ps) {
  if (pilha_vazia(ps)) {
    printf("Erro: pilha vazia!\n");
    exit(0);
  }
  return ps->item[ps->topo--];
}

elem_t elem_topo(Pilha *ps){
  if (pilha_vazia(ps)) {
    printf("Erro: pilha vazia!\n");
    exit(0);
  }
  return ps->item[ps->topo];
}

void libera_pilha(Pilha* ps) {
  ps->topo = -1;
}
