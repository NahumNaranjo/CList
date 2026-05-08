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
- **createList**: Asks for a default size and returns an empty list, use NULL instead of a number and it'll return a CLIST_NULL value.
- **len**: returns *list->size.
- **findFirst and findAll**: will respectively return a long with the index of the first appearance of a certain element or an array of all indexes of it no matter the datatype for as long as it isn't a struct.

### Ariadne borrowings
This functions were added in version 1.1.0 to have a better string management without the need to install ariadne, you can find these functions alone in [this link](https://github.com/NahumNaranjo/Ariadne) or install it via CLearning CLI with `cl install ariadne`
- **vote**: This function calls every string checker and returns an int with the result.
- **SimpleHeuristic**: Returns 1 if the string ***looks*** like a string and 0 if it doesn't.
- **EntropyAnalysis**: Returns the entropy value of the variable. Normal entropy for a string is 3.0 to 6.0.
- **SafeString**: Tries to break a non string variable, if it survives, then it returns 1. Be careful with this one, it purposefully tries to crash the program so it might generate some problems with mallocs.
- **getXChars**: Has 2 modes, `f` takes `x` chars from the beginning to the end of the string, `l` does the same but from the end to the beginning.

## Constants
- **CLIST_NULL**: Added for better error handling and its declared as `#define CLIST_NULL (List){0}`

**Author - Nahum Naranjo**  
**Version - 1.1.1**