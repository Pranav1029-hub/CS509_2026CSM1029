#include <string.h>
#include "gemm.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))

// ==========================================
// BLOCKING GEMM IMPLEMENTATION
// Tiled 6-nested loop for cache reuse
// ==========================================
void gemm_blocking(const Matrix *A, const Matrix *B, Matrix *C, int blockSize) {
    int M = A->rows;
    int K = A->cols;
    int N = B->cols;

    // Zero-initialize output matrix memory
    memset(C->data, 0, M * N * sizeof(double));

    for (int ii = 0; ii < M; ii += blockSize) {
        for (int jj = 0; jj < N; jj += blockSize) {
            for (int kk = 0; kk < K; kk += blockSize) {

                // Mini-GEMM within the block/tile
                int i_max = MIN(ii + blockSize, M);
                int j_max = MIN(jj + blockSize, N);
                int k_max = MIN(kk + blockSize, K);

                for (int i = ii; i < i_max; ++i) {
                    for (int k = kk; k < k_max; ++k) {
                        double r = MAT_GET(*A, i, k);
                        for (int j = jj; j < j_max; ++j) {
                            MAT_GET(*C, i, j) += r * MAT_GET(*B, k, j);
                        }
                    }
                }

            }
        }
    }
}