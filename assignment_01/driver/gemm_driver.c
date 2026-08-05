#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../Matrix_Multiplication/include/gemm.h"

int run_gemm_driver(const char *algo_type, const char *filepath, int block_size) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error: Cannot open GEMM input file '%s'\n", filepath);
        return 1;
    }

    int M, K, N;
    if (fscanf(fp, "%d %d %d", &M, &K, &N) != 3) {
        printf("Error: Invalid GEMM header format\n");
        fclose(fp);
        return 1;
    }

    Matrix A, B, C;
    A.rows = M; A.cols = K; A.data = (double *)calloc(M * K, sizeof(double));
    B.rows = K; B.cols = N; B.data = (double *)calloc(K * N, sizeof(double));
    C.rows = M; C.cols = N; C.data = (double *)calloc(M * N, sizeof(double));

    if (!A.data || !B.data || !C.data) {
        printf("Error: Allocation failed\n");
        fclose(fp);
        return 1;
    }

    for (int i = 0; i < M * K; i++) fscanf(fp, "%lf", &A.data[i]);
    for (int i = 0; i < K * N; i++) fscanf(fp, "%lf", &B.data[i]);
    fclose(fp);

    clock_t start = clock();
    if (strcmp(algo_type, "simple") == 0) {
        gemm_simple(&A, &B, &C);
        printf("Algorithm: GEMM Simple\n");
    } else {
        gemm_blocking(&A, &B, &C, block_size);
        printf("Algorithm: GEMM Blocking (Block size: %d)\n", block_size);
    }
    clock_t end = clock();

    double exec_time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Result matrix:\n");
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            printf("%.1f ", C.data[i * N + j]);
        }
        printf("\n");
    }

    printf("Execution time: %.3f ms\n", exec_time_ms);

    free(A.data);
    free(B.data);
    free(C.data);
    return 0;
}