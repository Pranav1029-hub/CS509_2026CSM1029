#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#define INF 1000000000

typedef struct {
    int V;
    int **dist_matrix;
    int has_negative_cycle;
    double execution_time_ms;
} FloydWarshallResult;

FloydWarshallResult run_floyd_warshall(int V, int **input_matrix);
void free_floyd_warshall_result(FloydWarshallResult *result);

#endif