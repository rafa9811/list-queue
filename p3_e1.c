#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "Node.h"

#define MAXTAM 128 

int main(int argc, char **argv) {
    FILE *f=NULL;
    Queue *q1=NULL,*q2=NULL,*q3=NULL;
    Node *n=NULL;
    int i,num,id,mid;
    char name[MAXTAM];
    void *e;
   
    q1=queue_ini(destroy_node_function,copy_node_function,print_node_function);
    q2=queue_ini(destroy_node_function,copy_node_function,print_node_function);
    q3=queue_ini(destroy_node_function,copy_node_function,print_node_function);
    
    if (argc != 2 ) {
	printf("Usage: ./p3_e1 nombre_fichero\n");
	exit(-1);
    }
    
    f=fopen(argv[1],"r");
    if(f==NULL){
        printf("Error abriendo el archivo: ");
        return -1;
    }
    
    if(queue_isEmpty(q1)==TRUE){
           printf("Cola 1: Queue vacia\n"); 
        }
    if(queue_isEmpty(q2)==TRUE){
          printf("Cola 2: Queue vacia\n");   
        }
    if(queue_isEmpty(q3)==TRUE){
           printf("Cola 3: Queue vacia\n");  
        }
    
    fscanf(f, "%d", &num);
    while (!feof(f)) {
        for (i = 0; i < num; i++) {
            n = node_ini();
            fscanf(f, "%d", &id);
            fscanf(f, "%s", name);

            n = node_setId(n, id);
            n = node_setName(n, name);

            q1 = queue_insert(q1, (void *) n);
            node_destroy(n);
            if (queue_isEmpty(q1) == TRUE) {
                printf("Cola 1: Queue vacia\n");
            }
            else{
                printf("Cola 1 con %d elementos: ",queue_size(q1));
                queue_print(stdout, q1);
                printf("\n");
            }
            if (queue_isEmpty(q2) == TRUE) {
                printf("Cola 2: Queue vacia\n");
            }
            if (queue_isEmpty(q3) == TRUE) {
                printf("Cola 3: Queue vacia\n");
            }
        }
    }
    mid=num/2;
    
    printf("<<<Pasando la primera mitad de Cola 1 a Cola 2\n");
    for (i = 0; i < mid; i++) {
        e = queue_extract(q1);
        q2 = queue_insert(q2, e);

        if (queue_isEmpty(q1) == TRUE) {
            printf("Cola 1: Queue vacia\n");
        } else {
            printf("Cola 1 con %d elementos: ", queue_size(q1));
            queue_print(stdout, q1);
            printf("\n");
        }
        if (queue_isEmpty(q2) == TRUE) {
            printf("Cola 2: Queue vacia\n");
        } else {
            printf("Cola 2 con %d elementos: ", queue_size(q2));
            queue_print(stdout, q2);
            printf("\n");
        }
        if (queue_isEmpty(q3) == TRUE) {
            printf("Cola 3: Queue vacia\n");
        } else {
            printf("Cola 3 con %d elementos: ", queue_size(q3));
            queue_print(stdout, q3);
            printf("\n");
        }
    }
    
    printf("<<<Pasando la segunda mitad de Cola 1 a Cola 3\n");
    for (; mid < num; mid++) {
        e = queue_extract(q1);
        q3 =queue_insert(q3, e);

        if (queue_isEmpty(q1) == TRUE) {
            printf("Cola 1: Queue vacia\n");
        } else {
            printf("Cola 1 con %d elementos: ", queue_size(q1));
            queue_print(stdout, q1);
            printf("\n");
        }
        if (queue_isEmpty(q2) == TRUE) {
            printf("Cola 2: Queue vacia\n");
        } else {
            printf("Cola 2 con %d elementos: ", queue_size(q2));
            queue_print(stdout, q2);
            printf("\n");
        }
        if (queue_isEmpty(q3) == TRUE) {
            printf("Cola 3: Queue vacia\n");
        } else {
            printf("Cola 3 con %d elementos: ", queue_size(q3));
            queue_print(stdout, q3);
            printf("\n");
        }
    }
    
    queue_destroy(q1);
    queue_destroy(q2);
    queue_destroy(q3);
    fclose(f);

    return 0;
}
