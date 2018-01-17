/* 
 Madrid, 20 de marzo de 2017.
 Autores: Carlos Luis Hojas García-Plaza y Rafael Hidalgo Alejo. Pareja 02.
 PROGRAMACIÓN II - ESCUELA POLITÉCNICA SUPERIOR DE LA UNIVERSIDAD AUTÓNOMA DE MADRID
 PRÁCTICA 2 
 */

/*Observación importante: A lo largo del código se utilizan sentencias para comprobar posibles errores y que no serán comentadas.*/

#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

struct _Graph {  
    int matrizAdy[MAX_NODES][MAX_NODES];
    Node **nodosSaved;
    int naristas;
    int nnodos;
};

Graph * graph_ini() {
    Graph *g=NULL;
    
    g = (Graph *) malloc(sizeof (Graph));
    if (g == NULL)return NULL;
    g->nodosSaved = (Node **) malloc(MAX_NODES * sizeof (Node*));
    if (g->nodosSaved == NULL) {
        free(g);
        return NULL;
    }
    
    g->nnodos = 0;
    g->naristas = 0;

    return g;
}


void graph_destroy(Graph *g) {
    int i=0;
    if (g == NULL)return;
    for (i = 0; i < g->nnodos; i++) {
        node_destroy(g->nodosSaved[i]);
    }
    free(g);
}


int graph_getNnodes(const Graph * g) {
    if (g == NULL)return -1;
    return g->nnodos;
}

int* graph_getNodeIds(const Graph * g) {
    int *ids=NULL, i=0;
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

    g->nodosSaved[g->nnodos] = node_copy(n);
    if (g->nodosSaved[g->nnodos] == NULL) return NULL;
    g->nnodos++;

    return g;
}

int find_node_index(const Graph * g, int nId1) {
    int i=0;
    if (g == NULL)return -1;
    for (i = 0; i < g->nnodos; i++) {
        if (node_getId(g->nodosSaved[i]) == nId1) {
            return i;
        }
    }
    return -1;
}

Graph * graph_addEdge(Graph * g, const int nId1, const int nId2) {
    int i=0, j=0;
    if (g == NULL)return NULL;
    i = find_node_index(g, nId1);
    j = find_node_index(g, nId2);
    
    if (g->matrizAdy[i][j] == 0) {
        g->naristas++;
    }
    g->matrizAdy[i][j] = 1;
    return g;
}

Node * graph_getNode(const Graph * g, int nId) {
    int i=0;
    if (g == NULL)return NULL;
    for (i = 0; i < g->nnodos; i++) {
        if (nId == node_getId(g->nodosSaved[i])) {
            return g->nodosSaved[i];
        }
    }
    return NULL;
}

Bool graph_areConnected(const Graph * g, const int nId1, const int nId2) {
    int i=0, j=0;
    if (g == NULL)return FALSE;
    i = find_node_index(g, nId1);
    j = find_node_index(g, nId2);
    if (g->matrizAdy[i][j] == 1)return TRUE;
    return FALSE;
}

int graph_getNumberOfConnectionsFrom(const Graph * g, const int fromId) {
    int i=0, j=0, k = 0;
    if (g == NULL)return -1;
    i = find_node_index(g, fromId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[i][j] == 1) {
            k++;
        }
    }
    return k;

}

int* graph_getConnectionsFrom(const Graph * g, const int fromId) {
    int i=0, j=0, k = 0, *ids = NULL;
    if (g == NULL)return NULL;
    ids = (int*) malloc(MAX_NODES * sizeof (int));
    i = find_node_index(g, fromId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[i][j] == 1) {
            ids[k] = node_getId(g->nodosSaved[j]);
            k++;
        }
    }
    return ids;
}


int graph_getNumberOfConnectionsTo(const Graph * g, const int toId) {
    int i=0, j=0, k = 0;
    if (g == NULL)return -1;
    i = find_node_index(g, toId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[j][i] == 1) {
            k++;
        }
    }
    return k;
}

int* graph_getConnectionsTo(const Graph * g, const int toId) {
    int i=0, j=0, k = 0, *ids = NULL;
    if (g == NULL)return NULL;
    ids = (int*) malloc(MAX_NODES * sizeof (int));
    i = find_node_index(g, toId);
    for (j = 0; j < MAX_NODES; j++) {
        if (g->matrizAdy[j][i] == 1) {
            ids[k] = node_getId(g->nodosSaved[j]);
            k++;
        }
    }
    return ids;
}

int graph_print(FILE *pf, const Graph * g) {
    int c = 0, i=0, j=0;
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

            c += fprintf(pf, "%d ", g->matrizAdy[i][j]);
        }
        c += fprintf(pf, "\n");
    }
    return c;
}


