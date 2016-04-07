#include <stdio.h>
#include <stdlib.h>
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
edge* getEdgesFrom(graph* g, int index);

void initializeGraph(graph* g, int graphSize);
// node* createNode(int index);
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

void enqueue(minQueue* q, queueItem* item);
void dequeue(minQueue* q, queueItem* item);
queueItem* getMin(minQueue* q);
void setPriority(minQueue* q, int node, int priority);
int queueIsEmpty(minQueue* q);

void enqueue(minQueue* queue, queueItem* item) {
    if(queue->qSize == 0) { // We need to set up a queue
        queue->qSize = 1;
        queue->q = malloc(sizeof(queueItem));
    } else { // Expand the queue
        queue->qSize++;
        queue->q = realloc(queue->q, sizeof(queueItem) * queue->qSize);
    }
    queue->q[queue->qSize - 1] = item;
}

void dequeue(minQueue* queue, queueItem* item) {
    int i;
    for(i=0; i<(queue->qSize); i++) {
      if(queue->q[i] == item) { // Now we have to make a new queue and copy everything over that we want to save
          int j;
          for(j=i; j<(queue->qSize - 1); j++) {
              queue->q[j] = queue->q[j+1];
          }
          queue->qSize--;
          printf("\tDEBUG QSIZE: %d\n", queue->qSize);
          queue->q = realloc(queue->q, sizeof(queueItem) * queue->qSize);
      }
    }
}

queueItem* getMin(minQueue* queue) {
    if(queueIsEmpty(queue) == TRUE) {
        return NULL;
    }
    queueItem* m = queue->q[0];
    int i;
    for(i=1; i<(queue->qSize); i++) { // i=1 to skip first member `m`
        if(queue->q[i]->priority < m->priority && queue->q[i]->priority != -1) {
            m = queue->q[i];
        }
    }
    dequeue(queue, m);
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
    
    printf("\nTesting queue\n");
    minQueue* queue = malloc(sizeof(minQueue));
    int i;
    for(i=0; i<(g->number_of_nodes); i++) {
        queueItem* item = malloc(sizeof(queueItem));
        item->node = i+1;
        item->priority = 10;
        enqueue(queue, item);
    }
    
    printf("Queue size: %d\n", queue->qSize); 
    if(queueIsEmpty(queue) == TRUE) {
        printf("Queue is empty\n");
    } else {
        printf("Queue has members\n");
    }
    
    for(i=0; i<queue->qSize; i++) {
        dequeue(queue, queue->q[i]);
    }
    printf("Queue size: %d\n", queue->qSize); 
    if(queueIsEmpty(queue) == TRUE) {
        printf("Queue is empty\n");
    } else {
        printf("Queue has members\n");
    }
    printf("Done\n");
    // TODO: Cleanup
    free(g);
}