#include <stdio.h>
#include <stdlib.h>

#include "list.h"


typedef struct _NodeList {
    void *data;
    struct _NodeList *next;
} NodeList;

NodeList *node_list_crear(){
    NodeList *nl=NULL;
    
    nl=(NodeList *)malloc(sizeof(NodeList));
    
    nl->data=NULL;
    nl->next=NULL;
    
    return nl;
}

void *node_list_liberar(NodeList *nl){
    if(!nl) return NULL;
    free(nl->data);
    free(nl);
    return NULL;
    }


struct _List {
    NodeList *node;
    
    destroy_elementlist_function_type destroy_element_function;
    copy_elementlist_function_type copy_element_function;
    print_elementlist_function_type print_element_function;
    cmp_elementlist_function_type cmp_element_function;
};


/* Inicializa la lista reservando memoria e inicializa todos sus elementos. */
List* list_ini(destroy_elementlist_function_type f1, copy_elementlist_function_type f2, print_elementlist_function_type f3, cmp_elementlist_function_type f4){
    List *list = NULL;
    list = (List *) malloc(sizeof (List));
    if (!list) return NULL;
    list->node = NULL;
    
    list->destroy_element_function=f1;
    list->copy_element_function=f2;
    list->print_element_function=f3;
    list->cmp_element_function=f4;
    
    return list;
}

/* Libera la lista y todos sus elementos desde el principio */
void list_free(List *list){
    NodeList *pn = NULL;
    if (!list) return;
    while (list->node != NULL) {
        pn = list->node;
        list->node = list->node->next;
        node_list_liberar(pn);
    }
    free(list);
}
/* Comprueba si una lista está vacía o no. */
Bool list_isEmpty(const List* list) {
    if (!list) return TRUE;       /* Caso de error*/
    if (!list->node) return TRUE; /* Caso de lista vacía*/
    
    return FALSE;
}

/* Inserta al principio de la lista realizando una copia del elemento. */
List *list_insertFirst(List *list, const void *elem){
    NodeList *pn =NULL;
    if (!list || !elem) return NULL;
    pn = node_list_crear();
    if (!pn) {
        return NULL;
    }
    pn->data = list->copy_element_function(elem);
    if (!pn->data) {
        node_list_liberar(pn);
        return NULL;
    }
    
    if(list_isEmpty(list)==TRUE){
        list->node=pn;
	
    }
    else {
        pn->next = list->node; /*Apuntamos el nuevo nodo al antiguo primer nodo */
        list->node = pn;       /*Apuntamos la estructura de lsit al nuevo nodo, que ahora es el primero*/
    }
    free(pn->data);
    node_list_liberar(pn);
    return list;
}
List* list_insertLast(List* list, const void *elem){
    NodeList *pn = NULL, *qn = NULL;
    if (!list || !elem) return NULL;
    pn = node_list_crear();
    if (!pn) {
        return NULL;
    }
    pn->data = list->copy_element_function(elem); /*Creamos un nodo y guardamos el elemento*/
    if (!pn->data) {
        node_list_liberar(pn);
        return NULL;
    }
    if (list_isEmpty(list) == TRUE) { /*Si la lista esta vacía apuntamos el primer al nuevo y nodo*/
        list->node = pn;
        return list;
    }
    /*Vemos si el primer nodo apunta a null, lo que indica el final, si no vemos el siguiente, asi hsta encontramos el final*/
    for (qn = list->node; qn->next != NULL; qn = qn->next);
        
    qn->next = pn;
    free(pn->data);
    node_list_liberar(pn);
    return list;
}

/* Inserta en orden en la lista realizando una copia del elemento. */
/*Suponiendo que se ordena de menor a mayor*/
List* list_insertInOrder(List *list, const void *pElem){
    NodeList *pn=NULL,*qn=NULL,*kn=NULL;
    void *v;
    int i,n;
    
    if(!pElem || !list) return NULL;
    
    pn=node_list_crear();
    if(!pn)return NULL;
    
    v=(void *)pElem;
    pn->data=v;
    if(pn->data==NULL)return NULL;
    
    if(list_isEmpty(list)==TRUE){
        list->node=pn;
        return list;
    }
    
    n=list_size(list);
    if(n==-1)return NULL;
    
    for (i=0,qn=list->node;i<n;qn=qn->next,i++){
        if(list->cmp_element_function((int*)pn->data,(int*)qn->data)<0){ /*Si el data del nodo que queremos insertar es menor que el estamos comparando lo insertamos*/
            if(i==0){
               pn->next=qn;
               list->node=pn;
               return list;
            }
            pn->next=qn;
            kn->next=pn;
            return list;
        }
        kn=qn;
    }
    
    kn->next=pn; /*Si no es menor que ninguno lo insertamos al final*/
    
    return list;
    
}

/* Extrae del principio de la lista realizando una copia del elemento almacenado en dicho nodo. */
void * list_extractFirst(List* list){
    NodeList *pn = NULL;
    void *pe = NULL;
    if (!list || list_isEmpty(list) == TRUE) {
        return NULL;
    }
    pn = list->node;                             /*Hacemos una copia del primer nodo*/
    pe = list->copy_element_function(pn->data);  /*Hacemos una copia del data del primer elemento*/
    if (!pe) {
        return NULL;
    }
    
    list->node = pn->next; /*Apuntamos la estrcutra del list al siguiente del nodo que extraemos, que ahora es el primero*/
    node_list_liberar(pn); /*Liberamos el nodo auxiliar*/
    
    return pe;             /*Delvolvemos el dato del nodo que hemos extraido*/
}

/* Extrae del final de la lista realizando una copia del elemento almacenado en dicho nodo. */
void * list_extractLast(List* list){
    NodeList *pn = NULL;
    void *pe = NULL;
    if (!list || list_isEmpty(list) == TRUE) return NULL;
    
    /* Caso: 1 nodo*/
    if (!list->node->next) {
        pe = list->copy_element_function(list->node->data); /*Si solo hay un nodo hacemos una copia y lo eliminamos*/
        if (!pe) return NULL;
        node_list_liberar(list->node);
        list->node = NULL;
        return pe;
    }
    
    /* Caso: 2 o más nodos*/
    /* -> se situa pn en el penúltimo nodo de la lista dado que no se cumple el bucle es en el penlutimo*/
    for (pn = list->node; pn->next->next != NULL; pn = pn->next)
        ;
    pe = list->copy_element_function(pn->next->data); /*Hacemos una copia del dato del ultimo nodo*/
    if (!pe) return NULL;
    node_list_liberar(pn->next); /*liberamos el ultimo nodo*/
    pn->next = NULL;             /*Apuntamos el penultimo nodo a null lo que lo convierte en el ultimo nodo*/
    
    return pe;
}

/* Devuelve el elemento i-ésimo almacenado en la lista. En caso de error, devuelve NULL. */
/*Teniendo en cuenta que el primer elemento de la lista es el 1*/
const void* list_get(const List* list, int i){
    int n;
    NodeList *qn=NULL,*kn=NULL;
    if(!list)return NULL;
    
    if(i==0){
        return list->node->data;
    }
    for (n=0,qn = list->node; n<i; qn = qn->next,n++){   
        kn=qn;
    }
    return kn->data;
        
}

int list_size(const List* list){
    NodeList *qn=NULL;
    int i;
    
    if(!list)return -1;
    
    if(list_isEmpty(list)==TRUE)return 0;
    
    for (i=0,qn = list->node; qn->next != NULL; qn = qn->next,i++){
        /*Vamos recorriendo la lista e incrementando el contador*/
    }
    return i+1;
}

int list_print(FILE *fd, const List* list){
    NodeList *qn=NULL;
    int c,c2,n,i;
    
    if(fd==NULL || list==NULL)return -1;
    
    if(list_isEmpty(list)==TRUE)return -2; /*Asignamos un codigo de error diferente si la lista esta vacia*/
    
    n=list_size(list);
    if(n==-1)return -1;
    
    for(i=0,c=0,c2=0,qn=(NodeList*)list->node; i<n; qn=qn->next,i++){
        c=list->print_element_function(stdout,qn->data);
        if(c==-1)return -1; /*Por si la impresion del algun nodo falla*/
        c2+=c;
    }
    
    return c2;
}




