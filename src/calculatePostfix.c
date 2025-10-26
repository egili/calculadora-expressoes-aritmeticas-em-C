#include "basics.h"
#include "fila.h"
#include "pilha.h"
#include "token.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

double string_para_double(const char* str) {
    return atof(str);
}

char* double_para_string(double valor) {
    char* str = (char*)malloc(32 * sizeof(char));
    if (str == NULL) return NULL;
    
    snprintf(str, 32, "%.15g", valor);
    return str;
}

double calcular_posfixa(Fila* fila_posfixa) {
    Pilha pilha_operandos;
    if (!newPilha(&pilha_operandos, 10)) {
        printf("Erro: Não foi possível criar a pilha de operandos\n");
        return 0.0;
    }

    while (!isFilaVazia(*fila_posfixa)) {
        Token* token;
        if (!getFromFila(*fila_posfixa, (ElementoDeFila*)&token)) {
            printf("Erro: Não foi possível obter token da fila\n");
            freePilha(&pilha_operandos);
            return 0.0;
        }
        removeFromFila(fila_posfixa);

        if (token->tipo == TOKEN_NUMERO) {

            if (!putOnPilha(&pilha_operandos, token->valor)) {
                printf("Erro: Não foi possível empilhar operando\n");
                free(token);
                freePilha(&pilha_operandos);
                return 0.0;
            }
            free(token);
        }
        else if (token->tipo == TOKEN_OPERADOR) {

            if (pilha_operandos.qtd_atual < 2) {
                printf("Erro: Operador '%s' requer 2 operandos, mas há apenas %d na pilha\n", 
                       token->valor, pilha_operandos.qtd_atual);
                free(token);
                freePilha(&pilha_operandos);
                return 0.0;
            }

            char* operando2_str;
            char* operando1_str;
            
            if (!getFromPilha(pilha_operandos, (ElementoDePilha*)&operando2_str)) {
                printf("Erro: Não foi possível desempilhar operando2\n");
                free(token);
                freePilha(&pilha_operandos);
                return 0.0;
            }
            removeFromPilha(&pilha_operandos);
            
            if (!getFromPilha(pilha_operandos, (ElementoDePilha*)&operando1_str)) {
                printf("Erro: Não foi possível desempilhar operando1\n");
                free(operando2_str);
                free(token);
                freePilha(&pilha_operandos);
                return 0.0;
            }
            removeFromPilha(&pilha_operandos);

            double operando1 = string_para_double(operando1_str);
            double operando2 = string_para_double(operando2_str);
            double resultado;

            free(operando1_str);
            free(operando2_str);

            char operador = token->valor[0];
            switch (operador) {
                case '+':
                    resultado = operando1 + operando2;
                    break;
                case '-':
                    resultado = operando1 - operando2;
                    break;
                case '*':
                    resultado = operando1 * operando2;
                    break;
                case '/':
                    if (operando2 == 0.0) {
                        printf("Erro: Divisão por zero não permitida\n");
                        free(token);
                        freePilha(&pilha_operandos);
                        return 0.0;
                    }
                    resultado = operando1 / operando2;
                    break;
                case '^':
                    resultado = pow(operando1, operando2);
                    break;
                default:
                    printf("Erro: Operador '%c' não reconhecido\n", operador);
                    free(token);
                    freePilha(&pilha_operandos);
                    return 0.0;
            }

            char* resultado_str = double_para_string(resultado);
            if (resultado_str == NULL) {
                printf("Erro: Não foi possível converter resultado para string\n");
                free(token);
                freePilha(&pilha_operandos);
                return 0.0;
            }

            if (!putOnPilha(&pilha_operandos, resultado_str)) {
                printf("Erro: Não foi possível empilhar resultado\n");
                free(resultado_str);
                free(token);
                freePilha(&pilha_operandos);
                return 0.0;
            }

            free(token);
        }
        else {
            printf("Erro: Token do tipo %d não esperado na expressão pós-fixa\n", token->tipo);
            free(token);
            freePilha(&pilha_operandos);
            return 0.0;
        }
    }

    if (pilha_operandos.qtd_atual == 1) {
        char* resultado_final_str;
        if (!getFromPilha(pilha_operandos, (ElementoDePilha*)&resultado_final_str)) {
            printf("Erro: Não foi possível obter resultado final\n");
            freePilha(&pilha_operandos);
            return 0.0;
        }
        
        double resultado_final = string_para_double(resultado_final_str);
        free(resultado_final_str);
        removeFromPilha(&pilha_operandos);
        freePilha(&pilha_operandos);
        
        return resultado_final;
    }
    else if (pilha_operandos.qtd_atual == 0) {
        printf("Erro: Expressão vazia\n");
        freePilha(&pilha_operandos);
        return 0.0;
    }
    else {
        printf("Erro: Expressão malformada - pilha contém %d valores não utilizados\n", 
               pilha_operandos.qtd_atual);
        freePilha(&pilha_operandos);
        return 0.0;
    }
}

// Função de teste
void testar_calculo_posfixa() {
    printf("=== Testando cálculo de expressões pós-fixas ===\n");
    
    // Teste 1: Expressão simples
    Fila fila1;
    newFila(&fila1, 10);
    
    Token* t1 = (Token*)malloc(sizeof(Token));
    t1->tipo = TOKEN_NUMERO;
    t1->valor = strdup("3");
    putOnFila(&fila1, t1);
    
    Token* t2 = (Token*)malloc(sizeof(Token));
    t2->tipo = TOKEN_NUMERO;
    t2->valor = strdup("4");
    putOnFila(&fila1, t2);
    
    Token* t3 = (Token*)malloc(sizeof(Token));
    t3->tipo = TOKEN_NUMERO;
    t3->valor = strdup("2");
    putOnFila(&fila1, t3);
    
    Token* t4 = (Token*)malloc(sizeof(Token));
    t4->tipo = TOKEN_OPERADOR;
    t4->valor = strdup("*");
    putOnFila(&fila1, t4);
    
    Token* t5 = (Token*)malloc(sizeof(Token));
    t5->tipo = TOKEN_OPERADOR;
    t5->valor = strdup("+");
    putOnFila(&fila1, t5);
    
    double resultado1 = calcular_posfixa(&fila1);
    printf("Teste 1: 3 4 2 * + = %.2f (esperado: 11.00)\n", resultado1);
    
    freeFila(&fila1);
    
    // Teste 2: Expressão com divisão
    Fila fila2;
    newFila(&fila2, 10);
    
    // 8 4 / → 8 ÷ 4 = 2
    Token* t6 = (Token*)malloc(sizeof(Token));
    t6->tipo = TOKEN_NUMERO;
    t6->valor = strdup("8");
    putOnFila(&fila2, t6);
    
    Token* t7 = (Token*)malloc(sizeof(Token));
    t7->tipo = TOKEN_NUMERO;
    t7->valor = strdup("4");
    putOnFila(&fila2, t7);
    
    Token* t8 = (Token*)malloc(sizeof(Token));
    t8->tipo = TOKEN_OPERADOR;
    t8->valor = strdup("/");
    putOnFila(&fila2, t8);
    
    double resultado2 = calcular_posfixa(&fila2);
    printf("Teste 2: 8 4 / = %.2f (esperado: 2.00)\n", resultado2);
    
    freeFila(&fila2);
}