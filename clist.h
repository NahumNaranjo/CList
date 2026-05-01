#ifndef CLIST_H
#define CLIST_H
    #include <stdio.h>
    #include <stdlib.h>

    #define CLIST_NULL (List){0}

    // Python is an engineering marvel

    typedef struct{
        void** content;
        int size;
        int allocated;
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
            if(i < *index && (*index != NULL || *index != -1)){
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

    // Deletes a specific index and fixes it
    static inline void cherryPick(List* list, size_t index){
        list->content[index] = NULL;
        
    }


    // Adds an item to the last position of the list
    static inline void append(List* list, void* obj){
        capCheck(list);
        list->size++;
        list->content[list->size] = obj;
    }

    // Inserts an item to the a specific index
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

    // create an empty list (Only compatible with string, byte, double, int, char, long, float and short)
    static inline List createList(size_t size){
        List list;
        // NULL init
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
        // Initialize all to NULL
        for (size_t i = 0; i < capacity; i++) {
            list.content[i] = NULL;
        }
        if(!list.content) return;
        list.size = 0;
        list.allocated = capacity;
        return list;
    }

    // Returns the length of the list
    static inline int* len(List* list){
        return &list->size;
    }
#endif