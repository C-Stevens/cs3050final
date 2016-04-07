#include <stdio.h>
#include <stdlib.h>

typedef struct edge {
    struct node* toNode;
    int weight;
} edge;

typedef struct node {
    int index;
    int number_of_edges; // Used for edge array construction
    edge **edges;
} node;

typedef struct graph {
    int number_of_nodes;
    node **nodes;
} graph;

// Graph functions
void appendEdge(node* n, edge* e);
node* getNode(graph* g, int index);
void addEdge(graph* g, int fromNode, int toNode, int weight);
edge* getEdgesFrom(graph* g, int index);

void initializeGraph(graph* g, int graphSize);
// node* createNode(int index);
// End graph functions

// Queue functions
typedef struct queueItem {
    node* node;
    int priority;
} queueItem;
typedef struct minQueue {
    //
} minQueue;
// End queue functions

void initializeGraph(graph* g, int graphSize) {
    g->number_of_nodes = graphSize;
    g->nodes = malloc(sizeof(node) * g->number_of_nodes);
    int i;
    for(i=0; i<(g->number_of_nodes); i++) {
        node *newNode = (node*)malloc(sizeof(node));
        newNode->index = i+1; // Graph is not 0-indexed
        g->nodes[i] = newNode;
    }
}

node* getNode(graph* g, int index) {
    return g->nodes[index-1];
}

void appendEdge(node* n, edge* e) {
    if(n->number_of_edges == 0) { // No edges yet
        n->edges = malloc(sizeof(edge));
        n->number_of_edges = 1;
    } else { // Increase the edges array with realloc()
        n->number_of_edges++;
        n->edges = realloc(n->edges, sizeof(edge) * n->number_of_edges);
    }
    printf("\tDEBUG # of edges: %d\n", n->number_of_edges); //DEBUG
    n->edges[n->number_of_edges - 1] = e;
}

void addEdge(graph* g, int fromNode, int toNode, int weight) {
    node* n = getNode(g, fromNode);
    edge* e = malloc(sizeof(edge));
    e->weight = weight;
    e->toNode = getNode(g, toNode);
    appendEdge(n, e);
}

// node* createNode(int index) {
//     node* newNode = malloc(sizeof(node));
//     newNode->index = index;
//     newNode->number_of_edges = 0;
//     return newNode;
// }

int main(void) {
    graph* g = malloc(sizeof(graph));
    initializeGraph(g, 6); // GRAPH SIZE 6 BURNED IN

    printf("Making nodes\n");
    addEdge(g, 2, 3, 10);
    addEdge(g, 1, 4, 7);
    addEdge(g, 1, 3, 3);
    addEdge(g, 3, 4, 3);
    addEdge(g, 4, 5, 1);
    printf("Done\n");
    
    // TODO: Cleanup
    free(g);
}