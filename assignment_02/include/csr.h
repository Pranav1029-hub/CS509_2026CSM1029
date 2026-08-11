#ifndef CSR_H
#define CSR_H

#define INF 1000000000

typedef struct {
    int num_vertices;
    int num_edges;
    int *row_ptr;   // Size: num_vertices + 1
    int *col_idx;   // Size: num_edges
    int *values;    // Size: num_edges
} CSRGraph;

CSRGraph* create_csr_graph(int V, int E);
void free_csr_graph(CSRGraph *graph);

#endif