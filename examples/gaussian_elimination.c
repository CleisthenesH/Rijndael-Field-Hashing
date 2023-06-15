#include <stdio.h>

#include "augmented_matrix.h"

void main()
{
	// Declare coefficients and vector
	uint8_t* coefficient = (uint8_t[]) { 
		1,2,3,4,
		1,7,4,6,
		4,6,2,3,
		6,7,8,1};

	uint8_t* vector = (uint8_t[]) {1,2,3,4};

	// Create augmented matrix
	struct augmented_matrix* matrix = augmented_matrix_new(4, coefficient, vector);

	// Display the original matrix
	printf("Original:\n");
	augmented_matrix_print(matrix);

	// Preform the elimination
	size_t rank_deficiency = gaussian_elimination(matrix);

	// Print the eliminated matrix
	printf("\nEliminated:\n");
	augmented_matrix_print(matrix);

	// Interpret rank deficiency, since we have it.
	if(rank_deficiency > 0)
		printf("\nMatrix isn't inevitable\n");

	// Free the augmented matrix
	augmented_matrix_free(matrix);
}
