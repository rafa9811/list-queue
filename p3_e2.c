#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "queue.h"
#include "types.h"

#define MAX 255

Graph * read_graph_from_file(char * filename){
	FILE * in=NULL;
	Graph * g=NULL;
	Node * n=NULL;
        char buff[MAX], name[MAX];
	int i=0, nnodes=0, id1=0, id2=0;

	g = graph_ini();
	if (g == NULL){
		return NULL;
	}
	in = (FILE*) fopen(filename, "r");
	if (in == NULL){
		graph_destroy(g);
		return NULL;
	}
	/* Format: nnodes \n node1id node1name ... nodenid nodenname connection1a connection1b ... */
    fgets(buff, MAX, in);
    sscanf(buff, "%d", &nnodes);
    /* read nodes line by line */
    for(i=0; i<nnodes;i++) {
        fgets(buff, MAX, in);
		sscanf(buff, "%d %s", &id1, name);
		/* create node */
		n = node_ini();
		if (node_setId(n, id1) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		if (node_setName(n, name) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		/* add node to graph */
		if (graph_addNode(g, n) == NULL){
			fclose (in);
			node_destroy(n);
			graph_destroy(g);
			return NULL;
		}
		/* destroy node */
		node_destroy(n);
	}
	/* read connections */
	while (!feof(in)){
        fgets(buff, MAX, in);
		sscanf(buff, "%d %d", &id1, &id2);
		if (graph_addEdge(g, id1, id2) == NULL){
			fclose (in);
			graph_destroy(g);
			return NULL;
		}
	}

	fclose (in);

	return g;
}


Bool recorrer(Graph *g,int id1, int id2){
    int numnodos=0,numcon=0,i=0;    
    Queue *q1=NULL;
    Queue *q2=NULL;
    
    Node *n=NULL, *n2=NULL;
    int *idscon, *vdescubiertos;
    void *v;

    if(g==NULL)return FALSE;

    q1=queue_ini(destroy_node_function,copy_node_function,print_node_function);
    q2=queue_ini(destroy_node_function,copy_node_function,print_node_function);
    n=node_ini();
    n2=node_ini();
    numnodos=graph_getNnodes(g);
    idscon=(int*)malloc(numnodos*sizeof(int));
    vdescubiertos=(int*)malloc(numnodos*sizeof(int));
    
    
    for(i=0;i<numnodos;i++){
        vdescubiertos[i]=0;
    }
   
    n=graph_getNode(g, id1);
    q1=queue_insert(q1,(void*)n);
    
    
    while (queue_isEmpty(q1)==FALSE){
        v=queue_extract(q1);
        q2=queue_insert(q2,v);
        n=(Node *)v;
        
        numcon=graph_getNumberOfConnectionsFrom(g,node_getId(n));
        
        idscon=graph_getConnectionsFrom(g,node_getId(n));
              
        
        for(i=0;i<numcon;i++){
           
            if (vdescubiertos[idscon[i]-1] == 0) {
                vdescubiertos[idscon[i]-1] = 1;
                
                n2 = graph_getNode(g, idscon[i]);
                if (idscon[i] == id2) {
                    free(idscon);
                    q2=queue_insert(q2,(void*)n2);
                    printf("Es posible encontrar un camino.\n");
                    free(vdescubiertos);
                                      
                    queue_destroy(q1);
                    queue_destroy(q2);                
                    
                    return TRUE;
                }
                q1=queue_insert(q1,(void*)n2);
                
            }
        }   
    }
    printf("No es posible encontrar un camino.\n");
    free(vdescubiertos);
    free(idscon);
    queue_destroy(q1);
    queue_destroy(q2);
    
    return FALSE;
}

int main(int argc, char **argv) {
    Graph *g=NULL;
    int e=0, s=0;
    if(argc!=4){
    printf("Error. Introduzca argumentos de entrada: File nodo nodo . Por ejemplo (en este caso): G1.txt 1 3 // G1.txt 3 1");
    return -1;
    }
    e=atoi(argv[2]);
    s=atoi(argv[3]);
    g=read_graph_from_file(argv[1]);
    recorrer(g,e,s);
    graph_destroy(g);
    return 0;
}

