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

void enqueue(queue* q, visitedNode* input) {
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

visitedNode* dequeue(queue* q) {
    visitedNode* output = q->tail;
    if(output == NULL) {
        return output; // Return NULL
    }
    q->tail = output->prev;
    q->tail->next = NULL;
    output->prev = NULL; // Prevent leakage of the rest of the list
    return output;
}

int queueIsEmpty(queue* q) {
    if (q->head == NULL) {
        return 1; // True (empty)
    }
    return 0; // False (non-empty)
}

adjList* getAdjListForVal(graph* graph, int val) {
    int i;
    for(i=0; i<(graph->size); i++) {
        adjList* currentList = graph->lists[i];
        if(currentList->head->dst == val) {
            return adjList;
        }
    }
}

void printDistancesFromOrigin(graph* graph) {
    queue* q = malloc(sizeof(queue));
    int* visits = malloc(sizeof(int) * graph->size);
    int* results = malloc(sizeof(int) * graph->size);
    int i;
    for(i=0; i<(graph->size); i++) { // Start each distance off as -1 (unreachable) and all as unvisited
        results[i] = -1;
        visits[i] = FALSE;
    }
    
    while(queueIsEmpty(q) != 1) {
        visitedNode* currentStruct = dequeue(q);
        int currentVal = currentStruct->nodeVal;
        int currentDist = currentStruct->nodeDist;
        results[currentVal - 1] = currentDist;
        
        
    }
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