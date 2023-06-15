// Copyright 2023 Kieran W Harvie. All rights reserved.

#ifndef AUGMENTED_MATRIX_GUARD
#define AUGMENTED_MATRIX_GUARD

#include <stdint.h>
#include <stdlib.h>

// Currently only supports a column vector of constants instead of a full second matrix.
struct augmented_matrix
{
	size_t size;
	uint8_t* matrix;
	uint8_t* vector;
};

struct augmented_matrix* augmented_matrix_new(size_t size, uint8_t* matrix, uint8_t* vector);
void augmented_matrix_free(struct augmented_matrix* matrix);

void augmented_matrix_print(struct augmented_matrix* matrix);
size_t gaussian_elimination(struct augmented_matrix* matrix);

#endif

