#include <stdio.h>
#include <stdlib.h>
#include "../include/floyd_warshall.h"

#ifdef _WIN32
#include <windows.h>
static double get_time_ms() {
    LARGE_INTEGER freq, count;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&count);
    return (double)count.QuadPart * 1000.0 / freq.QuadPart;
}
#else
#include <time.h>
static double get_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
}
#endif

FloydWarshallResult run_floyd_warshall(int V, int **input_matrix) {
    int **dist = (int**)malloc(V * sizeof(int*));
    for (int i = 0; i < V; i++) {
        dist[i] = (int*)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            dist[i][j] = input_matrix[i][j];
        }
    }

    int has_neg_cycle = 0;

    // === TIMING STARTS (Excluding file I/O & allocation) ===
    double start_time = get_time_ms();

    // Core Dynamic Programming Loop
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    if (dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }

    // Negative cycle detection check on diagonal
    for (int i = 0; i < V; i++) {
        if (dist[i][i] < 0) {
            has_neg_cycle = 1;
            break;
        }
    }

    double end_time = get_time_ms();
    // === TIMING ENDS ===

    FloydWarshallResult res;
    res.V = V;
    res.dist_matrix = dist;
    res.has_negative_cycle = has_neg_cycle;
    res.execution_time_ms = end_time - start_time;

    return res;
}

void free_floyd_warshall_result(FloydWarshallResult *result) {
    if (result->dist_matrix) {
        for (int i = 0; i < result->V; i++) free(result->dist_matrix[i]);
        free(result->dist_matrix);
    }
}