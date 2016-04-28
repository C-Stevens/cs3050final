#include "../include/file_io.h"
#include "../include/input_error.h"

void parseInputFile(char* filename) {
    FILE* input = fopen(filename, "r");
    if(input == NULL) {
        printf("Error: File could not be opened.\n");
        exit(FILE_FAILED_TO_OPEN);
    }
    
    while(!feof(input)) {
        int val;
        int matches = fscanf(input, "%d", &val);
        if(matches == 0) { // fscanf could not match (bad input)
            printf("Error: Invalid input data detected.\n");
            exit(PARSING_ERROR_INVALID_CHARACTER_ENCOUNTERED);
        }
        if(matches == EOF) { // File is done
            break;
        }
        printf("VAL: %d\n", val); //DEBUG
    }
    
    if(fclose(input) == EOF) {
        printf("Error: Failed to close file.\n");
        exit(FILE_FAILED_TO_CLOSE);
    }
}