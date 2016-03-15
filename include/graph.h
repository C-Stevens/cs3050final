#ifndef H_GRAPH_H
#define H_GRAPH_H

#include <stdio.h>
#include <stdlib.h>

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

typedef struct vistedNode {
    int nodeVal;
    int dist;
} visitedNode;

typedef struct queue {
    visitedNode* head;
    visitedNode* tail;
} queue;

listNode* makeNode(int); // Creates a new listNode with dst value `dst` and returns a listNode struct
graph* createGraph(int size); // Creates a new undirected graph, with `size` linked lists
void createEdge(graph* graph, int src, int dst); // Adds an edge to a graph struct
void printDistancesFromOrigin(graph* graph); // Returns shortest distance from `dst` to vertex 1
void createQueue;
void enqueue(queue, visitedNode*);
visitedNode* dequeue(queue);

//DEBUG
void printGraph(graph* graph);

#endif