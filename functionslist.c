#include <stdlib.h>
#include <stdio.h>

#include "functionslist.h"

/*
 * En este fichero se definen las funciones de destrucción, copia e impresión de elementos a almacenar en
 * una pila para distintos tipos de datos
 */

/* Las siguientes funciones se usarán cuando se quieran guardar enteros en la pila. Ojo! Estas funciones
reciben un puntero a entero, no una estructura con un puntero a entero (como en el ejercicio P2_E1) */
void destroy_intp_function(void* e) {
    free((int*) e);
}

void * copy_intp_function(const void* e) {
    int * dst;
    if (e == NULL)
        return NULL;
    dst = (int*) malloc(sizeof (int));
    /*Copiamos el elemento*/
    *(dst) = *((int*) e);
    return dst;
}

int print_intp_function(FILE * f, const void* e) {
    if (f != NULL && e != NULL)
        return fprintf(f, "[%d]", *((int*) e));
    return -1;
}

/* La siguiente función permite comparar dos elementos, devolviendo un número positivo, negativo o cero 
 * según si el primer argumento es mayor, menor o igual que el segundo argumento */
int cmp_intp_function(const void *n1, const void *n2){
    int *a=NULL,*b=NULL;
    
    a=(int *)n1;
    b=(int *)n2;
    
    if(*a<*b){
        return -1;
    }
    else if (*a>*b){
        return 1;
    }
    else return 0;
}



