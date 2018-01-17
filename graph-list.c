#include "graph.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _Graph {
    Node *nodosSaved[MAX_NODES];
    List* out_connections[MAX_NODES]; /* Nodos a los que se puede ir desde un nodo i */
    List* in_connections[MAX_NODES]; /* Nodos que van a un nodo i */
    int naristas;
    int nnodos;
};

Graph * graph_ini() {
    Graph *g;
    int i;
    g = (Graph *) malloc(sizeof (Graph));
    if (g == NULL)return NULL;

    for (i = 0; i < MAX_NODES; i++) {
        g->out_connections[i] = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
        g->in_connections[i] = list_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
    }

    g->nnodos = 0;
    g->naristas = 0;

    return g;
}

void graph_destroy(Graph *g) {
    int i;
    if (g == NULL)return;
    for (i = 0; i < g->nnodos; i++) {
        node_destroy(g->nodosSaved[i]);
    }

    for (i = 0; i < MAX_NODES; i++) {
        list_free(g->out_connections[i]);
        list_free(g->in_connections[i]);
    }

    free(g);
}

int graph_getNnodes(const Graph * g) {
    if (g == NULL)return -1;
    return g->nnodos;
}

int* graph_getNodeIds(const Graph * g) {
    int *ids, i;
    if (g == NULL)return NULL;
    ids = (int*) malloc(g->nnodos * sizeof (int));
    if (ids == NULL)return NULL;
    for (i = 0; i < g->nnodos; i++) {
        ids[i] = node_getId(g->nodosSaved[i]);
    }

    return ids;
}

int graph_getNedges(const Graph * g) {
    if (g == NULL)return -1;
    return g->naristas;
}

Graph * graph_addNode(Graph * g, const Node* n) {
    if (g == NULL || n == NULL)return NULL;

    g->nodosSaved[g->nnodos] = node_copy((Node*)n);
    if (g->nodosSaved[g->nnodos] == NULL) return NULL;
    g->nnodos++;

    return g;
}

int find_node_index(const Graph * g, int nId1) {
    int i;
    if (g == NULL)return -1;
    for (i = 0; i < g->nnodos; i++) {
        if (node_getId(g->nodosSaved[i]) == nId1) {
            return i;
        }
    }
    return -1;
}

Graph * graph_addEdge(Graph * g, const int nId1, const int nId2) {
    int i, j,n1,n2;
    void *v1, *v2;
    int *x1=NULL, *x2=NULL;
    n1=(int)nId1;
    n2=(int)nId2;

    x1 = &n1;
    x2 = &n2;
    
    v1 = (void*)x1;
    v2 = (void*)x2;

    if (g == NULL)return NULL;
    i = find_node_index(g, nId1);
    j = find_node_index(g, nId2);
    if(i==-1 || j==-1)return NULL;

    if((g->out_connections[i] = list_insertLast(g->out_connections[i], v2))==NULL)return NULL;
    if((g->in_connections[j] = list_insertLast(g->in_connections[j], v1))==NULL)return NULL;
    
    g->naristas++;

    return g;
}

Node * graph_getNode(const Graph * g, int nId) {
    int i;
    if (g == NULL)return NULL;
    for (i = 0; i < g->nnodos; i++) {
        if (nId == node_getId(g->nodosSaved[i])) {
            return g->nodosSaved[i];
        }
    }
    return NULL;
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2) {
    int i, j, k,m;
    if (g == NULL)return FALSE;
    if(nId1==nId2)return FALSE;
    i = find_node_index(g, nId1);
    if(i==-1)return FALSE;
    
    j=list_size(g->out_connections[i]);
    if(j==-1)return FALSE;

    for (k = 0; k < j+1; k++) {
        m=*(int*)list_get(g->out_connections[i], k);
        if(m==-1)return FALSE;
        if (m == nId2)return TRUE;
    }
    return FALSE;
}

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
    int i, k = 0;
    if (g == NULL)return -1;
    i = find_node_index(g, fromId);

    k = list_size(g->in_connections[i]);
    return k;

}

int* graph_getConnectionsFrom(const Graph * g, const int fromId) {
    int i, j,m, k, *ids = NULL;
    int *r;
    List *list=NULL;
    
    r=(int*)malloc(sizeof(int));
    list=list_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
    
    if (g == NULL)return NULL;
    ids = (int*) malloc(MAX_NODES * sizeof (int));
    i = find_node_index(g, fromId);
    
    j=list_size(g->in_connections[i]);
    if(j==-1 || j==0)return NULL;

    /*for (k = 0,m=0; k < j; k++,m++) {
        m=*(int*) list_get(g->out_connections[i],k);
        ids[k] = m;
    }*/
    
    for(k=0;k<j;k++){
        r=(int*)list_extractFirst(g->in_connections[i]);
        m=*r;
        ids[k]=m;
        list=list_insertLast(list,(void*)r);
       
    }
    
    j=list_size(list);
    if(j==-1 || j==0)return NULL;
    
    for(k=0;k<j;k++){
        r=(int*)list_extractFirst(list);
        list=list_insertLast(list,(void*)r);
    }
    
    free(r);
    list_free(list);
    
    return ids;
}

int graph_getNumberOfConnectionsTo(const Graph * g, const int toId) {
    int i, k = 0;
    if (g == NULL)return -1;
    i = find_node_index(g, toId);
    k = list_size(g->out_connections[i]);

    return k;
}

int* graph_getConnectionsTo(const Graph * g, const int toId) {
    int i, j,m, k, *ids = NULL;
    int *r;
    List *list=NULL;
    
    r=(int*)malloc(sizeof(int));
    list=list_ini(destroy_intp_function, copy_intp_function, print_intp_function, cmp_intp_function);
    
    if (g == NULL)return NULL;
    ids = (int*) malloc(MAX_NODES * sizeof (int));
    i = find_node_index(g, toId);
    
    j=list_size(g->out_connections[i]);
    if(j==-1 || j==0)return NULL;

    /*for (k = 0,m=0; k < j; k++,m++) {
        m=*(int*) list_get(g->out_connections[i],k);
        ids[k] = m;
    }*/
    
    for(k=0;k<j;k++){
        r=(int*)list_extractFirst(g->out_connections[i]);
        m=*r;
        ids[k]=m;
        list=list_insertLast(list,(void*)r);
       
    }
    
    j=list_size(list);
    if(j==-1 || j==0)return NULL;
    
    for(k=0;k<j;k++){
        r=(int*)list_extractFirst(list);
        list=list_insertLast(list,(void*)r);
    }
    
    free(r);
    list_free(list);
    
    return ids;
}

int graph_print(FILE *pf, const Graph * g) {
    int c = 0, i, j;
    if (g == NULL) {
        return 0;
    }
    if (pf == NULL) {
        printf("Error abriendo el archivo.");
        return 1;
    }
    fprintf(pf, "N=%d, E=%d:\n", g->nnodos, g->naristas);
    for (i = 0; i < g->nnodos; i++) {
        c += fprintf(pf, "[%d, %s]", node_getId(g->nodosSaved[i]), node_getName(g->nodosSaved[i]));
        c += fprintf(pf, "->");
        for (j = 0; j < g->nnodos; j++) {
            if (graph_areConnected(g, node_getId(g->nodosSaved[i]), node_getId(g->nodosSaved[j]))==TRUE) {
                c += fprintf(stdout, "1 ");
            } else {
                c += fprintf(stdout, "0 ");
            }
        }
        c += fprintf(pf, "\n");
    }
    return c;
}




