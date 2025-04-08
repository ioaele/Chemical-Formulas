#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdbool.h> 
#include "periodicTable.h"
#include "chemExt.h"
#include "parenthesisBal.h"
#include "protonNum.h"
#include "stack.h"
#define SIZE 50
/**
 * @brief Main function to process chemical formulas.
 * 
 * This program processes chemical formulas based on command-line options:
 * - `-v`: Verify if parentheses are balanced.
 * - `-ext`: Compute the extended version of the formulas and write to an output file.
 * - `-pn`: Compute the total proton number (atomic number) of formulas based on a periodic table.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return int Returns 0 on success, -1 on failure.
 */
int main(int argc, char *argv[]) {
    // Check if sufficient command-line arguments are provided
    if (argc < 4) {
        printf("Usage: %s -v <input_file> OR Usage: %s -ext <input_file> <output_file> OR "
               "Usage: %s -pn <input_file> <output_file> \n", argv[0], argv[0], argv[0]);
        return -1;
    }

    char *opt;
    opt = argv[2]; // Get the command option from the arguments

    // Check if the option is to verify balanced parentheses
    if (strcmp(opt, "-v") == 0) {
        FILE *in;
        in = fopen(argv[3], "r"); // Open the input file for reading
        if (in == NULL) {
            perror("Unable to open input file\n");
            exit(-1); // Exit if the file cannot be opened
        }

        
        char *chem;
            chem=(char *)malloc (SIZE*sizeof(char)); // Allocate memory for the chemical formula
    if (chem == NULL) {
        perror("Memory allocation failed");
        fclose(in);
        exit(-1);
    }
        int flag, line = 1;
        bool AllGood = true; // Flag to check if all formulas are balanced
        int size=SIZE;
        printf("Verify balanced parentheses in %s \n", argv[3]);
        // Process each formula in the input file
        while (fscanf(in, "%s", chem) != EOF) {
        // Check if `chem` needs more space to hold the formula
        if (sizeof(chem) >= size) {  // check if we need more memory space
            size *= 2;  // Increase size 
            char *temp = realloc(chem, size);
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(chem);
                fclose(in);
                return EXIT_FAILURE;
            }
            chem = temp;
        }
            flag = parB(chem); // Verify balanced parentheses in the formula

            // Check for errors and report unbalanced formulas
            if (flag == EXIT_FAILURE) {
                printf("Parentheses are NOT balanced in line: %d\n", line);
                AllGood = false; // Mark as unbalanced
            }
            line++; // Increment line number
        }
        
        // Final report of balance status
        if (AllGood) 
            printf("Parentheses are balanced for all chemical formulas.\n");
        
        free(chem); // Free memory for the chemical formula
        fclose(in); // Close the input file
    }
    // Check if the option is to compute the extended version of formulas
    else if (strcmp(opt, "-ext") == 0) {
        FILE *in, *out;
        in = fopen(argv[3], "r"); // Open the input file for reading
        if (in == NULL) {
            perror("Unable to open input file\n");
            exit(-1); // Exit if the file cannot be opened
        }

        out = fopen(argv[4], "w"); // Open the output file for writing
        if (out == NULL) {
            perror("Unable to open output file\n");
            fclose(in); // Close the input file if output file fails to open
            exit(-1);
        }
          char *chem,*ext; 
        chem=(char *)malloc (SIZE*sizeof(char)); // Allocate memory for the chemical formula
    if (chem == NULL) {
        perror("Memory allocation failed");
        fclose(in);
        fclose(out);
        exit(-1);
    }
        ext=(char *)malloc (SIZE*sizeof(char)); // Allocate memory for the extened chemical formula
          if (ext == NULL) {
        perror("Memory allocation failed");
        fclose(in);
        fclose(out);
        exit(-1);
    }
        int flag, line = 1;
        int size=SIZE;
        printf("Compute extended version of formulas in %s\n", argv[3]);
        // Process each formula in the input file
        while (fscanf(in, "%s", chem) != EOF) {
           if (sizeof(chem) >= size) {  // check if we need more memory space
            size *= 2;  // Increase size 
            char *temp = realloc(chem, size);
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(chem);
                fclose(in);
                 fclose(out);
                exit(-1);
            }
            chem = temp;
        }
           ext = "";  // expanded formula

            flag = extenedChem(chem, ext); // Expand the formula

            // Check for errors or write expanded formula to output
            if (flag == EXIT_FAILURE) {
                printf("Parentheses are NOT balanced in line: %d", line);
                printf(" -- Failed to compute extended version\n");
        
                fprintf(out, "Parentheses are NOT balanced: %s\n", chem);
            } else {
                fprintf(out, "%s\n", ext); // Write the expanded formula to the output file
            }
            line++; // Increment line number
        }
        printf("Writing formulas to %s\n", argv[4]);

        free(chem); // Free memory for the chemical formula
        fclose(in); // Close the input file
        fclose(out); // Close the output file
    }
    // Check if the option is to compute the total proton number(atomic number)
    else if (strcmp(opt, "-pn") == 0) {

    
        FILE *in, *out;
        in = fopen(argv[3], "r"); // Open the input file for reading
        if (in == NULL) {
            perror("Unable to open input file\n");
            exit(-1); // Exit if the file cannot be opened
        }

        out = fopen(argv[4], "w"); // Open the output file for writing
        if (out == NULL) {
            perror("Unable to open output file\n");
            fclose(in);
            exit(-1); // Exit if the output file cannot be opened
        } 
        
         PTABLE *pert = (PTABLE *) malloc(sizeof(PTABLE)); // Allocate memory for PTABLE
    if (pert == NULL) {
        perror("Memory allocation for periodic table failed.");
        fclose(in);
        fclose(out);
        exit(-1);
    }
        createTable(&pert, argv); // Create the periodic table from provided arguments

        int size=SIZE;
         char *chem,*ext; 
        chem=(char *)malloc (SIZE*sizeof(char)); // Allocate memory for the chemical formula
    if (chem == NULL) {
        perror("Memory allocation failed");
        fclose(in);
        fclose(out);
        exit(-1);
    }
        ext=(char *)malloc (SIZE*sizeof(char)); // Allocate memory for the extened chemical formula
          if (ext == NULL) {
        perror("Memory allocation failed");
        fclose(in);
        fclose(out);
        exit(-1);
    }
        int atnum; // Variable to store the atomic number
        printf("Compute total proton number (atomic number) of formulas in %s\n", argv[3]);

        // Process each formula in the input file
   while (fscanf(in, "%s", chem) != EOF) {
        if (sizeof(chem) >= size) {  // check if we need more memory space
            size *= 2;  // Increase size 
            char *temp = realloc(chem, size);
            if (temp == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(chem);
                fclose(in);
                 fclose(out);
                exit(-1);
            }
            chem = temp;
        }
    ext = "";  // expanded formula
    if (extenedChem(chem, ext) == EXIT_SUCCESS) {
        atnum = 0; // Reset total atomic number
        atomicNum(ext, &atnum, pert,out); // Calculate atomic number
        fprintf(out, "%d\n", atnum); // Write result to output file
    } else {
        fprintf(out, "Error processing formula: %s\n", chem);
    }

}
    
    printf("Writing formulas atomic numbers in %s \n", argv[4]);
       
         // Clean up resources
      // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(pert->ch[i]);
    }
    free(chem); // Free memory for the chemical formula
    free(ext); // Free memory for the extened chemical formula
    free(pert); // Free periodic table memory
    fclose(in);
    fclose(out);

     
    }   
    return 0;
}
