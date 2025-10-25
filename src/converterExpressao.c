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
                if (!putOnFila(filaSaida, token)) { //* numeros vao direto para a fila de saída
                    sucesso = false;
                }
                break;

            case TOKEN_OPERADOR: //* operadores processados conforme precedência e associatividade
                while (!isPilhaVazia(pilhaOperadores)) {
                    Token* topo;
                    getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo);
                    
                    if (topo->tipo == TOKEN_PARENTESE && topo->valor[0] == '(') { //* encontrou um parentese esquerdo
                        break;
                    }
                    
                    if (topo->tipo == TOKEN_OPERADOR) { //* validar se deve desempilhar operadores com precedencia maior ou igual
                        char operadorTopo = topo->valor[0];
                        char operadorAtual = token->valor[0];
                        
                        int precedenciaTopo = getPrecedencia(operadorTopo); 
                        int precedenciaAtual = getPrecedencia(operadorAtual); 
                        
                        boolean deveDesempilhar = (precedenciaTopo > precedenciaAtual) ||
                                            (precedenciaTopo == precedenciaAtual && operadorAtual != '^'); 
                        
                        if (deveDesempilhar) { //* mover o operador do topo para a saída
                            putOnFila(filaSaida, topo);
                            removeFromPilha(&pilhaOperadores);
                        } else {
                            break;
                        }
                    }
                }                
                if (!putOnPilha(&pilhaOperadores, token)) { //* empilha o operador atual
                    sucesso = false;
                }
                break;

            case TOKEN_PARENTESE:
                if (token->valor[0] == '(') { //* achou parêntese esquerdo e ele vai para a pilha
                    if (!putOnPilha(&pilhaOperadores, token)) {
                        sucesso = false;
                    }
                } else { //* Parêntese direito: desempilha até encontrar o esquerdo correspondente
                    boolean encontrouParenteseAberto = false;
                    
                    while (!isPilhaVazia(pilhaOperadores)) {
                        Token* topo;
                        getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo);
                        
                        if (topo->tipo == TOKEN_PARENTESE && topo->valor[0] == '(') { //* Encontrou o parêntese esquerdo correspondente
                            encontrouParenteseAberto = true;
                            removeFromPilha(&pilhaOperadores);
                            
                            free(topo->valor);
                            free(topo);
                            free(token->valor);
                            free(token);
                            token = NULL;
                            break;
                        } else { //* Move operadores para a saída
                            putOnFila(filaSaida, topo);
                            removeFromPilha(&pilhaOperadores);
                        }
                    }
                    
                    if (!encontrouParenteseAberto) { // ! direito sem correspondente
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

    //* Processa operadores restantes na pilha
    while (sucesso && !isPilhaVazia(pilhaOperadores)) {
        Token* topo;
        getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo);
        
        if (topo->tipo == TOKEN_PARENTESE && topo->valor[0] == '(') { //! parêntese esquerdo sem fechamento
            sucesso = false;
            free(topo->valor);
            free(topo);
        } else { //* Move operador para a saída
            if (!putOnFila(filaSaida, topo)) {
                sucesso = false;
                free(topo->valor);
                free(topo);
            } else {
                removeFromPilha(&pilhaOperadores);
            }
        }
    }

    if (!sucesso) { //* Libera tokens restantes na pilha
        while (!isPilhaVazia(pilhaOperadores)) {
            Token* topo;
            getFromPilha(pilhaOperadores, (ElementoDePilha*)&topo);
            removeFromPilha(&pilhaOperadores);
            free(topo->valor);
            free(topo);
        }
    }

    freePilha(&pilhaOperadores);
    return sucesso;
}

void freeFilaTokens(Fila* fila) {
    Token* token;
    while (getFromFila(*fila, (ElementoDeFila*)&token)) {
        removeFromFila(fila);
        free(token->valor);
        free(token);
    }
}

void printFilaTokens(Fila fila) {
    Fila filaTemporaria;

    if (!newFila(&filaTemporaria, fila.qtdAtual)) {
        return;
    }
    
    Token* token;
    while (getFromFila(fila, (ElementoDeFila*)&token)) {
        removeFromFila(&fila);
        printf("%s ", token->valor);
        putOnFila(&filaTemporaria, token);
    }
    
    while (getFromFila(filaTemporaria, (ElementoDeFila*)&token)) { //* restaura a fila original
        removeFromFila(&filaTemporaria);
        putOnFila(&fila, token);
    }
    
    freeFila(&filaTemporaria);
    printf("\n");
}