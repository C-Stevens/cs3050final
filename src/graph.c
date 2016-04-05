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
    
    int i;
    for(i=0; i<size; i++) { // Create `size` number of empty adjacency lists at this graph struct's list array
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
    visitedNode* tmp = q->tail;
    if(tmp == NULL) {
        return NULL;
    }
    if(q->head == q->tail) { // Queue size of 1
        q->head = NULL;
        q->tail = NULL;
        return tmp;
    }
    // Queue > 1
    q->tail = tmp->prev;
    tmp->prev = tmp->next = NULL; // Sanitize
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

void printDistancesFromOrigin(graph* graph) {
    // Initialize what we'll need
    queue* q = malloc(sizeof(queue));
    int* visits = malloc(sizeof(int) * graph->size);
    int* results = malloc(sizeof(int) * graph->size);
    int i;
    for(i=0; i<(graph->size); i++) { // Start each distance off as -1 (unreachable) and all as unvisited
        results[i] = -1;
        visits[i] = FALSE;
    }

    // Start the queue with node 1
    visitedNode* startNode = malloc(sizeof(visitedNode));
    startNode->nodeVal = 1; // We always start at node 1 (see project docs)
    startNode->nodeDist = 0;
    visits[0] = TRUE; // Node 1 marked as visited (since we start there)
    results[0] = 0; // Node 1 is 0 hops away from itself
    enqueue(q, startNode);

    while(queueIsEmpty(q) != TRUE) { // Run until the queue empties (BST)
        visitedNode* currentStruct = dequeue(q); // Pop off a node
        int currentVal = currentStruct->nodeVal;
        int currentDist = currentStruct->nodeDist;
        results[currentVal - 1] = currentDist; // Record its distance from node 1

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
        free(currentStruct); // This will free the queue members as they are popped off
    }
    
    // Print results
    for(i=0; i<(graph->size); i++) {
        printf("%d %d\n", (i+1), results[i]); // (i+1) is to convert from index vertices to graph numberings
    }
    
    // Cleanup
    free(startNode);
    free(visits);
    free(results);
    free(q);
}
