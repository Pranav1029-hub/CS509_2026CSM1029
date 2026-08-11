#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/floyd_warshall.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", filepath);
        return 1;
    }

    int V;
    if (fscanf(fp, "%d", &V) != 1) {
        printf("Error: Invalid header in %s\n", filepath);
        fclose(fp);
        return 1;
    }

    int **matrix = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        matrix[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            char val[32];
            fscanf(fp, "%s", val);
            if (strcmp(val, "INF") == 0) {
                matrix[i][j] = INF;
            } else {
                matrix[i][j] = atoi(val);
            }
        }
    }
    fclose(fp);

    FloydWarshallResult res = run_floyd_warshall(V, matrix);

    printf("Algorithm: Floyd-Warshall\n");

    if (res.has_negative_cycle) {
        printf("Negative cycle: true\n");
    } else {
        printf("Distance matrix:\n");
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (res.dist_matrix[i][j] == INF) {
                    printf("%-5s", "INF");
                } else {
                    printf("%-5d", res.dist_matrix[i][j]);
                }
            }
            printf("\n");
        }
        printf("Negative cycle: none\n");
    }
    printf("Execution time: %.3f ms\n", res.execution_time_ms);

    for (int i = 0; i < V; i++) free(matrix[i]);
    free(matrix);
    free_floyd_warshall_result(&res);
    return 0;
}