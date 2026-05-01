# CList - Another CLearning side quest
CList is a library designed to be like python's list and is part of the [CLearning](https://github.com/Nahumnaranjo/CLearning) ecosystem.

## Functions
- **MoveList**: Asks for three arguments, list (which the list you wanna modify), index which is when will the cycle stop (put 0 if you dont want it to stop) and orientation (only accepts 'r' and 'l') which will determine if it'll start from the right or the left
- **capCheck**: Reallocs enough memory for your list.
- **pop**: deletes the last item in your list.
- **cherryPick**: Will delete any item inside the index and then reaccomodate the list.
- **append**: add another item to the end of a list.
- **insert**: creates space to add an item into a specific index.
- **add**: will add an item to the beginning of the list.
- **createList**: Asks for a default size and returns an empty list, use NULL instead of a number and it'll return a CLIST_NULL value
- **len**: returns *list->size

## Constants
- **CLIST_NULL**: Added for better error handling and its declared as `#define CLIST_NULL (List){0}`

**Author - Nahum Naranjo**  
**Version - 1.0.3a**