#include <stdlib.h>
#include "fila.h"

boolean newFila(Fila* f, unsigned int capacidade) {
    if (capacidade <= 0) {
        return false;
    } 

    f->capacidadeInicial = capacidade;
    f->capacidade = capacidade;
    f->vetor = (ElementoDeFila*) malloc(capacidade * sizeof(ElementoDeFila));

    if(f->vetor == NULL) {
        return false;
    }

    f->qtdAtual = 0;
    f->inicio = 0;
    f->final = 0;

    return true;
}

boolean putOnFila(Fila* f, ElementoDeFila e) {
    if (f->qtdAtual == f->capacidade) {
        unsigned int novaCapacidade = f->capacidade * 2;
        ElementoDeFila* novoVetor = (ElementoDeFila*) malloc(novaCapacidade * sizeof(ElementoDeFila));
        
        if (novoVetor == NULL) {
            return false;
        }

        for (unsigned int i = 0; i < f->qtdAtual; i++) { // * copiar elementos na ordem correta
            unsigned int pos = (f->inicio + i) % f->capacidade;
            novoVetor[i] = f->vetor[pos];
        }

        free(f->vetor);
        f->vetor = novoVetor;
        f->capacidade = novaCapacidade;
        f->inicio = 0;
        f->final = f->qtdAtual;
    }

    f->vetor[f->final] = e;
    f->final = (f->final + 1) % f->capacidade;
    f->qtdAtual++;

    return true;
}

boolean getFromFila(Fila f, ElementoDeFila* e) {
    if (f.qtdAtual == 0) {
        return false;
    } 

    *e = f.vetor[f.inicio];
    
    return true;
}

boolean removeFromFila(Fila* f) {
    if (f->qtdAtual == 0) {
        return false;
    } 

    f->inicio = (f->inicio + 1) % f->capacidade;
    f->qtdAtual--;

    if (f->qtdAtual <= f->capacidade/4 && f->capacidade > f->capacidadeInicial) {
        unsigned int novaCapacidade = f->capacidade / 2;
        ElementoDeFila* novoVetor = (ElementoDeFila*) malloc(novaCapacidade * sizeof(ElementoDeFila));
        
        if (novoVetor == NULL) {
            return true; 
        }

        unsigned int posicaoAntiga; 
        unsigned int posicaoNova = 0;
        
        for (unsigned int i = 0; i < f->qtdAtual; i++) {
            posicaoAntiga = (f->inicio + i) % f->capacidade;
            novoVetor[posicaoNova] = f->vetor[posicaoAntiga];
            posicaoNova++;
        }
        
        free(f->vetor);
        f->vetor = novoVetor;
        f->capacidade = novaCapacidade;
        f->inicio = 0;
        f->final = f->qtdAtual;
    }
    return true;
}

boolean isFilaCheia(Fila f) {
    return f.qtdAtual == f.capacidade;
}

boolean isFilaVazia(Fila f) {
    return f.qtdAtual == 0;
}

boolean freeFila(Fila* f) {
    if (f->vetor == NULL) {
        return false;
    }
    
    free(f->vetor);
    f->vetor = NULL;
    f->qtdAtual = 0;
    f->inicio = 0;
    f->final = 0;
    f->capacidade = 0;
    f->capacidadeInicial = 0;
    
    return true;
}