#include <stdio.h> 
#include <stdbool.h> 
#include <string.h> 
#include <stdlib.h> 

#include "chemExt.h"
#include "stack.h"

/**
 * @brief Expands a chemical formula by handling parentheses and multipliers.
 * 
 * This function takes a chemical formula string, processes it to apply multipliers and handle 
 * nested parentheses, and produces an expanded form of the formula in the provided extchem variable.
 * 
 * @param chem The original chemical formula as a string (input).
 * @param extchem A buffer where the expanded chemical formula is stored (output).
 * @return int Returns EXIT_SUCCESS if the formula is expanded correctly, or EXIT_FAILURE if parentheses are unbalanced.
 */
int extenedChem(const char * const chem, char *extchem) {
    int length = strlen(chem); // Get the length of the input formula
   
    // If the formula is a single element, copy it directly to the output buffer
    if (length == 1) {
        strcpy(extchem, chem);
        return EXIT_SUCCESS; // Return success
    }

    bool onlyLetters = true; // Flag to check if formula contains only letters

    // Loop to check if formula contains numbers or parentheses
    for (int i = 0; i < length; i++) {
        if (((chem[i] > '0') && (chem[i] < '9')) || (chem[i] == '(') || (chem[i] == ')')) {
            onlyLetters = false; // Set flag to false if numbers or parentheses are found
        }
    }

    // If formula has only letters, copy it with spaces between elements
    if (onlyLetters) {
        strncat(extchem, &chem[0], 1);  // Add the first element to the output buffer
        for (int i = 1; i < length; i++) {
            if (chem[i] >= 'A' && chem[i] <= 'Z') { // Check if character is uppercase
                strcat(extchem, " "); // Add space before new element
            }
            strncat(extchem, &chem[i], 1); // Add character to output
        }
        return EXIT_SUCCESS; // Return success
    }

    STACK *stack = initStack(); // Initialize stack for parentheses
    STACK *stackParenthJ = initStack(); // Initialize stack to track group start indices
    int j = 0; // Index for the output buffer
    int parenthj = 0; // Starting index of a group in the expanded formula
    int parlength = 0; // Length of the content within parentheses
    int chemlength = 0; // Length of the current element

    // Loop through each character in the formula
    for (int i = 0; i < length; i++) {
        char c = chem[i]; // Get the current character

        // Reset chemlength if outside parentheses
        if (isEmpty(stack)) {
            chemlength = 0;
        }

        // If character is uppercase, it’s the start of a new element
        if (c >= 'A' && c <= 'Z') {
            extchem[j++] = c; // Add uppercase letter to output
            chemlength = 1; // Reset chemlength for new element

            // Add space if next character is also uppercase (start of a new element)
            if (chem[i + 1] >= 'A' && chem[i + 1] <= 'Z') 
                extchem[j++] = ' ';

            // Check if lowercase letters follow, indicating a complete element symbol
            else if (i + 1 < length && chem[i + 1] >= 'a' && chem[i + 1] <= 'z') {
                while (i + 1 < length && chem[i + 1] >= 'a' && chem[i + 1] <= 'z') {
                    i++; // Move to next character in the symbol
                    extchem[j++] = chem[i]; // Add to output
                    chemlength++; // Increase element length
                }
                extchem[j++] = ' '; // Add space after complete element symbol
            }
        }

        // If character is an opening parenthesis
        if (c == '(') {
            pushCHAR(c, stack); // Push '(' onto stack to track it
            pushINT(j, stackParenthJ); // Push the starting index of the group onto index stack
            parlength = 0; // Reset group length for a new group
        } 
        
        // If character is a closing parenthesis
        else if (c == ')') {
            if (isEmpty(stack)) {
                return EXIT_FAILURE; // If no matching '(', return failure
            }

            popCHAR(stack, &c); // Pop matching '('
            popINT(stackParenthJ, &parenthj); // Pop group start index
            parlength = j - parenthj; // Calculate length of content inside parentheses
       
            // Check if there’s a multiplier after the ')'
            if (i + 1 < length && chem[i + 1] >= '1' && chem[i + 1] <= '9') {
                i++; // Move to multiplier
                int count = chem[i] - '0'; // Convert char to int

                // Check for two-digit multiplier
                if (i + 1 < length && chem[i + 1] >= '0' && chem[i + 1] <= '9') {
                    count = count * 10 + (chem[++i] - '0'); // Form two-digit multiplier
                }
             
                // Repeat the content in parentheses `count` times
                for (int k = 1; k < count; k++) {
                    extchem[j++] = ' '; // Add space
                    for (int m = 0; m < parlength; m++) {
                        
                        extchem[j++] = extchem[parenthj + m]; // Copy group content
                    }
                }
            }
        }

        // Handle multipliers directly following an element
        if (i + 1 < length && chem[i + 1] >= '1' && chem[i + 1] <= '9') {
            int count = chem[++i] - '0'; // Convert multiplier to int

            // Check for two-digit multiplier
            if (i + 1 < length && chem[i + 1] >= '0' && chem[i + 1] <= '9') {
                count = count * 10 + (chem[++i] - '0'); // Form two-digit multiplier
            }
int repC;
        if(chemlength>1)
             repC = j - chemlength -1;
                 else
                     repC = j - chemlength ;
             // Position of the element start

            extchem[j++] = ' '; // Add space
            for (int k = 1; k < count; k++) {
                for (int m = 0; m < chemlength; m++) {
                    extchem[j++] = extchem[repC + m]; // Repeat the element
                }
                extchem[j++] = ' '; // Add space after repeated element
            }
        }

        chemlength = 0; // Reset chemlength for the next element
    }

    // If stack is not empty, there are unmatched parentheses
    if (!isEmpty(stack)) {
        return EXIT_FAILURE; // Return failure if unbalanced
    }

    extchem[j] = '\0'; // Null-terminate the expanded formula
    return EXIT_SUCCESS; // Return success
}

#ifdef DEBUG2
/**
 * @brief Main function to process chemical formulas from a file for testing.
 * 
 * This function reads chemical formulas from an input file, expands each formula, and writes the 
 * results to an output file.
 * 
 * @param argc The argument count.
 * @param argv The argument vector, containing program name, input file, and output file.
 * @return int Returns 0 on successful execution, or -1 on error.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return -1;
    }

    FILE *in, *out;
    in = fopen(argv[1], "r"); // Open input file for reading
    if (in == NULL) {
        perror("Unable to open input file\n"); // Print error if file fails to open
        exit(-1); // Exit with error code
    }

    out = fopen(argv[2], "w"); // Open output file for writing
    if (out == NULL) {
        perror("Unable to open output file\n"); // Print error if file fails to open
        exit(-1); // Exit with error code
    }

    char chem[50]; // Buffer for each chemical formula read from input file
    int flag, line = 1; // Track line number and function result
    bool AllGood = true; // Flag to check if all formulas are processed correctly

    // Process each formula in the input file
    while (fscanf(in, "%s", chem) != EOF) {
        char ext[50] = "";  // Buffer for expanded formula
        flag = extenedChem(chem, ext);  // Expand formula

        // Check for errors or write expanded formula to output
        if (flag == EXIT_FAILURE) {
            printf("Parentheses are NOT balanced in line: %d\n", line);
            AllGood = false; // Mark as unbalanced
            fprintf(out, "Parentheses are NOT balanced: %s\n", chem);
        } else {
            fprintf(out, "%s\n", ext); // Write expanded formula to output
        }

        line++; // Increment line number
    }

    // Report overall success if all formulas are balanced
    if (AllGood) {
        printf("Parentheses are balanced for all chemical formulas.\n");
    }

    fclose(in); // Close input file
    fclose(out); // Close output file
    return 0; // Return success
}
#endif
