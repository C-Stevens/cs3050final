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
    
    int i,inputSize,count,v1,v2;
    fscanf(input, "%d\n", &inputSize);
    graph* g = createGraph(inputSize);
    
    for(i=0; i<inputSize; i++) { // Load in vertices and edges
        count = fscanf(input, "(%d,%d)\n", &v1, &v2);
        if(count == EOF) {
            if(ferror(input)) {
                exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
            }
        } else if(count != 2) {
            if(count == 0) {
                exit(PARSING_ERROR_EMPTY_FILE);
            }
            exit(PARSING_ERROR_INVALID_FORMAT);
        }
        if(v1 < 1 || v1 > (g->size)) {
            exit(INTEGER_IS_NOT_A_VERTEX);
        }
        createEdge(g, v1, v2);
    }

    printDistancesFromOrigin(g);

    // Cleanup
    free(g->lists);
    free(g);
    if(fclose(input) == EOF) {
        exit(FILE_FAILED_TO_CLOSE);
    }
    exit(EXIT_SUCCESS);
}
