#define __USE_MINGW_ANSI_STDIO 1

#include "../include/csr_graph.h"
#include "../include/mst.h"
#include <time.h>

#ifdef _WIN32
#include <windows.h>
static double get_time_ms(void) {
    LARGE_INTEGER freq, counter;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&counter);
    return (double)counter.QuadPart * 1000.0 / (double)freq.QuadPart;
}
#else
static double get_time_ms(void) {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return ts.tv_sec * 1000.0 + ts.tv_nsec / 1000000.0;
}
#endif

typedef struct {
    int *parent;
    int *rank;
} DSU;

static DSU* create_dsu(int V) {
    DSU *dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(V * sizeof(int));
    dsu->rank = (int*)calloc(V, sizeof(int));
    for (int i = 0; i < V; i++) dsu->parent[i] = i;
    return dsu;
}

static int find_set(DSU *dsu, int i) {
    if (dsu->parent[i] == i)
        return i;
    return dsu->parent[i] = find_set(dsu, dsu->parent[i]);
}

static bool union_sets(DSU *dsu, int i, int j) {
    int root_i = find_set(dsu, i);
    int root_j = find_set(dsu, j);
    if (root_i != root_j) {
        if (dsu->rank[root_i] < dsu->rank[root_j]) {
            dsu->parent[root_i] = root_j;
        } else if (dsu->rank[root_i] > dsu->rank[root_j]) {
            dsu->parent[root_j] = root_i;
        } else {
            dsu->parent[root_j] = root_i;
            dsu->rank[root_i]++;
        }
        return true;
    }
    return false;
}

static void free_dsu(DSU *dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

static int compare_edges(const void *a, const void *b) {
    long long diff = ((MSTEdge*)a)->weight - ((MSTEdge*)b)->weight;
    return (diff > 0) - (diff < 0);
}

MSTResult run_kruskal_mst(const CSRGraph *csr) {
    MSTResult result;
    result.edges = (MSTEdge*)malloc((csr->V - 1) * sizeof(MSTEdge));
    result.edge_count = 0;
    result.total_weight = 0;

    double start_time = get_time_ms();

    // Step 1: Extract unique edges u < v from CSR
    MSTEdge *all_edges = (MSTEdge*)malloc(csr->E_undirected * sizeof(MSTEdge));
    int edge_idx = 0;
    for (int u = 0; u < csr->V; u++) {
        for (int j = csr->row_ptr[u]; j < csr->row_ptr[u + 1]; j++) {
            int v = csr->col_idx[j];
            if (u < v) {
                all_edges[edge_idx].u = u;
                all_edges[edge_idx].v = v;
                all_edges[edge_idx].weight = csr->values[j];
                edge_idx++;
            }
        }
    }

    // Step 2: Sort edges by non-decreasing weight
    qsort(all_edges, csr->E_undirected, sizeof(MSTEdge), compare_edges);

    // Step 3: DSU cycle detection & MST building
    DSU *dsu = create_dsu(csr->V);
    for (int i = 0; i < csr->E_undirected && result.edge_count < csr->V - 1; i++) {
        if (union_sets(dsu, all_edges[i].u, all_edges[i].v)) {
            result.edges[result.edge_count++] = all_edges[i];
            result.total_weight += all_edges[i].weight;
        }
    }

    double end_time = get_time_ms();
    result.execution_time_ms = end_time - start_time;

    free(all_edges);
    free_dsu(dsu);
    return result;
}