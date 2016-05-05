#include "../include/file_io.h"
#include "../include/input_error.h"

void freeTmp(tmp* t) {
    /* Frees the temporary holding list
     */
    tmpNode* cur = t->head;
    tmpNode* next = NULL;
    while(cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(t);
}

int* getStaticArray(tmp* t) {
    /* Converts the dynamically sized linked list at t to a static array of integers.
     */
    int* array = malloc(sizeof(int) * t->size);
    int i = 0;
    tmpNode* cur = t->head;
    while(cur != NULL) {
        array[i] = cur->val;
        i++;
        cur = cur->next;
    }
    return array;
}

void printTmpList(tmp* t) {
    /* Prints out the size of the tmpList t, as well as a visual depiction of the linked
     * list stored at t. Useful for debug purposes.
     */
    printf("Size of the list: %d\n", t->size);
    tmpNode* cur = t->head;
    while(cur != NULL) {
        printf("%d -> ", cur->val);
        cur = cur->next;
    }
    printf("NULL\n");
}

void addToTmpList(tmp* t, tmpNode* n) {
    /* Creates a new linked list at t if none exists, otherwise adds n to the linked list
     * and updates the tail pointer stored in t.
     */
    if(t->size == 0) { // No list yet
        t->head = t->tail = n;
    } else { // Add to the end of the list
        t->tail->next = n;
        t->tail = n;
    }
    t->size++;
}

prices* parseInputFile(char* filename) {
    /* Reads a formatted input file, creates a dynamically sized linked list of inputs until
     * the file reaches EOF, then converts and returns a static array of inputs.
     */
    FILE* input = fopen(filename, "r");
    if(input == NULL) {
        printf("Error: File could not be opened.\n");
        exit(FILE_FAILED_TO_OPEN);
    }
    
    tmp* inputVals = malloc(sizeof(tmp));
    inputVals->size = 0;
    
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
        tmpNode* n = malloc(sizeof(tmpNode));
        n->val = val;
        n->next = NULL;
        addToTmpList(inputVals, n);
    }
       
    if(fclose(input) == EOF) {
        printf("Error: Failed to close file.\n");
        exit(FILE_FAILED_TO_CLOSE);
    }
    
    int* priceArray = getStaticArray(inputVals);
    prices* p = malloc(sizeof(prices));
    p->size = inputVals->size;
    p->priceArray = priceArray;
    freeTmp(inputVals);
    
    return p;
}