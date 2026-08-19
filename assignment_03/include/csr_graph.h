#ifndef CSR_GRAPH_H
#define CSR_GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Compressed Sparse Row (CSR) Graph Representation
typedef struct {
    int V;              // Number of vertices
    int E_undirected;   // Number of undirected edges
    int total_entries;  // Size of col_idx and values (2 * E_undirected)
    int *row_ptr;       // Size V + 1
    int *col_idx;       // Size total_entries
    long long *values;  // Edge weights (Size total_entries)
} CSRGraph;

// Intermediate Adjacency List Structure for Input Parsing
typedef struct EdgeNode {
    int neighbor;
    long long weight;
    struct EdgeNode *next;
} EdgeNode;

typedef struct {
    int degree;
    EdgeNode *head;
} AdjList;

// Edge representation used for MST reporting and Kruskal sorting
typedef struct {
    int u;
    int v;
    long long weight;
} MSTEdge;

// Function Prototypes
CSRGraph* convert_adj_list_to_csr(int V, int E, AdjList *adj);
void free_csr_graph(CSRGraph *csr);

#endif // CSR_GRAPH_H