#include "basics.h"
#include "fila.h"
#include "token.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

boolean tokenizar(const char* expressao, Fila* filaTokens) {
    int i = 0;
    int tamanho = strlen(expressao);

    while (i < tamanho) {
        if (isspace(expressao[i])) {
            i++;
            continue;
        }

        if (isdigit(expressao[i])) {
            int inicio = i;
            while (i < tamanho && isdigit(expressao[i])) {
                i++;
            }
            int len = i - inicio;

            char* numero = (char*) malloc((len + 1) * sizeof(char));
            if (numero == NULL) return false;
            strncpy(numero, &expressao[inicio], len);
            numero[len] = '\0';

            Token* token = (Token*) malloc(sizeof(Token));
            if (token == NULL) {
                free(numero);
                return false;
            }
            token->tipo = TOKEN_NUMERO;
            token->valor = numero;

            if (!putOnFila(filaTokens, token)) {
                free(numero);
                free(token);
                return false;
            }
            continue;
        }

        char c = expressao[i];
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')') {
            char* simbolo = (char*) malloc(2 * sizeof(char));
            if (simbolo == NULL) return false;
            simbolo[0] = c;
            simbolo[1] = '\0';

            Token* token = (Token*) malloc(sizeof(Token));
            if (token == NULL) {
                free(simbolo);
                return false;
            }
            token->valor = simbolo;

            if (c == '(' || c == ')')
                token->tipo = TOKEN_PARENTESE;
            else
                token->tipo = TOKEN_OPERADOR;

            if (!putOnFila(filaTokens, token)) {
                free(simbolo);
                free(token);
                return false;
            }
            i++;
            continue;
        }

        printf("Erro: caractere inválido '%c'\n", expressao[i]);
        return false;
    }

    return true;
}