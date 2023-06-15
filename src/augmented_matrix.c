// Copyright 2023 Kieran W Harvie. All rights reserved.

#include "augmented_matrix.h"
#include "field_operations.h"

#include <stdio.h>
#include <string.h>

// Swap rows i and j
static void inline augmented_matrix_swap_row(struct augmented_matrix* matrix, size_t i, size_t j)
{
	uint8_t buffer;

	for (size_t k = 0; k < matrix->size; k++)
	{
		buffer = matrix->matrix[matrix->size * i + k];
		matrix->matrix[matrix->size * i + k] = matrix->matrix[matrix->size * j + k];
		matrix->matrix[matrix->size * j + k] = buffer;
	}

	buffer = matrix->vector[i];
	matrix->vector[i] = matrix->vector[j];
	matrix->vector[j] = buffer;
}

// Rearrange the matrix such that all zeros in the ith column i lower than the ith row are moved to the bottom
static size_t inline augmented_matrix_rearrange_zeros(struct augmented_matrix* matrix, size_t i)
{
	size_t leading_zeros = 0;

	for (size_t j = i; j < matrix->size - leading_zeros; j++)
	{
		while (matrix->matrix[i + matrix->size * j] == 0)
		{
			leading_zeros++;

			if (j != matrix->size - leading_zeros)
				augmented_matrix_swap_row(matrix, j, matrix->size - leading_zeros);
			else
				break;
		}
	}

	return leading_zeros;
}

// Scale row i
static void inline augmented_matrix_scale_row(struct augmented_matrix* matrix, size_t i, uint8_t scale)
{
	for (size_t k = 0; k < matrix->size; k++)
		matrix->matrix[matrix->size * i + k] = gmul(matrix->matrix[matrix->size * i + k], scale);

	matrix->vector[i] = gmul(matrix->vector[i], scale);
}

// Adds row j to i
static void inline augmented_matrix_add_row(struct augmented_matrix* matrix, size_t i, size_t j)
{
	for (size_t k = 0; k < matrix->size; k++)
		matrix->matrix[matrix->size * i + k] = gadd(matrix->matrix[matrix->size * i + k], matrix->matrix[matrix->size * j + k]);

	matrix->vector[i] = gadd(matrix->vector[i], matrix->vector[j]);
}

// Adds scaled row j to i
static void inline augmented_matrix_scale_and_add_row(struct augmented_matrix* matrix, size_t i, size_t j, uint8_t scale)
{
	uint8_t buffer;

	for (size_t k = 0; k < matrix->size; k++)
	{
		buffer = gmul(scale, matrix->matrix[matrix->size * j + k]);

		matrix->matrix[matrix->size * i + k] = gadd(matrix->matrix[matrix->size * i + k], buffer);
	}

	buffer = gmul(scale, matrix->vector[j]);

	matrix->vector[i] = gadd(matrix->vector[i], buffer);
}

// Simple constructor for augmented augmented matrices
struct augmented_matrix* augmented_matrix_new(size_t size, uint8_t* matrix, uint8_t* vector)
{
	struct augmented_matrix* output = malloc(sizeof(struct augmented_matrix));

	if(!output)
		return NULL;

	output->matrix = malloc(sizeof(uint8_t)*size*size);

	if(!output->matrix)
	{
		free(output);
		return NULL;
	}

	output->vector = malloc(sizeof(uint8_t)*size);

	if(!output->vector)
	{
		free(output->matrix);
		free(output);
		return NULL;
	}

	output->size = size;

	memcpy(output->matrix, matrix, sizeof(uint8_t)*size*size);
	memcpy(output->vector, vector, sizeof(uint8_t)*size);

	return output;
}

// Free the memory associated with the given augmented matrix
void augmented_matrix_free(struct augmented_matrix* matrix)
{
	free(matrix->matrix);
	free(matrix->vector);
	free(matrix);
}

// Preform Gaussian elimination in situ of the given matrix
size_t gaussian_elimination(struct augmented_matrix* matrix)
{
	size_t rank_deficiency = 0;

	// Make the matrix an upper triangular with leading zeros
	for (size_t i = 0; i < matrix->size; i++)
	{
		const size_t leading_zeros = augmented_matrix_rearrange_zeros(matrix, i);

		// Will halt loop iff the matrix isn't invertible
		const uint8_t inv = ginv(matrix->matrix[i + matrix->size * i]);
		augmented_matrix_scale_row(matrix, i, inv);

		for (size_t j = i + 1; j < matrix->size - leading_zeros; j++)
		{
			const uint8_t inv = ginv(matrix->matrix[i + matrix->size * j]);
			augmented_matrix_scale_row(matrix, j, inv);
			augmented_matrix_add_row(matrix, j, i);
		}

		// The matrix isn't invertible record the rank deficiency
		if(leading_zeros + i == matrix->size)
		{
			rank_deficiency = leading_zeros;
			break;
		}
	}

	// Make the matrix the identity matrix
	// This can be optimized, incorporate our knowledge of rank deficiency
	for (size_t i = 1; i < matrix->size; i++)
		for (size_t j = 0; j < i; j++)
			if (matrix->matrix[matrix->size * j + i])
			{
				const uint8_t scale = matrix->matrix[matrix->size * j + i];
				augmented_matrix_scale_and_add_row(matrix, j, i, scale);
			}

	return rank_deficiency;
}

// Pretty print an augmented matrix
void augmented_matrix_print(struct augmented_matrix* matrix)
{
	for (size_t i = 0; i < matrix->size; i++)
	{
		for (size_t j = 0; j < matrix->size; j++)
			printf("%02X ", matrix->matrix[j + i * matrix->size]);

		printf("| %02X\n", matrix->vector[i]);
	}
}

