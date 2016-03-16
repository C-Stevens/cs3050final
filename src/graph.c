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
    printQueue(q);
    printf("Debug 1\n");
    visitedNode* tmp = q->tail;
    if(tmp == NULL) {
        printf("Debug 1.5, returning NULL\n");
        return NULL;
    } 
    printf("Debug 2\n");
    // Sanitize
    tmp->prev = NULL;
    tmp->next = NULL;
    printf("Debug 3\n");
    // Fix the queue tail
    q->tail = q->tail->prev;
    return tmp;
}

int queueIsEmpty(queue* q) {
    if (q->head == NULL) {
        return TRUE; // Empty
    }
    return FALSE; // Non-empty
}

void printQueue(queue* q) {
    visitedNode* cur = q->head;
    printf("Current queue: \n");
    while(cur != NULL) {
        printf("%d -> ", cur->nodeVal);
        cur = cur->next;
    }
    printf("NULL\n");
}

adjList* getAdjListForVal(graph* graph, int val) {
//     adjList* aL = graph->lists;
//     int i;
//     for(i=0; i<(graph->size); i++) {
//         adjList* currentList = aL[i]);
//         if(currentList->head->dst == val) {
//             return currentList;
//         }
//     }
    return NULL;
}

void printDistancesFromOrigin(graph* graph) {
    printf("\tInitializing\n"); //DEBUG
    // Initialize what we'll need
    queue* q = malloc(sizeof(queue));
    int* visits = malloc(sizeof(int) * graph->size);
    int* results = malloc(sizeof(int) * graph->size);
    int i;
    for(i=0; i<(graph->size); i++) { // Start each distance off as -1 (unreachable) and all as unvisited
        results[i] = -1;
        visits[i] = FALSE;
    }
    printf("\tDone\n"); //DEBUG

    printf("\tStarting with node 1 and enqueuing\n"); //DEBUG
    // Start the queue with node 1
    visitedNode* startNode = malloc(sizeof(visitedNode));
    startNode->nodeVal = 1; // We always start at node 1 (see project docs)
    startNode->nodeDist = 0;
    visits[0] = TRUE; // Node 1 marked as visited (since we start there)
    results[0] = 0; // Node 1 is 0 hops away from itself
    enqueue(q, startNode);
    printf("\tDone\n"); //DEBUG

    while(queueIsEmpty(q) != 1) { // Run until the queue empties
        printf("\tIn while: getting a node\n"); //DEBUG
        visitedNode* currentStruct = dequeue(q); // Pop off a node
        int currentVal = currentStruct->nodeVal;
        int currentDist = currentStruct->nodeDist;
        printf("\tDone\n"); //DEBUG
        printf("\tIn while: recording distance\n"); //DEBUG
        results[currentVal - 1] = currentDist; // Record its distance from node 1
        printf("\tDone\n"); //DEBUG

//        adjList* lists = graph->lists;
//        adjList* neighbors = *(lists + currentVal);
//        listNode* iterNode = neighbors->head;
       listNode* iterNode = graph->lists[currentVal - 1].head;
        while(iterNode != NULL) { // Iterate over the node's adjacency list
            if (visits[iterNode->dst - 1] == FALSE) { // If we haven't visited this node yet, push it on the stack
                visitedNode* newQueueItem = malloc(sizeof(visitedNode));
                newQueueItem->nodeVal = iterNode->dst;
                newQueueItem->nodeDist = currentDist + 1;
                enqueue(q, newQueueItem);
                visits[iterNode->dst -1] = TRUE; // Mark this node as visited so we don't re-process it
            }
            iterNode = iterNode->next; // Move to the next neighbor
        }
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