#include "infixaParaPosfixa.h"
#include "pilha.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int precedencia(char operador) {
    switch (operador) {
        case '^': return 4;
        case '*': case '/': return 3;
        case '+': case '-': return 2;
        case '(': case ')': return 1;
        default: return 0;
    }
}

static boolean e_operador(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

static boolean deve_desempilhar(char topo_pilha, char entrada) {
    int prec_topo = precedencia(topo_pilha);
    int prec_entrada = precedencia(entrada);
    
    if (topo_pilha == '+' || topo_pilha == '-' || topo_pilha == '*' || topo_pilha == '/') {
        return prec_topo >= prec_entrada;
    }
    else if (topo_pilha == '^') {
        return prec_topo > prec_entrada;
    }
    
    return false;
}

Fila* infixa_para_posfixa(Fila* fila_infixa) {
    Pilha pilha_operadores;
    Fila* fila_saida = (Fila*)malloc(sizeof(Fila));
    
    if (!newPilha(&pilha_operadores, 10) || !newFila(fila_saida, 10)) {
        printf("Erro: Não foi possível criar estruturas para conversão\n");
        return NULL;
    }

    Fila fila_temp;
    if (!newFila(&fila_temp, 10)) {
        printf("Erro: Não foi possível criar fila temporária\n");
        freePilha(&pilha_operadores);
        freeFila(fila_saida);
        free(fila_saida);
        return NULL;
    }

    while (!isFilaVazia(*fila_infixa)) {
        Token* token;
        if (!getFromFila(*fila_infixa, (ElementoDeFila*)&token)) break;
        removeFromFila(fila_infixa);
        putOnFila(&fila_temp, token);
    }

    while (!isFilaVazia(fila_temp)) {
        Token* token;
        if (!getFromFila(fila_temp, (ElementoDeFila*)&token)) break;
        removeFromFila(&fila_temp);
        putOnFila(fila_infixa, token);

        if (token->tipo == TOKEN_NUMERO) {
            if (!putOnFila(fila_saida, token)) {
                printf("Erro ao colocar número na fila de saída\n");
                freePilha(&pilha_operadores);
                freeFila(&fila_temp);
                freeFila(fila_saida);
                free(fila_saida);
                return NULL;
            }
        }
        else if (token->tipo == TOKEN_PARENTESE) {
            if (strcmp(token->valor, "(") == 0) {
                if (!putOnPilha(&pilha_operadores, token)) {
                    printf("Erro ao empilhar parêntese aberto\n");
                    freePilha(&pilha_operadores);
                    freeFila(&fila_temp);
                    freeFila(fila_saida);
                    free(fila_saida);
                    return NULL;
                }
            }
            else {
                boolean encontrou_aberto = false;
                while (!isPilhaVazia(pilha_operadores)) {
                    Token* topo;
                    if (!getFromPilha(pilha_operadores, (ElementoDePilha*)&topo)) break;

                    if (strcmp(topo->valor, "(") == 0) {
                        encontrou_aberto = true;
                        removeFromPilha(&pilha_operadores);
                        free(topo->valor);
                        free(topo);
                        break;
                    }
                    else {
                        if (!putOnFila(fila_saida, topo)) {
                            printf("Erro ao mover operador para fila de saída\n");
                            freePilha(&pilha_operadores);
                            freeFila(&fila_temp);
                            freeFila(fila_saida);
                            free(fila_saida);
                            return NULL;
                        }
                        removeFromPilha(&pilha_operadores);
                    }
                }

                if (!encontrou_aberto) {
                    printf("Erro: Parênteses desbalanceados\n");
                    free(token->valor);
                    free(token);
                    freePilha(&pilha_operadores);
                    freeFila(&fila_temp);
                    freeFila(fila_saida);
                    free(fila_saida);
                    return NULL;
                }
                free(token->valor);
                free(token);
            }
        }
        else if (token->tipo == TOKEN_OPERADOR) {
            char operador_atual = token->valor[0];
            
            while (!isPilhaVazia(pilha_operadores)) {
                Token* topo;
                if (!getFromPilha(pilha_operadores, (ElementoDePilha*)&topo)) break;

                if (strcmp(topo->valor, "(") != 0 && 
                    e_operador(topo->valor[0]) && 
                    deve_desempilhar(topo->valor[0], operador_atual)) {
                    
                    if (!putOnFila(fila_saida, topo)) {
                        printf("Erro ao mover operador para fila de saída\n");
                        free(token->valor);
                        free(token);
                        freePilha(&pilha_operadores);
                        freeFila(&fila_temp);
                        freeFila(fila_saida);
                        free(fila_saida);
                        return NULL;
                    }
                    removeFromPilha(&pilha_operadores);
                }
                else break;
            }

            if (!putOnPilha(&pilha_operadores, token)) {
                printf("Erro ao empilhar operador\n");
                free(token->valor);
                free(token);
                freePilha(&pilha_operadores);
                freeFila(&fila_temp);
                freeFila(fila_saida);
                free(fila_saida);
                return NULL;
            }
        }
    }

    while (!isPilhaVazia(pilha_operadores)) {
        Token* topo;
        if (!getFromPilha(pilha_operadores, (ElementoDePilha*)&topo)) break;

        if (strcmp(topo->valor, "(") == 0) {
            printf("Erro: Parênteses desbalanceados\n");
            freePilha(&pilha_operadores);
            freeFila(&fila_temp);
            freeFila(fila_saida);
            free(fila_saida);
            return NULL;
        }

        if (!putOnFila(fila_saida, topo)) {
            printf("Erro ao mover operador final para fila de saída\n");
            freePilha(&pilha_operadores);
            freeFila(&fila_temp);
            freeFila(fila_saida);
            free(fila_saida);
            return NULL;
        }
        removeFromPilha(&pilha_operadores);
    }

    freePilha(&pilha_operadores);
    freeFila(&fila_temp);
    return fila_saida;
}