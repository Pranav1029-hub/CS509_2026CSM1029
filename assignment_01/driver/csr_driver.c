#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../CSR_Graph/include/csr.h"

int run_csr_driver(const char *filepath, int source_vertex) {
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error: Cannot open CSR graph input file '%s'\n", filepath);
        return 1;
    }

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2) {
        printf("Error: Invalid graph header format\n");
        fclose(fp);
        return 1;
    }

    int *degrees = (int *)calloc(V, sizeof(int));
    int **adj = (int **)malloc(V * sizeof(int *));
    int **weights = (int **)malloc(V * sizeof(int *));

    for (int i = 0; i < V; i++) {
        int u, deg;
        fscanf(fp, "%d %d", &u, &deg);
        degrees[u] = deg;
        adj[u] = (int *)malloc(deg * sizeof(int));
        weights[u] = (int *)malloc(deg * sizeof(int));
        for (int j = 0; j < deg; j++) {
            fscanf(fp, "%d", &adj[u][j]);
            weights[u][j] = 1; // Default edge weight
        }
    }
    fclose(fp);

    // Isolate timing
    clock_t start = clock();
    
    // Call CSR processing here if available
    
    clock_t end = clock();

    double exec_time_ms = ((double)(end - start) / CLOCKS_PER_SEC) * 1000.0;

    printf("Algorithm: CSR Graph Processing\n");
    printf("Source Vertex: %d\n", source_vertex);
    printf("Vertices: %d, Edges: %d\n", V, E);
    printf("Execution time: %.3f ms\n", exec_time_ms);

    for (int i = 0; i < V; i++) {
        free(adj[i]);
        free(weights[i]);
    }
    free(adj);
    free(weights);
    free(degrees);

    return 0;
}