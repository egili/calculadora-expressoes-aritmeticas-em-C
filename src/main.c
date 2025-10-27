#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "basics.h"
#include "fila.h"
#include "pilha.h"
#include "token.h"
#include "calculatePostfix.h"
#include "removerEspacos.c"
#include "breakExpressionTokens.c"
#include "calculatePostfix.c"

Fila* infixa_para_posfixa(Fila* fila_infixa) {
    Pilha pilha_operadores;
    Fila* fila_saida = (Fila*)malloc(sizeof(Fila));
    
    if (!newPilha(&pilha_operadores, 10) || !newFila(fila_saida, 10)) {
        printf("Erro: Não foi possível criar estruturas para conversão\n");
        return NULL;
    }

    int precedencia(char operador) {
        switch (operador) {
            case '^': return 4;
            case '*': case '/': return 3;
            case '+': case '-': return 2;
            case '(': case ')': return 1;
            default: return 0;
        }
    }

    boolean e_operador(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
    }

    boolean deve_desempilhar(char topo_pilha, char entrada) {
        int prec_topo = precedencia(topo_pilha);
        int prec_entrada = precedencia(entrada);
        
        // Para associatividade da esquerda (+, -, *, /)
        if (topo_pilha == '+' || topo_pilha == '-' || topo_pilha == '*' || topo_pilha == '/') {
            return prec_topo >= prec_entrada;
        }
        // Para associatividade da direita (^)
        else if (topo_pilha == '^') {
            return prec_topo > prec_entrada;
        }
        
        return false;
    }

    // Fila temporária para preservar a fila original
    Fila fila_temp;
    if (!newFila(&fila_temp, 10)) {
        printf("Erro: Não foi possível criar fila temporária\n");
        freePilha(&pilha_operadores);
        freeFila(fila_saida);
        free(fila_saida);
        return NULL;
    }

    // Transferir todos os tokens para fila temporária
    while (!isFilaVazia(*fila_infixa)) {
        Token* token;
        if (!getFromFila(*fila_infixa, (ElementoDeFila*)&token)) {
            break;
        }
        removeFromFila(fila_infixa);
        putOnFila(&fila_temp, token);
    }

    // Restaurar fila original e processar
    while (!isFilaVazia(fila_temp)) {
        Token* token;
        if (!getFromFila(fila_temp, (ElementoDeFila*)&token)) {
            printf("Erro ao obter token da fila temporária\n");
            break;
        }
        removeFromFila(&fila_temp);
        
        // Restaurar na fila original
        putOnFila(fila_infixa, token);

        if (token->tipo == TOKEN_NUMERO) {
            // Números vão direto para a fila de saída
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
                // Parêntese aberto vai para a pilha
                if (!putOnPilha(&pilha_operadores, token)) {
                    printf("Erro ao empilhar parêntese aberto\n");
                    freePilha(&pilha_operadores);
                    freeFila(&fila_temp);
                    freeFila(fila_saida);
                    free(fila_saida);
                    return NULL;
                }
            }
            else { // Parêntese fechado ")"
                // Desempilha até encontrar o parêntese aberto correspondente
                boolean encontrou_aberto = false;
                while (!isPilhaVazia(pilha_operadores)) {
                    Token* topo;
                    if (!getFromPilha(pilha_operadores, (ElementoDePilha*)&topo)) {
                        break;
                    }

                    if (strcmp(topo->valor, "(") == 0) {
                        encontrou_aberto = true;
                        removeFromPilha(&pilha_operadores);
                        free(topo->valor);
                        free(topo);
                        break;
                    }
                    else {
                        // Move operador para fila de saída
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
            
            // Desempilha operadores conforme a tabela de precedência
            while (!isPilhaVazia(pilha_operadores)) {
                Token* topo;
                if (!getFromPilha(pilha_operadores, (ElementoDePilha*)&topo)) {
                    break;
                }

                // Se o topo não for parêntese e deve desempilhar
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
                else {
                    break;
                }
            }

            // Empilha o operador atual
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

    // Desempilha todos os operadores restantes
    while (!isPilhaVazia(pilha_operadores)) {
        Token* topo;
        if (!getFromPilha(pilha_operadores, (ElementoDePilha*)&topo)) {
            break;
        }

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

// Função para exibir uma fila (para debug)
void exibir_fila(Fila* fila, const char* nome) {
    printf("%s: ", nome);
    
    Fila temp;
    newFila(&temp, fila->capacidade);
    
    while (!isFilaVazia(*fila)) {
        Token* token;
        if (getFromFila(*fila, (ElementoDeFila*)&token)) {
            printf("%s ", token->valor);
            putOnFila(&temp, token);
            removeFromFila(fila);
        }
    }
    
    // Restaura a fila original
    while (!isFilaVazia(temp)) {
        Token* token;
        if (getFromFila(temp, (ElementoDeFila*)&token)) {
            putOnFila(fila, token);
            removeFromFila(&temp);
        }
    }
    
    freeFila(&temp);
    printf("\n");
}

// função principal integrando todas as partes do projeto para ver se está funcionando.
int main() {
    printf("=== CALCULADORA DE EXPRESSÕES ARITMÉTICAS ===\n");
    printf("===   Estrutura e Recuperação de Dados    ===\n\n");
    printf("==  André Luis Dos Reis Gomes de Carvalho  ==\n\n");
    printf(" Desenvolvido por João Pedro e Eliseu - 2025 \n\n");
    
    while (true) {
        char expressao[1000];
        printf("Digite uma expressão (ou 'sair' para terminar): ");
        
        if (fgets(expressao, sizeof(expressao), stdin) == NULL) {
            break;
        }
        
        // Remove newline do final
        expressao[strcspn(expressao, "\n")] = '\0';
        
        if (strcmp(expressao, "sair") == 0) {
            printf("Encerrando calculadora...\n");
            break;
        }
        
        if (strlen(expressao) == 0) {
            continue;
        }
        
        printf("\nExpressão original: '%s'\n", expressao);
        
        // ETAPA 1: Remover espaços
        if (!removerEspacos(expressao)) {
            printf("Erro: Expressão contém espaços entre dígitos ou caracteres inválidos\n");
            continue;
        }
        printf("Expressão sem espaços: '%s'\n", expressao);
        
        // ETAPA 2: Tokenização
        Fila fila_tokens;
        if (!newFila(&fila_tokens, 10)) {
            printf("Erro: Não foi possível criar fila de tokens\n");
            continue;
        }
        
        if (!tokenizar(expressao, &fila_tokens)) {
            printf("Erro na tokenização da expressão\n");
            freeFila(&fila_tokens);
            continue;
        }
        
        Fila* fila_posfixa = infixa_para_posfixa(&fila_tokens);
        if (fila_posfixa == NULL) {
            printf("Erro na conversão para notação pós-fixa\n");
            freeFila(&fila_tokens);
            continue;
        }
        
        double resultado = calcular_posfixa(fila_posfixa);
        
        printf("Resultado: %.2f\n\n", resultado);
        
        freeFila(&fila_tokens);
        freeFila(fila_posfixa);
        free(fila_posfixa);
    }
    
    printf("PROGRAMA FINALIZADO COM SUCESSO!\n");
    return 0;
}