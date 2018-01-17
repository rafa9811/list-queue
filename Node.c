#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Node.h"
#include "types.h"
#define DIM 1000


struct _Node {
    char name[DIM];
    int id;
};


Node * node_ini() {
    return (Node*) malloc(sizeof (Node));
}


void node_destroy(Node * n) {
    if (n == NULL) return;
    free(n);
}


int node_getId(const Node * n) {
    int id;
    if (n == NULL) {
        return -1;
    }
    
    id = n->id;

    return id;
}


char* node_getName(const Node * n) {
    char *name = NULL;
    if (n == NULL) return NULL;
    name = (char*) malloc(50 * sizeof (char));
    strcpy(name, n->name);

    return name;
}


Node *node_setName(Node * n, const char* name) {
    if (name == NULL || n == NULL) return NULL;

    strcpy(n->name, name);

    return n;
}


Node * node_setId(Node * n, const int id) {
    if (n == NULL) {
        return NULL;
    }
    n->id = id;
    return n;
}


Bool node_equals(const Node * n1, const Node * n2) {
    if (n1 == NULL || n2 == NULL) {
        return FALSE;
    }
    if ((n1->id == n2->id) && (!strcmp(n1->name, n2->name))) return TRUE;
    return FALSE;
}


Node * node_copy(const Node * src) {
    Node *n2 = NULL;
    char *nameaux;
    if (src == NULL) return NULL;
    n2 = node_ini();
    nameaux= node_getName(src);
    n2=node_setId(n2, node_getId(src));
    n2=node_setName(n2, nameaux);
    free (nameaux);
    return n2;
}


int node_print(FILE *pf, const Node * n) {
    int c;
    if (pf == NULL || n == NULL) {
        return 0;
    }

    c = fprintf(pf, "[%d, %s]", n->id, n->name);

    return c;
}

