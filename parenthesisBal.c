#include "stack.h"
#include "parenthesisBal.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include "chemExt.h"

/**
 * @brief Checks if the parentheses in a chemical formula are balanced.
 * 
 * This function processes a given chemical formula and uses a stack 
 * to determine whether the parentheses are balanced. 
 * It returns EXIT_SUCCESS if the parentheses are balanced, 
 * or EXIT_FAILURE if they are unbalanced.
 * 
 * @param chem A pointer to the chemical formula string to be checked.
 * @return int Returns EXIT_SUCCESS (0) if the parentheses are balanced, 
 *         or EXIT_FAILURE (1) if they are unbalanced.
 */
int parB(char *chem) {
    int length = strlen(chem);
    
    // Initialize stacks for tracking parentheses
    STACK *stack = initStack();
   
    // Process each character in the formula
    for (int i = 0; i < length; i++) {
        char c = chem[i];

        // Skip any character that is not a parenthesis
        if (!(c != '(' || c != ')'))
            continue;

        // Handle opening parentheses
        if (c == '(') {
            pushCHAR(c, stack); // Track '(' in stack
        } 
        
        // Handle closing parentheses
        else if (c == ')') {
            if (isEmpty(stack)) {
                return EXIT_FAILURE; // Unbalanced if ')' with no matching '('
            }

            popCHAR(stack, &c); // Pop matching '('
        }
    }

    // If stack is empty, parentheses are balanced
    if (isEmpty(stack)) 
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE; // Unmatched parentheses remain in stack
}

#ifdef DEBUG4
/**
 * @brief Main function to process chemical formulas from a file.
 * 
 * This function reads chemical formulas from the specified input file, 
 * checks each formula for balanced parentheses, and prints the results 
 * to the console.
 * 
 * Usage: program_name <input_file> <output_file>
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return -1;
    }

    FILE *in;
    in = fopen(argv[1], "r");
    if (in == NULL) {
        perror("Unable to open input file\n");
        exit(-1);
    }

    char *chem;
    chem=(char *)malloc (50*sizeof(char)); // Allocate memory for the chemical formula
    int flag, line = 1;
    bool AllGood = true;

    // Process each formula in the input file
    while (fscanf(in, "%s", chem) != EOF) {
        char ext[50] = "";  // Store expanded formula here
        flag = parB(chem);  // Check if the parentheses are balanced

        // Check for errors or write expanded formula to output
        if (flag == EXIT_FAILURE) {
            printf("Parentheses are NOT balanced in line: %d\n", line);
            AllGood = false;
        }

        line++;
    }

    if (AllGood) {
        printf("Parentheses are balanced for all chemical formulas.\n");
    }
    free(chem); // Free memory for the chemical formula
    fclose(in); // Close input file
    return 0;
}
#endif
