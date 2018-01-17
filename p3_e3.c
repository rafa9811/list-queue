

#include <stdio.h>
#include <stdlib.h>

#include "list.h"


int main(int argc, char** argv) {
    FILE *f=NULL;
    int *x=NULL,c,i,n,nl1,nl2;
    void *v;
    List *list=NULL,*list2=NULL;
    
    list=list_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
    list2=list_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
    x=(int*)malloc(sizeof(int));
    
    f=fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stdout,"Error abriendo el archivo.");
        return -1;
    }
    
    while(!feof(f)){
        fscanf(f,"%d",x);
        if (*x % 2 == 0) {
            v = (void*) x;
            if(list_insertFirst(list, v)==NULL){
                printf("Error insertando al principio");
		free(v);
		free(x);
                list_free(list);
                return -1;
            }
        }
        else{
            v = (void*) x;
            if(list_insertLast(list, v)==NULL){
                printf("Error insertando al final");
                free(v);
                free(x);
		list_free(list);
                return -1;
            }
        }
        nl1=list_size(list);
        fprintf(stdout,"Lista con %d elementos\n",nl1);
        c=list_print(stdout, list);
        if(c==-1){
            printf("Error en list print.");
        }
        fprintf(stdout,"\n");
        
    }
    
    fprintf(stdout,"\n\n");
    fprintf(stdout,"Sacando la primera mitad de la lista por el principio\n");
    
    n=list_size(list);
    for(i=0;i<(n/2);i++){
        v=list_extractFirst(list);
        list2=list_insertInOrder(list2,v);
        free(v);
        nl1=list_size(list);
        fprintf(stdout,"Lista 1 con %d elementos\n",nl1);
        c=list_print(stdout, list);
        if(c==-1){
            printf("Error en list print.");
            return -1;
        }
        fprintf(stdout,"\n");
        
        nl2=list_size(list2);
        fprintf(stdout,"Lista 2 con %d elementos\n",nl2);
        c=list_print(stdout, list2);
        if(c==-1){
            printf("Error en list print.");
            return -1;
        }
        fprintf(stdout,"\n");
    }
    
    
    fprintf(stdout,"\n\n");
    fprintf(stdout,"Sacando la segunda mitad de la lista por el final\n");
    
    
    for(;i<n;i++){
        v=list_extractLast(list);
        list2=list_insertInOrder(list2,v);
        free(v);
        nl1=list_size(list);
        fprintf(stdout,"Lista 1 con %d elementos\n",nl1);
        c=list_print(stdout, list);
        if(c==-1){
            printf("Error en list print.");
            return -1;
        }
        else if(c==-2){
            printf("Lista vacìa.");
        }
        fprintf(stdout,"\n");
        
        nl2=list_size(list2);
        fprintf(stdout,"Lista 2 con %d elementos\n",nl2);
        c=list_print(stdout, list2);
        if(c==-1){
            printf("Error en list print.");
            return -1;
        }
        fprintf(stdout,"\n");
    }
    
    list_free(list);
    list_free(list2);
    free(x);
    fclose(f);
    
    return 0;
}

