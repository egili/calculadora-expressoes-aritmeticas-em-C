#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

int main()
{
    Fila fil;
    nova_fila (&fil,10);
    
    int*  i;

    i=(int*)malloc(sizeof(int));
    *i=2;
    guarde_na_fila (&fil,(ElementoDeFila)i);
    i=NULL;

    i=(int*)malloc(sizeof(int));
    *i=3;
    guarde_na_fila (&fil,(ElementoDeFila)i);
    i=NULL;

    i=(int*)malloc(sizeof(int));
    *i=5;
    guarde_na_fila (&fil,(ElementoDeFila)i);
    i=NULL;

    while (!fila_vazia(fil))
    {
        recupere_da_fila(fil,(ElementoDeFila*)&i);
        remova_elemento_da_fila(&fil);
        printf("%d ",*i);
        free(i);
        i=NULL;
    }

    free_fila(&fil);

    return 0;
}