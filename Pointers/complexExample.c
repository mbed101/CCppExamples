#include <stdio.h>
#include <stdlib.h>

int main()
{
    int rows = 3;
    int columns = 4;

    int (*matrix)[columns];  // Declare a pointer to an array of 4 integers

    matrix = (int (*)[columns]) malloc(rows * columns * sizeof(int));
    // Allocate memory for a 3x4 matrix and cast the result to a pointer to an array of 4 integers

    if (matrix == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    // Fill the matrix with values
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            *(*(matrix + i) + j) = i * columns + j;
        }
    }

    // Print the matrix
    printf("The matrix is:\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            printf("%d ", *(*(matrix + i) + j));
        }
        printf("\n");
    }

    // Free the dynamically allocated memory
    free(matrix);

    return 0;
}

This program demonstrates the use of a pointer to a two-dimensional array in C.
The pointer matrix is declared as a pointer to an array of 4 integers. 
Memory for a 3x4 matrix is then dynamically allocated using malloc(), and the result is cast to a pointer to an array of 4 integers. 
The matrix is filled with values and printed, and the dynamically allocated memory is freed using free() when the program is finished.
