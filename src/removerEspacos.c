#include "basics.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

boolean removerEspacos(char* str) {
    if (str == NULL) {
        return false;
    }

    // Primeiro, verificar se há caracteres inválidos
    char* ponteiroLeitura = str;
    while (*ponteiroLeitura != '\0') {
        if (!isspace(*ponteiroLeitura) && 
            !isdigit(*ponteiroLeitura) && 
            !strchr("+-*/().^", *ponteiroLeitura)) {
            printf("Erro: Caractere inválido '%c'\n", *ponteiroLeitura);
            return false;
        }
        ponteiroLeitura++;
    }

    // Verificar se há espaços entre dígitos
    ponteiroLeitura = str;
    boolean emNumero = false;
    boolean espacoEncontrado = false;
    
    while (*ponteiroLeitura != '\0') {
        if (isdigit(*ponteiroLeitura)) {
            if (espacoEncontrado && emNumero) {
                printf("Erro: Espaço entre dígitos não permitido\n");
                return false;
            }
            emNumero = true;
            espacoEncontrado = false;
        } 
        else if (isspace(*ponteiroLeitura)) {
            if (emNumero) {
                espacoEncontrado = true;
            }
        } 
        else {
            // Operador ou parêntese
            emNumero = false;
            espacoEncontrado = false;
        }
        ponteiroLeitura++;
    }

    // Agora remover os espaços
    ponteiroLeitura = str;
    char* ponteiroEscrita = str;

    while (*ponteiroLeitura != '\0') {
        if (!isspace(*ponteiroLeitura)) {
            *ponteiroEscrita = *ponteiroLeitura;
            ponteiroEscrita++;
        }
        ponteiroLeitura++;
    }

    *ponteiroEscrita = '\0';
    
    return true;
}