#include "ui.h"
#include <stdio.h>
#include <string.h>

void exibir_cabecalho() {
    printf("=== CALCULADORA DE EXPRESSÕES ARITMÉTICAS ===\n");
    printf("===   Estrutura e Recuperação de Dados    ===\n\n");
    printf("==  André Luis Dos Reis Gomes de Carvalho  ==\n\n");
    printf(" Desenvolvido por João Pedro e Eliseu - 2025 \n\n");
}

void obter_expressao(char* buffer, int tamanho) {
    printf("Digite uma expressão (ou 'sair' para terminar): ");
    if (fgets(buffer, tamanho, stdin) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}