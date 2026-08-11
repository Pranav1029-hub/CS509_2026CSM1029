#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/csr.h"
#include "../include/bellman_ford.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    const char *filepath = argv[1];
    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        printf("Error: Could not open file %s\n", filepath);
        return 1;
    }

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2) {
        printf("Error: Invalid header in %s\n", filepath);
        fclose(fp);
        return 1;
    }

    CSRGraph *graph = create_csr_graph(V, E);
    graph->row_ptr[0] = 0;

    int current_edge = 0;
    for (int i = 0; i < V; i++) {
        int u, deg;
        fscanf(fp, "%d %d", &u, &deg);

        for (int d = 0; d < deg; d++) {
            int neighbor, weight;
            fscanf(fp, "%d %d", &neighbor, &weight);
            graph->col_idx[current_edge] = neighbor;
            graph->values[current_edge] = weight;
            current_edge++;
        }
        graph->row_ptr[i + 1] = current_edge;
    }

    char source_tag[16];
    int source = 0;
    if (fscanf(fp, "%s %d", source_tag, &source) != 2) {
        source = 0;
    }
    fclose(fp);

    BellmanFordResult res = run_bellman_ford(graph, source);

    printf("Algorithm: Bellman-Ford\n");
    printf("Source: %d\n", source);

    if (res.has_negative_cycle) {
        printf("Negative cycle: true\n");
    } else {
        printf("Vertex Distance\n");
        for (int i = 0; i < V; i++) {
            if (res.distances[i] == INF) {
                printf("%-6d INF\n", i);
            } else {
                printf("%-6d %d\n", i, res.distances[i]);
            }
        }
        printf("Negative cycle: none\n");
    }
    printf("Execution time: %.3f ms\n", res.execution_time_ms);

    free_bellman_ford_result(&res);
    free_csr_graph(graph);
    return 0;
}