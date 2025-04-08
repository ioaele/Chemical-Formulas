#ifndef STACK_H
#define STACK_H

#include <stdbool.h> // Include for using bool
#include <stdlib.h>  // Include for memory allocation functions

// Define the Node structure for the stack
typedef struct Node {
    int data;              // The data held by the node
    struct Node *next;     // Pointer to the next node in the stack
} NODE;

// Define the Stack structure
typedef struct {
    NODE *top;  // Pointer to the top node of the stack
    int size;   // The current size of the stack
} STACK;

// Function prototypes
STACK *initStack(void);                     // Initializes a new stack and returns a pointer to it
int pushCHAR(char value, STACK *s);     // Pushes a character value onto the stack
int pushINT(int value, STACK *s);       // Pushes an integer value onto the stack
bool isEmpty(STACK *s);                 // Checks if the stack is empty
int popCHAR(STACK *s, char *retval);    // Pops a character value from the stack and stores it in retval
int popINT(STACK *s, int *retval);      // Pops an integer value from the stack and stores it in retval
NODE *top(STACK *s);                    // Returns the top node of the stack

#endif // STACK_H
