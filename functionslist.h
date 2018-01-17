

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void destroy_intp_function(void* e) ;

void * copy_intp_function(const void* e) ;

int print_intp_function(FILE * f, const void* e);


/* La siguiente función permite comparar dos elementos, devolviendo un número positivo, negativo o cero 
 * según si el primer argumento es mayor, menor o igual que el segundo argumento */
int cmp_intp_function(const void*, const void*);


#endif /* FUNCTIONS_H */

