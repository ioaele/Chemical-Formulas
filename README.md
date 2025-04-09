@mainpage EPL232 Assignment 2: Chemical Formula Processing with Dynamic Data Structures
@author Eleni Ioannou
@last updated: 28/10/24

This program for the parses, verifies , and analyses chemical formulas using dynamic data structures. It supports operations such as checking for balanced parentheses, expanding formulas, and calculating the total number of protons based on the periodic table.

Features:
	•	Balanced Parentheses Verification: Ensures that the parentheses in the chemical formulas are properly matched and nested.
	•	Formula Expansion: Expands chemical formulas to reveal their full structural representation.
	•	Proton Count Calculation: Computes the total number of protons present(the atomic number) in the given chemical formulas using atomic numbers from the periodic table.
	•	Dynamic Data Structures: Utilizes stacks and linked lists to efficiently manage the data involved in processing formulas.

Warning:
It supports the formulas where the number for the repeated wanted formula is up to two digits number.
The allocated memory for each chemical formula in inputFile is 50B as well as the extended version that is printed in outputFile. But, only the original chemical formula can be realloc (allocate more space) - doubled each time.


Compilation and Execution with using the make file:

gcc parseFormula.c periodicTable.c chemExt.c parenthesisBal.c protonNum.c stack.c -o parseFormula
./parseFormula.c /FILE THAT CONTAINS THE PERIODIC TABLE/ * **
*
	•	  - `-v`: Verify if parentheses are balanced. ** / NAME OF INPUT FILE
	•	  - `-ext`: Compute the extended version of the formulas and write to an output file. ** NAME OF INPUT FILE NAME OF OUTPUT FILE
	•	  - `-pn`: Compute the total proton number (atomic number) of formulas based on a periodic table. **NAME OF INPUT FILE NAME OF OUTPUT FILE



Comments: 
The program was very challenging but I’m glad I managed to make it work! 
