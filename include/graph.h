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

listNode* makeNode(int); // Creates a new listNode with dst value `dst` and returns a listNode struct
graph* createGraph(int size); // Creates a new undirected graph, with `size` linked lists
void createEdge(graph* graph, int src, int dst); // Adds an edge to a graph struct

//DEBUG
void printGraph(graph* graph);

#endif