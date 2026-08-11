#ifndef BELLMAN_FORD_H
#define BELLMAN_FORD_H

#include "csr.h"

typedef struct {
    int *distances;
    int has_negative_cycle;
    double execution_time_ms;
} BellmanFordResult;

BellmanFordResult run_bellman_ford(const CSRGraph *graph, int source);
void free_bellman_ford_result(BellmanFordResult *result);

#endif