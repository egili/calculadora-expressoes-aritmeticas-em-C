#include "basics.h"
#include <ctype.h>
#include <string.h>

boolean removeGaps(char* str) {
    if (str == NULL) {
        return false;
    }

    char* tempPtr        = str;
    boolean inNumber     = false; // pra validar se atualmente estamos lendo um número
    boolean lastWasDigit = false; // pra validar se o último caractere lido foi um dígito
    
    while (*tempPtr != '\0') {
        if (*tempPtr == ' ') {
            if (inNumber && isdigit(*(tempPtr + 1)) && *(tempPtr + 1) != '\0') { // isDigit serve para validar se o caractere é um dígito decimal 0-9
                return false;
            }
        } else if (isdigit(*tempPtr)) {
            if (!inNumber && lastWasDigit) {
                return false; 
            }
            inNumber = true;
            lastWasDigit = true;
        } else {
            inNumber = false;
            lastWasDigit = false;
            
            if (!strchr("+-*/().", *tempPtr)) {
                return false; 
            }
        }
        tempPtr++;
    }

    char* readPtr = str;
    char* writePtr = str;

    while (*readPtr != '\0') {
        if (*readPtr != ' ') {
            *writePtr = *readPtr;
            writePtr++;
        }
        readPtr++;
    }

    *writePtr = '\0';
    
    return true;
}

void testRemoveGaps() {
    printf("=== Testando removeGaps para expressões matemáticas ===\n");
    
    // Testes VÁLIDOS
    char valid1[] = "10 + (2 * 3)";
    printf("Teste 1 - Válido: '%s' -> ", valid1);
    printf("%s -> ", removeGaps(valid1) ? "SUCESSO" : "ERRO");
    printf("'%s'\n", valid1);
    
    char valid2[] = "( 123 + 456 ) * 789 ";
    printf("Teste 2 - Válido: '%s' -> ", valid2);
    printf("%s -> ", removeGaps(valid2) ? "SUCESSO" : "ERRO");
    printf("'%s'\n", valid2);
    
    char valid3[] = "5+6*7-8/2";
    printf("Teste 3 - Válido: '%s' -> ", valid3);
    printf("%s -> ", removeGaps(valid3) ? "SUCESSO" : "ERRO");
    printf("'%s'\n", valid3);
    
    // Testes INVÁLIDOS
    char invalid1[] = "1 0 + (2 * 3)";
    char backup1[50];
    strcpy(backup1, invalid1);
    printf("Teste 4 - Inválido: '%s' -> ", invalid1);
    printf("%s\n", removeGaps(invalid1) ? "SUCESSO" : "ERRO (esperado)");
    
    char invalid2[] = "12 34 + 5";
    char backup2[50];
    strcpy(backup2, invalid2);
    printf("Teste 5 - Inválido: '%s' -> ", invalid2);
    printf("%s\n", removeGaps(invalid2) ? "SUCESSO" : "ERRO (esperado)");
    
    char invalid3[] = "5 + 6 7";
    char backup3[50];
    strcpy(backup3, invalid3);
    printf("Teste 6 - Inválido: '%s' -> ", invalid3);
    printf("%s\n", removeGaps(invalid3) ? "SUCESSO" : "ERRO (esperado)");
    
    char invalid4[] = "10 + a * 3"; // Caractere inválido
    char backup4[50];
    strcpy(backup4, invalid4);
    printf("Teste 7 - Inválido: '%s' -> ", invalid4);
    printf("%s\n", removeGaps(invalid4) ? "SUCESSO" : "ERRO (esperado)");
    
    printf("=== Fim dos testes ===\n\n");
}

int main() {
    testRemoveGaps();
    return 0;
}