#include <stdlib.h>
#include "pilha.h"

boolean newPilha(Pilha* p, unsigned int capacidade) {
    if (capacidade <= 0) {
        return false;
    }

    p->capacidade_inicial = capacidade;
    p->capacidade = capacidade;
    p->qtd_atual = 0;
    p->vetor = (ElementoDePilha*) malloc(capacidade * sizeof(ElementoDePilha));

    if(p->vetor == NULL) {
        return false;
    }

    return true;
}

boolean putOnPilha(Pilha* p, ElementoDePilha e) {
    if (p->qtd_atual == p->capacidade) {
        unsigned int novaCapacidade = p->capacidade * 2;
        ElementoDePilha* novoVetor = (ElementoDePilha*) malloc(novaCapacidade * sizeof(ElementoDePilha));
        
        if (novoVetor == NULL) {
            return false;
        }

        for (unsigned int i = 0; i < p->qtd_atual; i++) {
            novoVetor[i] = p->vetor[i];
        }

        free(p->vetor);
        p->vetor = novoVetor;
        p->capacidade = novaCapacidade;
    }

    p->vetor[p->qtd_atual] = e;
    p->qtd_atual++;

    return true;
}

boolean getFromPilha(Pilha p, ElementoDePilha* e) {
    if (p.qtd_atual == 0) {
        return false;
    } 

    *e = p.vetor[p.qtd_atual - 1];
    
    return true;
}

boolean removeFromPilha(Pilha* p) {
    if (p->qtd_atual == 0) {
        return false;
    }

    p->qtd_atual--;
    p->vetor[p->qtd_atual] = NULL;

    if (p->qtd_atual <= p->capacidade / 4 && p->capacidade > p->capacidade_inicial) {
        unsigned int novaCapacidade = p->capacidade / 2;
        ElementoDePilha* novoVetor = (ElementoDePilha*) malloc(novaCapacidade * sizeof(ElementoDePilha));
        
        if (novoVetor == NULL) {
            return true; 
        }

        for (unsigned int i = 0; i < p->qtd_atual; i++) {
            novoVetor[i] = p->vetor[i];
        }

        free(p->vetor);
        p->vetor = novoVetor;
        p->capacidade = novaCapacidade;
    }  

    return true;
}

boolean isPilhaCheia(Pilha p) {
    return p.qtd_atual == p.capacidade;
}

boolean isPilhaVazia(Pilha p) {
    return p.qtd_atual == 0;
}

boolean freePilha(Pilha* p) {
    if (p->vetor == NULL) {
        return false;
    }

    for (unsigned int i = 0; i < p->qtd_atual; i++) {
        p->vetor[i] = NULL;
    }

    free(p->vetor);
    p->vetor = NULL;
    p->qtd_atual = 0;
    p->capacidade = 0;
    p->capacidade_inicial = 0;

    return true;
}