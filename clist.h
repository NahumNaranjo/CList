#ifndef CLIST_H
#define CLIST_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <ctype.h>
    #include <setjmp.h>
    #include <signal.h>
    #include <math.h>
    static jmp_buf buf;

    #define CLIST_NULL (List){0}

    // Python is an engineering marvel
    typedef struct{
        void** content;
        size_t size;
        size_t allocated;
    } List;

    // Checks if the ist hasn't gone out of bounds
    static inline void capCheck(List* list){
        if(list->size >= list->allocated){
            size_t newSize = list->allocated + (list->allocated >> 2);
            list->content = (void**)realloc(list->content, newSize * sizeof(void*)); // Crazier realloc
            list->allocated = newSize;
        }
    }

    // Moves all the values of a list, index makes it stop at a specific point and orientation ('l' or 'r') marks where it'll begin
    static inline void moveList(List* list, size_t* index, char* orientation){
        capCheck(list);

        if(orientation[0] != 'l' && orientation[0] != 'r'){
            return;
        }

        for(
            int i = (orientation[0] == 'l' ? 0 : list->size);   // if it goes to the right, i = list->size
            orientation[0] == 'l' ? i <= list->size : i >= 0;   
            orientation[0] == 'l' ? i++ : i-- // if it goes to the right, i--
        ){
            if(i < *index && *index != 0){
                break;
            }
            if(orientation[0] == 'r'){
                list->content[i] = list->content[i-1];
            } else{
                list->content[i] = list->content[i+1];
            }
        }
    }

    // Deletes the last item
    static inline void pop(List* list){
        list->content[list->size] = NULL;
        list->size--;
    }

    // Deletes a specific index and reorganizes the list
    static inline void cherryPick(List* list, size_t index){
        list->content[index] = NULL;
        
    }


    // Adds an item to the last position of the list
    static inline void append(List* list, void* obj){
        capCheck(list);
        if(list->size != 0) list->size++;

        list->content[list->size] = obj;

        if(list->size == 0) list->size++;
    }

    // Inserts an item to a specific index
    static inline void insert(List* list, void* obj, size_t index){
        capCheck(list);

        // Move all objects to the right and insert the recieving one
        for(int i = list->size; i > 0; i--){
            if(i < index){
                break;
            }
            list->content[i] = list->content[i-1];
        }
        list->content[index] = obj;
        list->size++;
    }

    // Adds an item to the first position of the list
    static inline void add(List* list, void* obj){
        capCheck(list);

        // switch all to the right and add obj to the start
        // Impossible to do O(1) but meh
        for (int i = list->size; i > 0; i--) {
            list->content[i] = list->content[i-1];
        }
        list->content[0] = obj;
        list->size++;
    }

    //TODO: ERROR MANAGER

    // creates an empty list
    static inline List createList(size_t size){
        List list;
        if(size == NULL){
            list.allocated = NULL;
            list.size = NULL;
            list.content = NULL;
            return list;
        }
        // Python style overallocation
        size_t capacity;
        if (size < 8) {
            capacity = size + 3;  // Small lists get more relative room
        } else {
            // ~22.5% overallocation: size + size/4 + small constant
            capacity = size + (size >> 2) + 6;
        }
        list.content = (void**)malloc(capacity * sizeof(void*)); // Crazy allocation
        if(!list.content) {
            list.size = 0;
            list.allocated = 0;
            return list;
        }

        // Initialize all to NULL
        memset(list.content, 0, capacity * sizeof(void*));
        list.size = 0;
        list.allocated = capacity;
        return list;
    }

    static inline void destroyList(List *list) {
        if (list->content) {
            free(list->content);
            list->content = NULL;
            list->size = 0;
            list->allocated = 0;
        }
    }

    // Returns the length of the list
    static inline size_t len(List* list){
        return list->size;
    }

    //* ↓↓↓ Ariadne borrowings ↓↓↓

    // returns x quantity of characters of a string, f returns the first x and l returns the last x
    static inline char getXChars(char* string, int chars, char mode){
        if(chars <= 0 || !chars){
            perror("Can't get less than 1 character");
            return NULL;
        }
        if(!string){
            perror("No string to read");
            return NULL;
        }
        if((mode != 'l' && mode != 'f') || !mode){
            perror("Unsopported mode");
            return NULL;
        }
        char *returning = (char*)malloc(sizeof(char)*chars);
        if(mode == 'f'){
            for(int i = 0; i < chars; i++){
                returning[i] = string[i];
            }
        } else if(mode == 'l'){
            for(int i = chars; i > 0; i--){
                returning[-(i - chars)] = string[-(i - chars)];
            }
        }
        return *returning;
    }

    // First string check, borrowed from Ariadne
    static inline short SimpleHeuristic(char* string){
        short nullFound = 0;
        // Checks for \0
        for(int i = 0; i < 256; i++){
            // checks for valid string chars
            if(
                isprint((unsigned char)string[i]) || 
                isspace((unsigned char)string[i]) ||
                string[i] == '\n' || string[i] == '\t' ||
                string[i] == '\\' || string[i] == '\"' ||
                string[i] == '\'' || string[i] == '\b' ||
                string[i] == '\a' || string[i] == '\r' ||
                string[i] == '\v' || string[i] == '\f'
            ){
                continue;
            }

            // checks for null terminator
            if(string[i] == '\0' && i > 0){
                return 1;
            }
            if(string[i] == '\0' && i == 0){
                return 0;
            }
        }
        return 0;
    }

    // return's a string's randomness
    float EntropyAnalysis(char* value) {
        if (!value || !SimpleHeuristic(value)) return 8.0; // High entropy if not string
    
        int counts[256] = {0};
        int len = 0;
    
        // scan up to 256 chars or until null
        for (int i = 0; i < 256 && value[i] != '\0'; i++) {
            counts[(unsigned char)value[i]]++;
            len++;
        }
    
        if (len == 0) return 8.0;
    
        float entropy = 0;
        for (int i = 0; i < 256; i++) {
            if (counts[i] > 0) {
                float p = (float)counts[i] / len;
                entropy -= p * log2f(p);
            }
        }
        return entropy;
    }

    // Does string-only operations and returns 1 if it all went alright
    static inline short SafeString(char* string){
        if(!string) return 0;
        if(setjmp(buf) == 0){
            signal(SIGSEGV, handleCrash); 
            volatile size_t len = 0;
            char* p = string;
            for(int i = 0; i < 512; i++) {
                if (p[i] == '\0') {
                    signal(SIGSEGV, SIG_DFL);
                    return 1;
                }
            }
            signal(SIGSEGV, SIG_DFL);
            return 0;
        } else {
            signal(SIGSEGV, SIG_DFL);
            return 0;
        }
        
    }

    static inline void handleCrash(int sig){
        longjmp(buf, 1);
    }

    static inline int vote(void* value){
        signal(SIGSEGV, handleCrash);
        // String guessing
        int votingResults = 0;
        char* string = (char*)value;

        votingResults += SafeString(string);
        votingResults += SimpleHeuristic(string);
        float entropy = EntropyAnalysis(string);
        if(entropy > 3.0 && entropy < 6.0){
            votingResults += 1;
        }
        return votingResults;
    }
    
    //* ↑↑↑ Ariadne borrowings ↑↑↑

    // Obiviously, couldn't make them O(1) D:

    // returns the index of the first appearance of an element
    // WARNING: Use only for string or numbers, structs are not supported
    static inline long findFirst(List* list, void* value){
        int votingResults = vote(value);
        for (int i = 0; i < list->size; i++){
            if(votingResults > 2){
                if((char*)strcmp(list->content[i], (char*)value)){
                    return i;
                } 
            } else {
                if(*(size_t *)list->content[i] == *(size_t *)value) return i;
            }
        }
        return -1;
    }
    //TODO: Add an universal resizer

    // returns the indexes of all appearances of a certain element
    static inline long* findAll(List* list, void* value){
        int votingResults = vote(value);
        long results[] = malloc(sizeof(long) * 1024);
        long count = 0;
        for (int i = 0; i > list->size; i++){
            if(votingResults > 2){
                if(strcmp((char*)list->content, (char*)value)){
                    results[count] = i;
                    count++;
                }
            } else {
                if(*(size_t*)list->content == *(size_t*)value){
                    results[count] = i;
                    count++;
                } 
            }
        }
        return results; 
    }

#endif