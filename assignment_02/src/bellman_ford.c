#include <stdio.h>
#include <stdlib.h>
#include "../include/bellman_ford.h"

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

BellmanFordResult run_bellman_ford(const CSRGraph *graph, int source) {
    int V = graph->num_vertices;
    int *dist = (int*)malloc(V * sizeof(int));
    
    for (int i = 0; i < V; i++) dist[i] = INF;
    dist[source] = 0;

    int has_neg_cycle = 0;

    // === TIMING STARTS (Excluding file I/O & memory allocation) ===
    double start_time = get_time_ms();

    // 1. Relax edges V - 1 times
    for (int pass = 0; pass < V - 1; pass++) {
        int updated = 0;
        for (int u = 0; u < V; u++) {
            if (dist[u] == INF) continue;

            int start_edge = graph->row_ptr[u];
            int end_edge = graph->row_ptr[u + 1];

            for (int e = start_edge; e < end_edge; e++) {
                int v = graph->col_idx[e];
                int weight = graph->values[e];

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    updated = 1;
                }
            }
        }
        if (!updated) break;
    }

    // 2. Pass V: Negative cycle detection
    for (int u = 0; u < V; u++) {
        if (dist[u] == INF) continue;

        int start_edge = graph->row_ptr[u];
        int end_edge = graph->row_ptr[u + 1];

        for (int e = start_edge; e < end_edge; e++) {
            int v = graph->col_idx[e];
            int weight = graph->values[e];

            if (dist[u] + weight < dist[v]) {
                has_neg_cycle = 1;
                break;
            }
        }
        if (has_neg_cycle) break;
    }

    double end_time = get_time_ms();
    // === TIMING ENDS ===

    BellmanFordResult res;
    res.distances = dist;
    res.has_negative_cycle = has_neg_cycle;
    res.execution_time_ms = end_time - start_time;

    return res;
}

void free_bellman_ford_result(BellmanFordResult *result) {
    if (result->distances) free(result->distances);
}