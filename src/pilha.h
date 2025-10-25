#ifndef PILHA
#define PILHA

#include "basics.h"

typedef void* ElementoDePilha;

typedef struct {
    ElementoDePilha* vetor; 
    unsigned int capacidade_inicial;
    unsigned int capacidade;
    unsigned int qtd_atual;
} Pilha;

boolean newPilha (Pilha* p, unsigned int capacidade);
boolean putOnPilha (Pilha* p, ElementoDePilha e);
boolean getFromPilha (Pilha p, ElementoDePilha* e);
boolean removeFromPilha (Pilha* p);
boolean isPilhaCheia (Pilha p);
boolean isPilhaVazia (Pilha p);
boolean freePilha (Pilha* p);

#endif // PILHA