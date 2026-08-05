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

void generate_graph_file(int V, const char *filename) {
    char filepath[256];
    snprintf(filepath, sizeof(filepath), "data/%s", filename);

    printf("Generating %s (V=%d)... ", filename, V);
    fflush(stdout);

    FILE *f = fopen(filepath, "w");
    if (!f) {
        fprintf(stderr, "Error creating file %s\n", filepath);
        return;
    }

    // Average 4 edges per vertex
    int avg_deg = 4;
    int E = (V * avg_deg) / 2;

    fprintf(f, "%d %d\n", V, E);

    for (int u = 0; u < V; ++u) {
        int degree = rand() % 5 + 1; // 1 to 5 neighbors
        fprintf(f, "%d %d", u, degree);

        for (int d = 0; d < degree; ++d) {
            int neighbor = rand() % V;
            fprintf(f, " %d", neighbor);
        }
        fprintf(f, "\n");
    }

    fprintf(f, "SOURCE 0\n");
    fclose(f);
    printf("Done!\n");
}

int main(void) {
    srand((unsigned int)time(NULL));
    mkdir_p("data");

    int sizes[] = {10, 100, 10000, 50000, 100000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);

    for (int i = 0; i < num_sizes; ++i) {
        char filename[64];
        snprintf(filename, sizeof(filename), "csr_%d.txt", sizes[i]);
        generate_graph_file(sizes[i], filename);
    }

    printf("\nAll graph test files generated in 'CSR Graph/data/' folder!\n");
    return 0;
}