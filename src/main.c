#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basics.h"
#include "fila.h"
#include "pilha.h"
#include "token.h"
#include "calculatePostfix.h"
#include "removerEspacos.h"
#include "breakExpressionTokens.h"
#include "infixaParaPosfixa.h"
#include "interface.h"

int main() {
    exibir_cabecalho();
    
    while (true) {
        char expressao[1000];
        obter_expressao(expressao, sizeof(expressao));
        
        if (strcmp(expressao, "sair") == 0) {
            printf("Encerrando calculadora...\n");
            break;
        }
        
        if (strlen(expressao) == 0) continue;
        
        printf("\nExpressão original: '%s'\n", expressao);
        
        if (!removerEspacos(expressao)) {
            printf("Erro: Expressão contém espaços entre dígitos ou caracteres inválidos\n");
            continue;
        }
        printf("Expressão sem espaços: '%s'\n", expressao);
        
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
