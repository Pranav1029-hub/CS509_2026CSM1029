#include "gemm.h"

// ==========================================
// SIMPLE GEMM IMPLEMENTATION
// Direct 3-nested loop algorithm
// ==========================================
void gemm_simple(const Matrix *A, const Matrix *B, Matrix *C) {
    int M = A->rows;
    int K = A->cols;
    int N = B->cols;

    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < K; ++k) {
                sum += MAT_GET(*A, i, k) * MAT_GET(*B, k, j);
            }
            MAT_GET(*C, i, j) = sum;
        }
    }
}