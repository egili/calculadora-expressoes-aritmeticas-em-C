#include "basics.h"
#include <ctype.h>
#include <string.h>

boolean removeGaps(char* str) {
    if (str == NULL) {
        return false;
    }

    char* tempPtr        = str;
    boolean inNumber     = false;
    boolean lastWasDigit = false;
    
    while (*tempPtr != '\0') {
        if (*tempPtr == ' ') {
            if (inNumber && isdigit(*(tempPtr + 1)) && *(tempPtr + 1) != '\0') {
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