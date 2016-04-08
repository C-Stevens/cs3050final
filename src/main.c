#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <ctype.h>
#include "../include/input_error.h"
#define TRUE 1
#define FALSE 0

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
edge** getEdgesFrom(graph* g, int index);

void initializeGraph(graph* g, int graphSize);
// End graph functions

// Queue functions
typedef struct queueItem {
    int node;
    int priority;
} queueItem;
typedef struct minQueue {
    int qSize;
    queueItem** q;
} minQueue;
// End queue functions

// Traversal
void printDistancesFromOne(graph* g);

void enqueue(minQueue* q, queueItem* item);
void dequeue(minQueue* q, int itemIndex);
queueItem* getMin(minQueue* q);
void setPriority(minQueue* q, int node, int priority);
int queueIsEmpty(minQueue* q);

void enqueue(minQueue* queue, queueItem* item) {
    if(queue->qSize == 0) { // We need to set up a queue
        queue->qSize = 1;
        queue->q = malloc(sizeof(queueItem*));
    } else { // Expand the queue
        queue->qSize++;
        queue->q = realloc(queue->q, sizeof(queueItem*) * queue->qSize);
    }
    queue->q[queue->qSize - 1] = item;
}

void dequeue(minQueue* queue, int itemIndex) {
    if(queue->q == NULL || queueIsEmpty(queue) == TRUE) { // Given an empty queue
        return;
    }
    if(queue->qSize == 1) { // Queue size of one, destroy the queue
        free(queue->q);
        queue->q = NULL;
        queue->qSize = 0;
    }
    
    queueItem** newQueue = malloc(sizeof(queueItem*) * (queue->qSize - 1));
    int i;
    for(i=0; i<itemIndex; i++) { // Copy over the queue up until the break
        newQueue[i] = queue->q[i];
    }
    for(i=itemIndex+1; i<queue->qSize; i++) { // Copy over the queue after the break
        newQueue[i-1] = queue->q[i]; // i-1 to avoid copying over the gap
    }
    queue->qSize--;
    free(queue->q);
    queue->q = newQueue;
}

queueItem* getMin(minQueue* queue) {
    if(queueIsEmpty(queue) == TRUE) {
        return NULL;
    }
    queueItem* m = queue->q[0];
    int minIndex = 0;
    int i;
    for(i=1; i<(queue->qSize); i++) { // i=1 to skip first member `m`
        if(queue->q[i]->priority < m->priority && queue->q[i]->priority != -1) {
            m = queue->q[i];
            minIndex = i;
        }
    }
    dequeue(queue, minIndex);
    return(m);
}

void setPriority(minQueue* queue, int node, int priority) {
    int i;
    for(i=0; i<queue->qSize; i++) {
       if(queue->q[i]->node == node) {
           queue->q[i]->priority = priority;
           break;
       }
    }
}

int queueIsEmpty(minQueue* q) {
    if(q->qSize > 0) {
        return FALSE;
    }
    return TRUE;
}

void initializeGraph(graph* g, int graphSize) {
    g->number_of_nodes = graphSize;
    g->nodes = malloc(sizeof(node*) * g->number_of_nodes);
    int i;
    for(i=0; i<(g->number_of_nodes); i++) {
        node *newNode = malloc(sizeof(node));
        newNode->index = i+1; // Graph is not 0-indexed
        g->nodes[i] = newNode;
    }
}

void cleanupGraph(graph* g) {
    int i;
    for(i=0; i<(g->number_of_nodes); i++) {
        free(g->nodes[i]->edges);
        free(g->nodes[i]);
    }
    free(g->nodes);
}

node* getNode(graph* g, int index) {
    return g->nodes[index-1];
}

void appendEdge(node* n, edge* e) {
    if(n->number_of_edges == 0) { // No edges yet
        n->edges = malloc(sizeof(edge*));
        n->number_of_edges = 1;
    } else { // Increase the edges array with realloc()
        n->number_of_edges++;
        n->edges = realloc(n->edges, sizeof(edge*) * n->number_of_edges);
    }
    n->edges[n->number_of_edges - 1] = e;
}

void addEdge(graph* g, int fromNode, int toNode, int weight) {
    node* n = getNode(g, fromNode);
    edge* e = malloc(sizeof(edge));
    e->weight = weight;
    e->toNode = getNode(g, toNode);
    appendEdge(n, e);
}

edge** getEdgesFrom(graph* g, int index) {
    node* n = getNode(g, index);
    return n->edges;
}

void printDistancesFromOne(graph* g) {
    int* distances = malloc(sizeof(int) * g->number_of_nodes);
    int i;
    for(i=0; i<(g->number_of_nodes); i++) {
        distances[i] = -1;
    }
    distances[0] = 0; // Starting from vertex 1
    
    minQueue* queue = malloc(sizeof(minQueue));
    for(i=0; i<(g->number_of_nodes); i++) {
        queueItem* item = malloc(sizeof(queueItem));
        item->node = i+1;
        item->priority = distances[i];
        enqueue(queue,item);
    }
    
    while(queueIsEmpty(queue) != TRUE) {
        queueItem* item = getMin(queue);
        edge** edgeList = getEdgesFrom(g, item->node);
        
        int edgeListSize = getNode(g, item->node)->number_of_edges;
        int i;
        for(i=0; i<edgeListSize; i++) {
            int oldDist = distances[edgeList[i]->toNode->index - 1];
            int newDist = distances[item->node - 1] + edgeList[i]->weight;
            
            if(newDist < oldDist || oldDist == -1) {
                distances[edgeList[i]->toNode->index - 1] = newDist;
                setPriority(queue, item->node, newDist);
            }
        }
    }
    
    for(i=0; i<(g->number_of_nodes); i++) {
        printf("%d %d\n", i+1, distances[i]);
    }
        
    free(queue->q);
    free(queue);
    free(distances);
}

// File processing
void parseInputFile(char* filename, graph* g);

void parseInputFile(char* filename, graph* g) {
    FILE* input = fopen(filename, "r");
    if(input == NULL) {
        exit(FILE_FAILED_TO_OPEN);
    }
    
    int vertCount;
    fscanf(input, "%d\n", &vertCount); // Get # of vertices
    initializeGraph(g, vertCount);
    
    int v1, v2, weight;
    int count = 0;
    while(!feof(input)) {
        count = fscanf(input, "(%d,%d,%d)\n", &v1, &v2, &weight);
        if(count != 3) {
            fclose(input);
            if(count == 0) {
                exit(PARSING_ERROR_EMPTY_FILE);
            }
            exit(PARSING_ERROR_INVALID_FORMAT);
        }
        // Vertex integrity checks
        if(v1 < 1 || v2 < 1) { 
            fclose(input);
            exit(INTEGER_IS_NOT_A_VERTEX);
        }
        if(v1 > vertCount || v2 > vertCount) {
            fclose(input);
            exit(INTEGER_IS_NOT_A_VERTEX);
        }
        addEdge(g, v1, v2, weight);
    }
}

int main(int argc, char** argv) {
    if(argc != 2) {
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    // initialize
    graph* g = malloc(sizeof(graph));
    parseInputFile(argv[1], g);      
    
    // The fun part
    printDistancesFromOne(g);

    // Cleaning up
    cleanupGraph(g);
    free(g);
}