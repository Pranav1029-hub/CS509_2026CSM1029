#ifndef CSR_H
#define CSR_H

#include <stdio.h>
#include <stdlib.h>

// Standard Adjacency List Node
typedef struct AdjListNode {
    int neighbor;
    int weight; // Set to 1 for unweighted graphs
    struct AdjListNode *next;
} AdjListNode;

// Intermediate Adjacency List Representation
typedef struct {
    int V;
    int E;
    int source;
    AdjListNode **heads;
} AdjListGraph;

// Compressed Sparse Row (CSR) Representation
typedef struct {
    int V;
    int E;
    int *row_ptr; // Size: V + 1
    int *col_idx; // Size: total outgoing edges
    int *values;  // Size: total outgoing edges
} CSRGraph;

// Function Declarations
AdjListGraph *create_adj_list(int V, int E);
void free_adj_list(AdjListGraph *graph);

CSRGraph *adj_list_to_csr(const AdjListGraph *adj_graph);
void free_csr(CSRGraph *csr);

void print_csr(const CSRGraph *csr);

#endif // CSR_H