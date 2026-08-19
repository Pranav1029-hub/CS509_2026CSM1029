#ifndef MST_H
#define MST_H

#include "csr_graph.h"

typedef struct {
    MSTEdge *edges;
    int edge_count;
    long long total_weight;
    double execution_time_ms;
} MSTResult;

// Algorithm Declarations
MSTResult run_kruskal_mst(const CSRGraph *csr);
MSTResult run_prim_mst(const CSRGraph *csr);
void free_mst_result(MSTResult *res);

#endif // MST_H