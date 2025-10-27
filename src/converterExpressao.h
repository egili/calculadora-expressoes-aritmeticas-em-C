
#ifndef CONVERTEREXPRESSAO_H
#define CONVERTEREXPRESSAO_H

#include "basics.h"
#include "fila.h"
#include "token.h"

boolean converterExpressao(Fila* filaEntrada, Fila* filaSaida);
void freeFilaTokens(Fila* fila);
void printFilaTokens(Fila fila);

#endif