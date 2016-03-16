#ifndef H_GRAPH_H
#define H_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#define FALSE 0
#define TRUE 1

typedef struct listNode { // Individual nodes
    int dst;
    struct listNode* next;
} listNode;

typedef struct adjList { // Adjacency list per node
    listNode* head;
} adjList;

typedef struct graph { // Struct containing all adjacency lists as an array
    int size;
    adjList* lists;
} graph;

typedef struct vistedNode { // Used for BST and calculating distances
    int nodeVal;
    int nodeDist;
    struct visitedNode* prev;
    struct visitedNode* next;
} visitedNode;

typedef struct queue { // Holds visitedNodes during BST queueing
    visitedNode* head;
    visitedNode* tail;
} queue;

listNode* makeNode(int); // Creates a new listNode with dst value `dst` and returns a listNode struct
graph* createGraph(int size); // Creates a new undirected graph, with `size` linked lists
void createEdge(graph*, int, int); // Adds an edge to a graph struct
void printDistancesFromOrigin(graph*); // Prints shortest distances from vertex 1
void enqueue(queue*, visitedNode*); // Adds element of type struct vistedNode to the queue
int queueIsEmpty(queue*); // Returns TRUE if queue has 0 members, FALSE otherwise
void printQueue(queue*); // Prints out the queue at its current state, for debug
visitedNode* dequeue(queue*); // Returns a struct visitedNode element at the tail, returns it, and removes it from the queue

//DEBUG
void printGraph(graph* graph);

#endif