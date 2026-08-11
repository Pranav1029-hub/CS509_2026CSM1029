#include <stdio.h>
#include <stdlib.h>
#include "../include/csr.h"

CSRGraph* create_csr_graph(int V, int E) {
    CSRGraph *graph = (CSRGraph*)malloc(sizeof(CSRGraph));
    graph->num_vertices = V;
    graph->num_edges = E;
    graph->row_ptr = (int*)malloc((V + 1) * sizeof(int));
    graph->col_idx = (int*)malloc(E * sizeof(int));
    graph->values = (int*)malloc(E * sizeof(int));
    return graph;
}

void free_csr_graph(CSRGraph *graph) {
    if (graph) {
        if (graph->row_ptr) free(graph->row_ptr);
        if (graph->col_idx) free(graph->col_idx);
        if (graph->values) free(graph->values);
        free(graph);
    }
}