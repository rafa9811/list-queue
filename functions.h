

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void destroy_intp_function(void* e) ;

void * copy_intp_function(const void* e) ;

int print_intp_function(FILE * f, const void* e);

/* Las siguientes se usarán cuando se quieran guardar nodos en la pila */
void destroy_node_function(void* e);

void * copy_node_function(const void* e);

int print_node_function(FILE * f, const void* e) ;


#endif /* FUNCTIONS_H */

