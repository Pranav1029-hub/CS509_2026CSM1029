#define __USE_MINGW_ANSI_STDIO 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>
#include "../include/csr_graph.h"
#include "../include/mst.h"

void print_output(const char *alg_name, const MSTResult *res) {
    printf("Algorithm: %s\n", alg_name);
    printf("MST edges:\n");
    for (int i = 0; i < res->edge_count; i++) {
        printf("%d %d %" PRId64 "\n", res->edges[i].u, res->edges[i].v, res->edges[i].weight);
    }
    printf("Total MST weight: %" PRId64 "\n", res->total_weight);
    printf("Execution time: %.3f ms\n\n", res->execution_time_ms);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <kruskal|prim|both> <input_file.txt>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *mode = argv[1];
    const char *filepath = argv[2];

    FILE *fp = fopen(filepath, "r");
    if (!fp) {
        fprintf(stderr, "Error: Could not open file %s\n", filepath);
        return EXIT_FAILURE;
    }

    int V, E;
    if (fscanf(fp, "%d %d", &V, &E) != 2) {
        fprintf(stderr, "Error: Invalid header in %s\n", filepath);
        fclose(fp);
        return EXIT_FAILURE;
    }

    AdjList *adj = (AdjList*)calloc(V, sizeof(AdjList));

    for (int i = 0; i < V; i++) {
        int u, deg;
        fscanf(fp, "%d %d", &u, &deg);
        adj[u].degree = deg;

        EdgeNode *tail = NULL;
        for (int d = 0; d < deg; d++) {
            int v;
            int64_t w;
            fscanf(fp, "%d %" SCNd64, &v, &w);

            EdgeNode *node = (EdgeNode*)malloc(sizeof(EdgeNode));
            node->neighbor = v;
            node->weight = w;
            node->next = NULL;

            if (!adj[u].head) {
                adj[u].head = node;
            } else {
                tail->next = node;
            }
            tail = node;
        }
    }
    fclose(fp);

    CSRGraph *csr = convert_adj_list_to_csr(V, E, adj);

    for (int i = 0; i < V; i++) {
        EdgeNode *curr = adj[i].head;
        while (curr) {
            EdgeNode *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(adj);

    if (strcmp(mode, "kruskal") == 0 || strcmp(mode, "both") == 0) {
        MSTResult res_k = run_kruskal_mst(csr);
        print_output("Kruskal's MST", &res_k);
        free_mst_result(&res_k);
    }

    if (strcmp(mode, "prim") == 0 || strcmp(mode, "both") == 0) {
        MSTResult res_p = run_prim_mst(csr);
        print_output("Prim's MST", &res_p);
        free_mst_result(&res_p);
    }

    free_csr_graph(csr);
    return EXIT_SUCCESS;
}