#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

#ifdef _WIN32
#include <direct.h>
#define mkdir_p(path) _mkdir(path)
#else
#define mkdir_p(path) mkdir(path, 0777)
#endif

void generate_gemm_file(int size, const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);

    printf("Generating %s (%dx%d)... ", filename, size, size);
    fflush(stdout);

    FILE *f = fopen(filepath, "w");
    if (f == NULL) {
        fprintf(stderr, "\nError: Could not create file %s\n", filepath);
        return;
    }

    int M = size, K = size, N = size;

    // 1. Write Header: M K N
    fprintf(f, "%d %d %d\n", M, K, N);

    // 2. Write Matrix A (M x K)
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < K; ++j) {
            fprintf(f, "%d%s", (rand() % 10) + 1, (j == K - 1 ? "" : " "));
        }
        fprintf(f, "\n");
    }

    // 3. Write Matrix B (K x N)
    for (int i = 0; i < K; ++i) {
        for (int j = 0; j < N; ++j) {
            fprintf(f, "%d%s", (rand() % 10) + 1, (j == N - 1 ? "" : " "));
        }
        fprintf(f, "\n");
    }

    fclose(f);
    printf("Done!\n");
}

int main(void) {
    // Seed random number generator
    srand((unsigned int)time(NULL));

    // Ensure data directory exists
    mkdir_p("data");

    // Sizes specified
    int sizes[] = {10, 100, 1000, 10000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; ++i) {
        char filename[64];
        snprintf(filename, sizeof(filename), "gemm_%d.txt", sizes[i]);
        generate_gemm_file(sizes[i], filename);
    }

    printf("\nAll test files generated inside 'data/' folder!\n");
    return 0;
}