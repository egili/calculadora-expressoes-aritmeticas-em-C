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
            if (isNumeroAtualmente && isdigit(*(ponteiroTemporario + 1)) && *(ponteiroTemporario + 1) != '\0') { //* isDigit serve para validar se o caractere é um dígito decimal 0-9
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