#include <stdio.h>
#include <stdlib.h>
#include "csr.h"

// Helper to create empty Adjacency List
AdjListGraph *create_adj_list(int V, int E) {
    AdjListGraph *graph = (AdjListGraph *)malloc(sizeof(AdjListGraph));
    graph->V = V;
    graph->E = E;
    graph->source = 0;
    graph->heads = (AdjListNode **)calloc(V, sizeof(AdjListNode *));
    return graph;
}

// Memory cleanup for Adjacency List
void free_adj_list(AdjListGraph *graph) {
    if (!graph) return;
    for (int i = 0; i < graph->V; ++i) {
        AdjListNode *curr = graph->heads[i];
        while (curr) {
            AdjListNode *temp = curr;
            curr = curr->next;
            free(temp);
        }
    }
    free(graph->heads);
    free(graph);
}

// Convert Adjacency List to Compressed Sparse Row (CSR) format
CSRGraph *adj_list_to_csr(const AdjListGraph *adj_graph) {
    if (!adj_graph) return NULL;

    CSRGraph *csr = (CSRGraph *)malloc(sizeof(CSRGraph));
    csr->V = adj_graph->V;
    
    // Count total outgoing connections in the adjacency list
    int total_edges = 0;
    for (int i = 0; i < adj_graph->V; ++i) {
        AdjListNode *curr = adj_graph->heads[i];
        while (curr) {
            total_edges++;
            curr = curr->next;
        }
    }
    csr->E = total_edges;

    // Allocate CSR arrays
    csr->row_ptr = (int *)malloc((csr->V + 1) * sizeof(int));
    csr->col_idx = (int *)malloc(csr->E * sizeof(int));
    csr->values  = (int *)malloc(csr->E * sizeof(int));

    // Populate row_ptr, col_idx, and values
    csr->row_ptr[0] = 0;
    int edge_count = 0;

    for (int u = 0; u < adj_graph->V; ++u) {
        AdjListNode *curr = adj_graph->heads[u];
        while (curr) {
            csr->col_idx[edge_count] = curr->neighbor;
            csr->values[edge_count]  = curr->weight;
            edge_count++;
            curr = curr->next;
        }
        csr->row_ptr[u + 1] = edge_count;
    }

    return csr;
}

// Free CSR graph memory
void free_csr(CSRGraph *csr) {
    if (!csr) return;
    free(csr->row_ptr);
    free(csr->col_idx);
    free(csr->values);
    free(csr);
}

// Print CSR Structure
void print_csr(const CSRGraph *csr) {
    printf("CSR Format:\n");
    printf("row_ptr: ");
    for (int i = 0; i <= csr->V; ++i) {
        printf("%d ", csr->row_ptr[i]);
    }
    printf("\ncol_idx: ");
    for (int i = 0; i < csr->E; ++i) {
        printf("%d ", csr->col_idx[i]);
    }
    printf("\nvalues:  ");
    for (int i = 0; i < csr->E; ++i) {
        printf("%d ", csr->values[i]);
    }
    printf("\n");
}