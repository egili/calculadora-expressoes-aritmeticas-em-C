#include "basics.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>

boolean removerEspacos(char* str) {
    if (str == NULL) {
        return false;
    }

    char* stringAuxiliar               = str;
    boolean isNumeroAtualmente         = false; 
    boolean ultimoCaracterLidoEhDigito = false; 
    
    while (*stringAuxiliar != '\0') {
        if (*stringAuxiliar == ' ') {
            if (isNumeroAtualmente && isdigit(*(stringAuxiliar + 1)) && *(stringAuxiliar + 1) != '\0') { //* isDigit serve para validar se o caractere é um dígito decimal 0-9
                return false;
            }
        } else if (isdigit(*stringAuxiliar)) {
            if (!isNumeroAtualmente && ultimoCaracterLidoEhDigito) {
                return false; 
            }
            isNumeroAtualmente = true;
            ultimoCaracterLidoEhDigito = true;
        } else {
            isNumeroAtualmente = false;
            ultimoCaracterLidoEhDigito = false;
            
            if (!strchr("+-*/().", *stringAuxiliar)) {
                return false; 
            }
        }
        stringAuxiliar++;
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