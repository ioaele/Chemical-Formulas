#include <stdio.h>
#include <stdlib.h>
#include "periodicTable.h"

/**
 * @brief Creates and initializes the periodic table from a file.
 * 
 * This function allocates memory for the `PTABLE` structure and reads
 * element data from a file specified in the command line arguments.
 * The file should contain element symbols and their atomic numbers.
 *
 * @param pert Pointer to the pointer of the `PTABLE` structure to be initialized.
 * @param argv Command line arguments where `argv[1]` is the file path.
 */
void createTable(PTABLE **pert, char *argv[]) {
  
    int i = 0;
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        perror("Unable to open file");
        exit(-1);
    }
 
    // Allocate memory for the PTABLE structure
    *pert = (PTABLE *)malloc(sizeof(PTABLE));
    if (*pert == NULL) {
        perror("Memory allocation failed");
        fclose(fp);
        exit(-1);
    }
    
    // Allocate memory for each string in ch array
    for (i = 0; i < N; i++) {
        (*pert)->ch[i] = (char *)malloc(3 * sizeof(char));
        if ((*pert)->ch[i] == NULL) {
            perror("Memory allocation failed for element name");
            fclose(fp);
            free(*pert);
            exit(-1);
        }
    }
  
    i = 0;

    // Read data from the file
    while (fscanf(fp, "%s %d", (*pert)->ch[i], &(*pert)->anum[i]) != EOF ) {
        i++;
    }
    fclose(fp);
}

#ifdef DEBUG1
/**
 * @brief Main function for testing `createTable` function in debug mode.
 * 
 * This function is compiled only when DEBUG1 is defined. It initializes
 * the periodic table by calling `createTable` and prints each element
 * with its atomic number.
 *
 * @param argc Argument count.
 * @param argv Argument vector; `argv[1]` should be the filename containing the periodic table data.
 * @return Returns 0 on success, -1 on error.
 */
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return -1;
    }

    PTABLE *pert = (PTABLE *) malloc(sizeof(PTABLE)); // Allocate memory for PTABLE
    if (pert == NULL) {
        perror("Memory allocation for periodic table failed.");
        exit(-1);
    }
    createTable(&pert, argv);

    // Print out the elements read
    for (int i = 0; i < N; i++) {
        if (pert->ch[i] != NULL && pert->anum[i] != 0) {
            printf("Element: %s, Atomic number: %d\n", pert->ch[i], pert->anum[i]);
        }
    }

    // Free allocated memory
    for (int i = 0; i < N; i++) {
        free(pert->ch[i]);
    }
    free(pert);
    return 0;
}
#endif
