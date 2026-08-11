#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#ifdef _WIN32
#include <direct.h>
#define MKDIR(dir) _mkdir(dir)
#else
#include <sys/stat.h>
#define MKDIR(dir) mkdir(dir, 0777)
#endif

typedef struct {
    int to;
    int weight;
} Edge;

typedef struct {
    int count;
    int capacity;
    Edge *edges;
} AdjList;

void add_edge(AdjList *adj, int to, int weight) {
    if (adj->count == adj->capacity) {
        adj->capacity = (adj->capacity == 0) ? 4 : adj->capacity * 2;
        adj->edges = (Edge*)realloc(adj->edges, adj->capacity * sizeof(Edge));
    }
    adj->edges[adj->count].to = to;
    adj->edges[adj->count].weight = weight;
    adj->count++;
}

// Generate Bellman-Ford weighted directed graph (DAG ensures no negative cycles)
void generate_bellman_ford(const char *filename, int V, int target_E) {
    printf("Generating Bellman-Ford test file: %s (V=%d, E=%d)...\n", filename, V, target_E);
    
    AdjList *adj = (AdjList*)calloc(V, sizeof(AdjList));
    int actual_E = 0;

    // 1. Create a backbone path (0 -> 1 -> 2 ... -> V-1) to ensure reachability
    for (int i = 0; i < V - 1; i++) {
        int weight = (rand() % 25) - 4; // Weights between -4 and 20
        add_edge(&adj[i], i + 1, weight);
        actual_E++;
    }

    // 2. Add remaining random edges (u -> v with u < v to guarantee no negative cycles)
    while (actual_E < target_E) {
        int u = rand() % (V - 1);
        int max_span = (V - 1 - u < 50) ? (V - 1 - u) : 50; 
        if (max_span <= 0) continue;
        
        int v = u + 1 + (rand() % max_span);
        int weight = (rand() % 25) - 4;
        add_edge(&adj[u], v, weight);
        actual_E++;
    }

    // 3. Write to file
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open file %s for writing.\n", filename);
        for (int i = 0; i < V; i++) if (adj[i].edges) free(adj[i].edges);
        free(adj);
        return;
    }

    // Header: V E
    fprintf(fp, "%d %d\n", V, actual_E);

    // Adjacency list: u degree neighbor1 weight1 neighbor2 weight2 ...
    for (int u = 0; u < V; u++) {
        fprintf(fp, "%d %d", u, adj[u].count);
        for (int e = 0; e < adj[u].count; e++) {
            fprintf(fp, " %d %d", adj[u].edges[e].to, adj[u].edges[e].weight);
        }
        fprintf(fp, "\n");
    }

    // Footer: SOURCE 0
    fprintf(fp, "SOURCE 0\n");
    fclose(fp);

    // Clean up
    for (int i = 0; i < V; i++) {
        if (adj[i].edges) free(adj[i].edges);
    }
    free(adj);

    printf("  [Done] %s created successfully.\n", filename);
}

// Generate Floyd-Warshall dense matrix file
void generate_floyd_warshall(const char *filename, int V, double density) {
    printf("Generating Floyd-Warshall test file: %s (V=%d)...\n", filename, V);
    
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error: Could not open file %s for writing.\n", filename);
        return;
    }

    // Header: V
    fprintf(fp, "%d\n", V);

    // Stream V x V matrix directly to file (Low memory footprint)
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (i == j) {
                fprintf(fp, "0");
            } else if (i < j) {
                double r = (double)rand() / RAND_MAX;
                if (r < density) {
                    int weight = (rand() % 25) - 4; // Weights between -4 and 20
                    fprintf(fp, "%d", weight);
                } else {
                    fprintf(fp, "INF");
                }
            } else {
                // i > j: INF ensures strict DAG structure (no cycles)
                fprintf(fp, "INF");
            }

            if (j < V - 1) fprintf(fp, " ");
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
    printf("  [Done] %s created successfully.\n", filename);
}

int main() {
    srand(42); // Seed for reproducible test cases

    // Create output directory
    MKDIR("assignment_02");
    MKDIR("assignment_02/data");

    printf("==================================================\n");
    printf(" Generating Assignment 2 Test Files (C Version)   \n");
    printf("==================================================\n\n");

    // 1. Generate Bellman-Ford Test Cases (Sparse graphs: E ≈ 3V)
    generate_bellman_ford("assignment_02/data/bf_10.txt", 10, 25);
    generate_bellman_ford("assignment_02/data/bf_100.txt", 100, 300);
    generate_bellman_ford("assignment_02/data/bf_10000.txt", 10000, 30000);
    generate_bellman_ford("assignment_02/data/bf_50000.txt", 50000, 150000);
    generate_bellman_ford("assignment_02/data/bf_100000.txt", 100000, 300000);

    printf("\n");

    // 2. Generate Floyd-Warshall Test Cases
    generate_floyd_warshall("assignment_02/data/fw_10.txt", 10, 0.40);
    generate_floyd_warshall("assignment_02/data/fw_100.txt", 100, 0.20);
    generate_floyd_warshall("assignment_02/data/fw_500.txt", 500, 0.10);
    generate_floyd_warshall("assignment_02/data/fw_1000.txt", 1000, 0.05);
    generate_floyd_warshall("assignment_02/data/fw_2000.txt", 2000, 0.02);

    printf("\n==================================================\n");
    printf(" All test cases generated in 'assignment_02/data/'\n");
    printf("==================================================\n");

    return 0;
}