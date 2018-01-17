
#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

#define MAXQUEUE 64

struct _Queue {
    void** head;
    void** end;
    void* item[MAXQUEUE];
    destroy_elementqueue_function_type destroy_element_function;
    copy_elementqueue_function_type copy_element_function;
    print_elementqueue_function_type print_element_function;
};

Queue* queue_ini(destroy_elementqueue_function_type f1, copy_elementqueue_function_type f2,print_elementqueue_function_type f3){
    Queue *q=NULL;
    
    q=(Queue *)malloc(sizeof(Queue));
    if(q==NULL)return NULL;
    q->destroy_element_function=f1;
    q->copy_element_function=f2;
    q->print_element_function=f3;
    
    q->end  = &(q->item[0]); /* pq->rear = pq->datos  end=rear*/
    q->head = &(q->item[0]); /* pq->front = pq->datos head=front*/
    
    return q;
}

void queue_destroy(Queue *q) {
        if (q==NULL) return;
        while (q->head != q->end) {
            q->destroy_element_function(*(q->head));
            if (q->head != &(q->item[MAXQUEUE - 1])) {
                q->head = q->head + 1;
            } else {
                q->head = &(q->item[0]);
            }
         }
        free(q);
    }

Bool queue_isEmpty(const Queue *q) {
    if (q == NULL) {
        return FALSE;
    }
    if (q->end == q->head) {
        return TRUE;
    }
    return FALSE;
}

Bool queue_isFull(const Queue* q) {
    void **aux=NULL;
    if (q == NULL) {
        return FALSE;
    }
    /* Apuntamos aux donde avanzaria rear si se incrementase */
    if (q->end == &(q->item[MAXQUEUE - 1])) {
        aux = (void**)&(q->item[0]); /* Al comienzo del array.*/
    }                        /* Equivale a aux = pq->datos*/
    else {
        aux = q->end + 1; /* A la siguiente posicion*/
    }
    /* Si aux (que es rear+1) coincide con front, cola llena*/
    if (aux == q->head) {
        return TRUE;
    }
    return FALSE;
}

Queue* queue_insert(Queue *q, const void* pElem) {
    void *aux = NULL;
    if (q == NULL || pElem == NULL || queue_isFull(q) == TRUE) {
        return NULL;
    }
    aux = q->copy_element_function(pElem);
    if (aux == NULL) {
        return NULL;
    }
    /* Guardamos el dato en el rear */
    *(q->end) = aux;
    
    /* Actualizamos el rear */
    if (q->end == &(q->item[MAXQUEUE - 1])) {
        q->end = &(q->item[0]); /* pq->rear = pq->datos*/
    } else {
        q->end++;
    }
    return q;
}

void * queue_extract(Queue *q) {
    void *pe = NULL;
    if (q == NULL || queue_isEmpty(q) == TRUE) {
        return NULL;
    }
    /* Recuperamos el dato del front */
    pe = *(q->head);
    /* Actualizamos el front */
    if (q->head == &(q->item[MAXQUEUE - 1])) {
        q->head = &(q->item[0]); /* pq->front= pq->datos*/
    } else {
        q->head++;
    }
    return pe;
}

int queue_size(const Queue *q) {
    int i=0;
    void **aux;
    if (q == NULL)return -1;
    else if (queue_isEmpty(q) == TRUE)return 0;
    else if (queue_isFull(q) == TRUE) return MAXQUEUE;
    
    aux=q->head;

    while (aux != q->end) {
        i++;
        if (aux != &(q->item[MAXQUEUE - 1])) {
            aux = aux + 1;
        } else {
            aux = (void**)&(q->item[0]);
        }

    }
    return i;
}

int queue_print(FILE *pf, const Queue *q){
    void **aux=NULL;
    int i=0;    
    if(pf==NULL || q==NULL)return -1;
    
    aux=q->head;
    
    while (aux != q->end) {
            
            i+=q->print_element_function(pf,*(aux));
            if (aux != &(q->item[MAXQUEUE - 1])) {
                aux = aux + 1;
            } else {
                aux = (void**)&(q->item[0]);
            }
            
        }
    return i;
}

