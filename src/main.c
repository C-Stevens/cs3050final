#include "../include/input_error.h"
#include "../include/graph.h"

int main(int argc, char** argv) {
    if(argc != 2) { // Read in one argument
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    FILE* input = fopen(argv[1], "r");
    if(input == NULL) {
        exit(FILE_FAILED_TO_OPEN);
    }
    
    int test = 5; //DEBUG
    printf("hi im just starting\n"); //DEBUG
    graph* g = createGraph(test); //DEBUG
    printf("made graph\n"); //DEBUG
    createEdge(g, 2, 3);
    createEdge(g, 1, 4);
    createEdge(g, 1, 3);
    createEdge(g, 3, 4);
    createEdge(g, 4, 5);
    printf("done making edges\n"); //DEBUG
    printGraph(g); //DEBUG
    
    if(fclose(input) == EOF) {
        exit(FILE_FAILED_TO_CLOSE);
    }
    exit(EXIT_SUCCESS);
}
