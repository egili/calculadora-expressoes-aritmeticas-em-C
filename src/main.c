#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main() {
    Fila fil;
    newFila (&fil,10);
    
    int* i;

    i = (int*)malloc(sizeof(int));
    *i = 2;
    putOnFila (&fil,(ElementoDeFila)i);
    i = NULL;

    i = (int*)malloc(sizeof(int));
    *i = 3;
    putOnFila (&fil,(ElementoDeFila)i);
    i = NULL;

    i = (int*)malloc(sizeof(int));
    *i=5;
    putOnFila (&fil,(ElementoDeFila)i);
    i = NULL;

    while (!isFilaVazia(fil)) {
        getFromFila(fil,(ElementoDeFila*)&i);
        removeFromFila(&fil);
        printf("%d ",*i);
        free(i);
        i = NULL;
    }

    freeFila(&fil);

    return 0;
}