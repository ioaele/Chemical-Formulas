#ifndef PERIODIC_TABLE
#define PERIODIC_TABLE

#define N 118           ///< Maximum number of elements in the periodic table

/**
 * @brief Structure to hold the periodic table data.
 * 
 * This structure stores chemical element symbols and their corresponding 
 * atomic numbers in an array format. It includes an array for the symbols
 * and another for the atomic numbers.
 */
typedef struct {
    char *ch[N];         ///< Array of strings to hold element symbols
    int anum[N];        ///< Array of integers to hold atomic numbers
} PTABLE;


void createTable(PTABLE **c, char *argv[]);

#endif
