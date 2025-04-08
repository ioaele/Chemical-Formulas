#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

/**
 * @brief Pushes a character onto the stack.
 * 
 * This function creates a new node for the stack and pushes a character onto the top.
 * 
 * @param value The character to be pushed onto the stack.
 * @param s Pointer to the stack.
 * @return EXIT_SUCCESS if the push operation was successful, EXIT_FAILURE otherwise.
 */
int pushCHAR(char value, STACK *s) {
    NODE *p = NULL; // Pointer for the new node
    if (s == NULL) { 
        return EXIT_FAILURE; // Check if stack is NULL
    }
    
    // Allocate memory for a new node
    p = (NODE *)malloc(sizeof(NODE));
    if (p == NULL) {
        printf("System out of memory!\n");
        return EXIT_FAILURE; // Check for memory allocation failure
    }

    p->data = value; // Assign the value to the new node
    p->next = s->top; // Adjust the next pointer to the current top
    s->top = p; // Update the top pointer to the new node
    (s->size)++; // Increment the stack size
    return EXIT_SUCCESS; // Return success
}

/**
 * @brief Pushes an integer onto the stack.
 * 
 * This function creates a new node for the stack and pushes an integer onto the top.
 * 
 * @param value The integer to be pushed onto the stack.
 * @param s Pointer to the stack.
 * @return EXIT_SUCCESS if the push operation was successful, EXIT_FAILURE otherwise.
 */
int pushINT(int value, STACK *s) {
    NODE *p = NULL; // Pointer for the new node
    if (s == NULL) { 
        return EXIT_FAILURE; // Check if stack is NULL
    }

    // Allocate memory for a new node
    p = (NODE *)malloc(sizeof(NODE));
    if (p == NULL) {
        printf("System out of memory!\n");
        return EXIT_FAILURE; // Check for memory allocation failure
    }

    p->data = value; // Assign the value to the new node
    p->next = s->top; // Adjust the next pointer to the current top
    s->top = p; // Update the top pointer to the new node
    (s->size)++; // Increment the stack size
    return EXIT_SUCCESS; // Return success
}

/**
 * @brief Gets the top node of the stack.
 * 
 * This function retrieves the top node of the stack without removing it.
 * 
 * @param s Pointer to the stack.
 * @return Pointer to the top node of the stack.
 */
NODE *top(STACK *s) { 
    return s->top; // Return the top node
}

/**
 * @brief Checks if the stack is empty.
 * 
 * This function checks whether the stack is empty.
 * 
 * @param s Pointer to the stack.
 * @return true if the stack is empty, false otherwise.
 */
bool isEmpty(STACK *s) {
    return ((s->top) == NULL || s->size == 0); // Return true if top is NULL or size is zero
}

/**
 * @brief Pops a character from the stack.
 * 
 * This function removes the top character from the stack and returns it.
 * 
 * @param s Pointer to the stack.
 * @param retval Pointer to where the popped character will be stored.
 * @return EXIT_SUCCESS if the pop operation was successful, EXIT_FAILURE otherwise.
 */
int popCHAR(STACK *s, char *retval) {
    NODE *p = NULL; // Pointer for the node to be popped
    if (s == NULL || s->size == 0) {
        printf("Sorry, stack is empty…\n");
        return EXIT_FAILURE; // Check if stack is NULL or empty
    }
    if (retval == NULL) {
        printf("Retval is null");
        return EXIT_FAILURE; // Check if retval is NULL
    }
    *retval = (s->top)->data; // Get the top value
    p = s->top; // Remember the top node for freeing
    s->top = p->next; // Update the top to the next node
    (s->size)--; // Decrement the stack size
    free(p); // Free the allocated memory
    return EXIT_SUCCESS; // Return success
}

/**
 * @brief Pops an integer from the stack.
 * 
 * This function removes the top integer from the stack and returns it.
 * 
 * @param s Pointer to the stack.
 * @param retval Pointer to where the popped integer will be stored.
 * @return EXIT_SUCCESS if the pop operation was successful, EXIT_FAILURE otherwise.
 */
int popINT(STACK *s, int *retval) {
    NODE *p = NULL; // Pointer for the node to be popped
    if (s == NULL || s->size == 0) {
        printf("Sorry, stack is empty…\n");
        return EXIT_FAILURE; // Check if stack is NULL or empty
    }
    if (retval == NULL) {
        printf("Retval is null");
        return EXIT_FAILURE; // Check if retval is NULL
    }
    *retval = (s->top)->data; // Get the top value
    p = s->top; // Remember the top node for freeing
    s->top = p->next; // Update the top to the next node
    (s->size)--; // Decrement the stack size
    free(p); // Free the allocated memory
    return EXIT_SUCCESS; // Return success
}

/**
 * @brief Initializes a new stack.
 * 
 * This function allocates memory for a new stack and initializes it.
 * 
 * @return Pointer to the newly created stack, or NULL if memory allocation fails.
 */
STACK *initStack() {
    STACK *stack = (STACK *)malloc(sizeof(STACK)); // Allocate memory for the stack
    if (stack == NULL) return NULL; // Check for memory allocation failure
    stack->top = NULL; // Initialize top to NULL
    stack->size = 0; // Initialize size to 0
    return stack; // Return the initialized stack
}
