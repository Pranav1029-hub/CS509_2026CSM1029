#ifndef GEMM_H
#define GEMM_H

#include <stdio.h>
#include <stdlib.h>

#ifndef BLOCK_SIZE
#define BLOCK_SIZE 32
#endif

// Matrix structure storing dimensions and contiguous 1D array data
typedef struct {
    int rows;
    int cols;
    double *data;
} Matrix;

// Function Declarations
Matrix create_matrix(int rows, int cols);
void free_matrix(Matrix *mat);
void print_matrix(const Matrix *mat);

void gemm_simple(const Matrix *A, const Matrix *B, Matrix *C);
void gemm_blocking(const Matrix *A, const Matrix *B, Matrix *C, int blockSize);

// Helper macro for 2D indexing on contiguous 1D array
#define MAT_GET(mat, r, c) ((mat).data[(r) * (mat).cols + (c)])

#endif // GEMM_H