#ifndef BREAKEXPRESSIONTOKENS_H
#define BREAKEXPRESSIONTOKENS_H

#include "basics.h"
#include "fila.h"
#include "token.h"

boolean tokenizar(const char* expressao, Fila* filaTokens);

#endif // BREAKEXPRESSIONTOKENS_H