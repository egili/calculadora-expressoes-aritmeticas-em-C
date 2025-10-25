#include "basics.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

boolean removerEspacos(char* str) {
    if (str == NULL) {
        return false;
    }

    char* ponteiroTemporario           = str;
    boolean isNumeroAtualmente         = false; 
    boolean ultimoCaracterLidoEhDigito = false; 
    
    while (*ponteiroTemporario != '\0') {
        if (*ponteiroTemporario == ' ') {
            if (isNumeroAtualmente && isdigit(*(ponteiroTemporario + 1)) && *(ponteiroTemporario + 1) != '\0') { // isDigit serve para validar se o caractere é um dígito decimal 0-9
                return false;
            }
        } else if (isdigit(*ponteiroTemporario)) {
            if (!isNumeroAtualmente && ultimoCaracterLidoEhDigito) {
                return false; 
            }
            isNumeroAtualmente = true;
            ultimoCaracterLidoEhDigito = true;
        } else {
            isNumeroAtualmente = false;
            ultimoCaracterLidoEhDigito = false;
            
            if (!strchr("+-*/().", *ponteiroTemporario)) {
                return false; 
            }
        }
        ponteiroTemporario++;
    }

    char* ponteiroLeitura = str;
    char* ponteiroEscrita = str;

    while (*ponteiroLeitura != '\0') {
        if (*ponteiroLeitura != ' ') {
            *ponteiroEscrita = *ponteiroLeitura;
            ponteiroEscrita++;
        }
        ponteiroLeitura++;
    }

    *ponteiroEscrita = '\0';
    
    return true;
}

void testremoverEspacos() {
    printf("=== Testando removerEspacos para expressões matemáticas ===\n");
    
    // Testes VÁLIDOS
    char valid1[] = "10 + (2 * 3)";
    printf("Teste 1 - Válido: '%s' -> ", valid1);
    printf("%s -> ", removerEspacos(valid1) ? "SUCESSO" : "ERRO");
    printf("'%s'\n", valid1);
    
    char valid2[] = "( 123 + 456 ) * 789 ";
    printf("Teste 2 - Válido: '%s' -> ", valid2);
    printf("%s -> ", removerEspacos(valid2) ? "SUCESSO" : "ERRO");
    printf("'%s'\n", valid2);
    
    char valid3[] = "5+6*7-8/2";
    printf("Teste 3 - Válido: '%s' -> ", valid3);
    printf("%s -> ", removerEspacos(valid3) ? "SUCESSO" : "ERRO");
    printf("'%s'\n", valid3);
    
    // Testes INVÁLIDOS
    char invalid1[] = "1 0 + (2 * 3)";
    char backup1[50];
    strcpy(backup1, invalid1);
    printf("Teste 4 - Inválido: '%s' -> ", invalid1);
    printf("%s\n", removerEspacos(invalid1) ? "SUCESSO" : "ERRO (esperado)");
    
    char invalid2[] = "12 34 + 5";
    char backup2[50];
    strcpy(backup2, invalid2);
    printf("Teste 5 - Inválido: '%s' -> ", invalid2);
    printf("%s\n", removerEspacos(invalid2) ? "SUCESSO" : "ERRO (esperado)");
    
    char invalid3[] = "5 + 6 7";
    char backup3[50];
    strcpy(backup3, invalid3);
    printf("Teste 6 - Inválido: '%s' -> ", invalid3);
    printf("%s\n", removerEspacos(invalid3) ? "SUCESSO" : "ERRO (esperado)");
    
    char invalid4[] = "10 + a * 3"; // Caractere inválido
    char backup4[50];
    strcpy(backup4, invalid4);
    printf("Teste 7 - Inválido: '%s' -> ", invalid4);
    printf("%s\n", removerEspacos(invalid4) ? "SUCESSO" : "ERRO (esperado)");
    
    printf("=== Fim dos testes ===\n\n");
}

// int main() {
//     testremoverEspacos();
//     return 0;
// }