#include <stdlib.h>
#include "pilha.h"

boolean newPilha (Pilha* p, unsigned int capacidade) {
    if (capacidade <= 0) {
        return false;
    }

    (*p).capacidade_inicial = capacidade;
    (*p).capacidade = capacidade;
    (*p).qtd_atual = 0;
    (*p).vetor = (ElementoDePilha*) malloc(capacidade*sizeof(ElementoDePilha));

    if((*p).vetor == NULL) {
        return false;
    }

    return true;
}

boolean putOnPilha (Pilha* p, ElementoDePilha e) {
    if (p->qtd_atual == p->capacidade) {
        p->capacidade *= 2;
        p->vetor = (ElementoDePilha*) realloc(p->vetor, p->capacidade*sizeof(ElementoDePilha));
    }

    (*p).vetor[(*p).qtd_atual] = e;

    (*p).qtd_atual++;

    return true;
}

boolean getFromPilha (Pilha p, ElementoDePilha* e) {
    if (p.qtd_atual == 0) {
        return false;
    } 

    *e = p.vetor[p.qtd_atual - 1];
    
    return true;
}

boolean removeFromPilha (Pilha* p) {
    if (p->qtd_atual == 0) {
        return false;
    }

    p->qtd_atual--;
    p->vetor[p->qtd_atual] = NULL;

    if (p->qtd_atual <= 0.25 * p->capacidade && p->capacidade > p->capacidade_inicial){
        p->capacidade /= 2;
        p->vetor = (ElementoDePilha*) realloc(p->vetor, p->capacidade*sizeof(ElementoDePilha));
    }  

    return true;
}

boolean isPilhaCheia (Pilha p) {
    return p.qtd_atual == p.capacidade;
}

boolean isPilhaVazia (Pilha p) {
    return p.qtd_atual == 0;
}

boolean freePilha (Pilha* p) {
    if (p->vetor==NULL) return false;

    for (int i=0; i < p->qtd_atual; i++) {
        free(p->vetor[--(p->qtd_atual)]);
        p->vetor[p->qtd_atual] = NULL;
    }

    free(p->vetor);
    p->vetor = NULL;

    return true;
}