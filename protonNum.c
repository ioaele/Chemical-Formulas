#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "periodicTable.h"
#include "chemExt.h"
#include "protonNum.h"

/**
 * @brief Calculates the total atomic number for the given extended chemical formula.
 * 
 * This function parses the extended formula string to extract element symbols,
 * searches for them in the provided periodic table, and sums their atomic numbers.
 *
 * @param ext The extended formula as a string containing element symbols.
 * @param atnum Pointer to an integer where the total atomic number will be stored.
 * @param pert Pointer to a constant `PTABLE` structure containing periodic table data.
 * @param out Pointer to a file where error messages will be written.
 */
void atomicNum(char *ext, int *atnum, const PTABLE * const pert, FILE *out) {
    int k = 0; 
    int m = 0; 
   
    char *ch;
    ch=(char *)malloc(3*sizeof(char)); // Allocate memory for each the chemical type  
    for (int i = 0; i < strlen(ext); i++) {
        
        while (ext[i] == ' ') {
            i++; // Skip spaces
        }

        k = 0; // Reset symbol index

        // Extract the symbol
        while (ext[i] != ' ' && ext[i] != '\0') {
            if (k < 2) {  // Ensure we don't overflow `ch`
                ch[k++] = ext[i];
            }
            i++;
        }
        ch[k] = '\0';  // Null-terminate the symbol
  
        m = 0; // Reset periodic table index

        // Search for the symbol in the periodic table
        while (m < N && strcmp(pert->ch[m], ch) != 0) {
            m++;
        }

        // Add atomic number if the element was found
        if (m < N) {
            *atnum += pert->anum[m];
        } else {
            fprintf(out, "Element %s not found in periodic table.\n", ch);
        }
    }

    free(ch); //free memory for each chemical type
}

#ifdef DEBUG3
/**
 * @brief Main function for testing the atomic number calculation.
 * 
 * This function reads chemical formulas from an input file, expands them,
 * and calculates the total atomic number for each formula using the periodic table.
 *
 * @param argc Argument count.
 * @param argv Argument vector; should contain the periodic table file, input file, and output file.
 * @return Returns 0 on success, -1 on error.
 */
int main(int argc, char *argv[]) {
    
    if (argc < 4) {
        printf("Usage: %s <periodic_table_file> <input_file> <output_file>\n", argv[0]);
        return -1;
    }

    FILE *in, *out;
    in = fopen(argv[2], "r"); // Open input file
    if (in == NULL) {
        perror("Unable to open input file\n");
        exit(-1);
    }

    out = fopen(argv[3], "w"); // Open output file
    if (out == NULL) {
        perror("Unable to open output file\n");
        fclose(in);
        exit(-1);
    }

    PTABLE *pert = (PTABLE *) malloc(sizeof(PTABLE)); // Allocate memory for PTABLE
    if (pert == NULL) {
        perror("Memory allocation for periodic table failed.");
        fclose(in);
        fclose(out);
        exit(-1);
    }

    createTable(&pert, argv); // Load periodic table data
    
     char *chem,*ext; 
        chem=(char *)malloc (50*sizeof(char)); // Allocate memory for the chemical formula
        ext=(char *)malloc (50*sizeof(char)); // Allocate memory for the extened chemical formula
    int atnum;

    // Process each formula in the input file
    while (fscanf(in, "%s", chem) != EOF) {
        ext= "";  // Buffer for expanded formula
          
        if (extenedChem(chem, ext) == EXIT_SUCCESS) {
            // Expand formula successfully
            atnum = 0; // Reset total atomic number
            atomicNum(ext, &atnum, pert, out); // Calculate atomic number
            fprintf(out, "%d\n", atnum); // Write result to output file
        } else {
            fprintf(out, "Error processing formula: %s\n", chem);
        }
    }

    // Clean up resources
    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(pert->ch[i]);
    }
    free(pert); // Free periodic table memory
    free(chem); // Free memory for the chemical formula
    free(ext); // Free memory for the extened chemical formula
    fclose(in); 
    fclose(out);

    return 0;
}
#endif
