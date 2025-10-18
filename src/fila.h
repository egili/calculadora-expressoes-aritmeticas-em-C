#ifndef FILA
#define FILA

#include "basics.h"

typedef void* ElementoDeFila;

typedef struct {
    ElementoDeFila* vetor; 
    unsigned int capacidadeInicial;
    unsigned int capacidade;
    unsigned int qtdAtual;
    unsigned int inicio;
    unsigned int final;
} Fila;

boolean newFila (Fila* p, unsigned int capacidade);
boolean putOnFila (Fila* p, ElementoDeFila e);
boolean getFromFila (Fila p, ElementoDeFila* e);
boolean removeFromFila (Fila* p);
boolean isFilaCheia (Fila p);
boolean isFilaVazia (Fila p);
boolean freeFila (Fila* p);

#endif // FILA
