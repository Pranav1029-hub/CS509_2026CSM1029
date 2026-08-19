#include "../include/csr_graph.h"

CSRGraph* convert_adj_list_to_csr(int V, int E, AdjList *adj) {
    CSRGraph *csr = (CSRGraph*)malloc(sizeof(CSRGraph));
    csr->V = V;
    csr->E_undirected = E;
    csr->row_ptr = (int*)malloc((V + 1) * sizeof(int));

    int total_entries = 0;
    for (int i = 0; i < V; i++) {
        total_entries += adj[i].degree;
    }
    csr->total_entries = total_entries;
    csr->col_idx = (int*)malloc(total_entries * sizeof(int));
    csr->values = (long long*)malloc(total_entries * sizeof(long long));

    csr->row_ptr[0] = 0;
    int current_idx = 0;
    for (int i = 0; i < V; i++) {
        EdgeNode *curr = adj[i].head;
        while (curr != NULL) {
            csr->col_idx[current_idx] = curr->neighbor;
            csr->values[current_idx] = curr->weight;
            current_idx++;
            curr = curr->next;
        }
        csr->row_ptr[i + 1] = current_idx;
    }

    return csr;
}

void free_csr_graph(CSRGraph *csr) {
    if (!csr) return;
    free(csr->row_ptr);
    free(csr->col_idx);
    free(csr->values);
    free(csr);
}