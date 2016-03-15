#include "../include/graph.h"

listNode* makeNode(int dst) {
    listNode* newNode = malloc(sizeof(listNode));
    newNode->dst = dst;
    newNode->next = NULL;
    return newNode;
}

graph* createGraph(int size) {
    graph* newGraph = malloc(sizeof(graph));
    newGraph->size = size;
    newGraph->lists = malloc(sizeof(adjList) * size);
    printf("\tGraph set up\n"); //DEBUG
    
    int i;
    for(i=0; i<size; i++) { // Create `size` number of empty adjacency lists at this graph struct's list array
        printf("\tAdding a new list\n"); //DEBUG
        newGraph->lists[i].head = NULL;
    }
    
    return newGraph;
}

void createEdge(graph* graph, int src, int dst) {
    // Add an edge from src to dst
    listNode* newNode = makeNode(dst);
    newNode->next = graph->lists[src-1].head;
    graph->lists[src-1].head = newNode;
    
    // Add an edge from dst to src
    newNode = makeNode(src);
    newNode->next = graph->lists[dst-1].head;
    graph->lists[dst-1].head = newNode;
}

void enqueue(queue q, visitedNode* input) {
    input->prev = NULL;
    input->next = q->head;
    if(q->head == NULL) { //empty queue
        q->head = input;
        q->tail = input;
    } else {
        q->head->prev = input;
        q->head = input;
    }
}

visitedNode* dequeue(queue q) {
    output = q->tail;
    if(output == NULL) {
        return output; // Return NULL
    }
    q->tail = output->prev;
    q->tail->next = NULL;
    return output;
}

int shortestNodeDistance(graph* graph, int dst) {
    queue* q = malloc(sizeof(queue));
}

// A utility function to print the adjacency list representation of graph
void printGraph(graph* graph)
{
    int v;
    for (v = 0; v < graph->size; v++)
    {
        listNode* pCrawl = graph->lists[v].head;
        printf("\n Adjacency list of vertex %d\n head ", v+1);
        while (pCrawl)
        {
            printf("-> %d", pCrawl->dst);
            pCrawl = pCrawl->next;
        }
        printf("\n");
    }
}