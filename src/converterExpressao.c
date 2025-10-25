#include "converterExpressao.h"
#include "pilha.h"
#include "fila.h"
#include "token.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

static int getPrecedencia(char operador) {
    
    if (operador == '^') {
        return 3;
    }
    
    if (operador == '*' || operador == '/') {
        return 2;
    }

    if (operador == '+' || operador == '-') {
        return 1;
    } 
    
    return 0;
}

boolean converterExpressao(Fila* filaEntrada, Fila* filaSaida) {
    Pilha pilhaOperadores;
    
    if (!newPilha(&pilhaOperadores, 10)) {
        return false;
    }

    Token* token;
    boolean sucesso = true;

    while (getFromFila(*filaEntrada, (ElementoDeFila*)&token)) {
        removeFromFila(filaEntrada);

        switch (token->tipo) {
            case TOKEN_NUMERO:
                if (!putOnFila(filaSaida, token)) {
                    sucesso = false;
                }
                break;

            case TOKEN_OPERADOR:
                while (!isPilhaVazia(pilhaOperadores)) {
                    Token* topo;
                    if (!getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo)) {
                        break;
                    }
                    
                    if (topo->tipo == TOKEN_PARENTESE && topo->valor[0] == '(') { //* para se encontrar parêntese esquerdo
                        break;
                    }
                    
                    if (topo->tipo == TOKEN_OPERADOR) {
                        char operadorTopo = topo->valor[0];
                        char operadorAtual = token->valor[0];
                        
                        int precedenciaTopo = getPrecedencia(operadorTopo);
                        int precedenciaAtual = getPrecedencia(operadorAtual);
                        
                        boolean deveDesempilhar = (precedenciaTopo > precedenciaAtual) || (precedenciaTopo == precedenciaAtual && !operadorAtual == '^');
                        
                        if (deveDesempilhar) {
                            putOnFila(filaSaida, topo);
                            removeFromPilha(&pilhaOperadores);
                        } else {
                            break;
                        }
                    } else {
                        break;
                    }
                }
                
                if (!putOnPilha(&pilhaOperadores, token)) {
                    sucesso = false;
                }
                break;

            case TOKEN_PARENTESE:
                if (token->valor[0] == '(') {
                    if (!putOnPilha(&pilhaOperadores, token)) {
                        sucesso = false;
                    }
                } else {
                    boolean encontrouParenteseAberto = false;
                    
                    while (!isPilhaVazia(pilhaOperadores)) {
                        Token* topo;
                        if (!getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo)) {
                            break;
                        }
                        
                        if (topo->tipo == TOKEN_PARENTESE && topo->valor[0] == '(') {
                            encontrouParenteseAberto = true;
                            removeFromPilha(&pilhaOperadores);
                            
                            free(topo->valor);
                            free(topo);
                            free(token->valor);
                            free(token);
                            token = NULL;
                            break;
                        } else {
                            putOnFila(filaSaida, topo);
                            removeFromPilha(&pilhaOperadores);
                        }
                    }
                    
                    if (!encontrouParenteseAberto) {
                        sucesso = false;
                        if (token) {
                            free(token->valor);
                            free(token);
                        }
                    }
                }
                break;
        }
        
        if (!sucesso) break;
    }

    while (sucesso && !isPilhaVazia(pilhaOperadores)) { //* processa os operadores restantes na pilha
        Token* topo;
        if (!getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo)) {
            break;
        }
        
        if (topo->tipo == TOKEN_PARENTESE && topo->valor[0] == '(') {
            sucesso = false;
            free(topo->valor);
            free(topo);
        } else {
            if (!putOnFila(filaSaida, topo)) {
                sucesso = false;
                free(topo->valor);
                free(topo);
            }
            removeFromPilha(&pilhaOperadores);
        }
    }

    if (!sucesso) { //* limpar em caso de erro
        while (!isPilhaVazia(pilhaOperadores)) {
            Token* topo;
            if (getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo)) {
                removeFromPilha(&pilhaOperadores);
                free(topo->valor);
                free(topo);
            }
        }
        
        while (getFromFila(*filaEntrada, (ElementoDeFila*)&token)) {
            removeFromFila(filaEntrada);
            free(token->valor);
            free(token);
        }
    }

    freePilha(&pilhaOperadores);
    return sucesso;
}

void freeFilaTokens(Fila* fila) {
    if (fila == NULL) return;
    
    Token* token;
    while (getFromFila(*fila, (ElementoDeFila*)&token)) {
        removeFromFila(fila);
        free(token->valor);
        free(token);
    }
}

void printFilaTokens(Fila fila) {
    if (fila.qtdAtual == 0) {
        printf("\n");
        return;
    }

    unsigned int i = fila.inicio;
    unsigned int count = 0;
    
    while (count < fila.qtdAtual) {
        Token* token = (Token*)fila.vetor[i];
        printf("%s ", token->valor);
        i = (i + 1) % fila.capacidade;
        count++;
    }
    printf("\n");
}