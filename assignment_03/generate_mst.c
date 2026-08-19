#define __USE_MINGW_ANSI_STDIO 1 // Enables standard C99 %lld support on MinGW/Windows

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <inttypes.h>

typedef struct Node {
    int neighbor;
    int64_t weight;
    struct Node *next;
} Node;

typedef struct {
    int degree;
    Node *head;
} AdjList;

// Check if an undirected edge (u, v) already exists
static bool edge_exists(const AdjList *adj, int u, int v) {
    Node *curr = adj[u].head;
    while (curr) {
        if (curr->neighbor == v) return true;
        curr = curr->next;
    }
    return false;
}

// Add undirected edge to both u and v adjacency lists
static void add_undirected_edge(AdjList *adj, int u, int v, int64_t weight) {
    // Add v to u's list
    Node *n1 = (Node*)malloc(sizeof(Node));
    n1->neighbor = v;
    n1->weight = weight;
    n1->next = adj[u].head;
    adj[u].head = n1;
    adj[u].degree++;

    // Add u to v's list
    Node *n2 = (Node*)malloc(sizeof(Node));
    n2->neighbor = u;
    n2->weight = weight;
    n2->next = adj[v].head;
    adj[v].head = n2;
    adj[v].degree++;
}

void generate_mst_testcase(const char *filename, int V, int E) {
    if (E < V - 1) {
        fprintf(stderr, "Error: Edge count E must be at least V - 1 to build a connected graph.\n");
        return;
    }

    AdjList *adj = (AdjList*)calloc(V, sizeof(AdjList));

    // Step 1: Ensure connectivity with a random spanning tree (V - 1 edges)
    for (int i = 1; i < V; i++) {
        int parent = rand() % i;
        int64_t weight = (rand() % 200) - 50; // Random edge weight [-50, 149]
        add_undirected_edge(adj, i, parent, weight);
    }

    // Step 2: Add remaining unique edges
    int current_edges = V - 1;
    while (current_edges < E) {
        int u = rand() % V;
        int v = rand() % V;

        if (u != v && !edge_exists(adj, u, v)) {
            int64_t weight = (rand() % 200) - 50;
            add_undirected_edge(adj, u, v, weight);
            current_edges++;
        }
    }

    // Step 3: Write to file using specified adjacency-list format[cite: 3, 4]
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        perror("File opening failed");
        free(adj);
        return;
    }

    fprintf(fp, "%d %d\n", V, E);

    for (int u = 0; u < V; u++) {
        fprintf(fp, "%d %d", u, adj[u].degree);
        Node *curr = adj[u].head;
        while (curr) {
            fprintf(fp, " %d %" PRId64, curr->neighbor, curr->weight);
            curr = curr->next;
        }
        fprintf(fp, "\n");
    }

    fclose(fp);

    // Free memory
    for (int i = 0; i < V; i++) {
        Node *curr = adj[i].head;
        while (curr) {
            Node *tmp = curr;
            curr = curr->next;
            free(tmp);
        }
    }
    free(adj);

    printf("Successfully generated %s (V = %d, E = %d)\n", filename, V, E);
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(NULL));

    if (argc == 4) {
        const char *outfile = argv[1];
        int V = atoi(argv[2]);
        int E = atoi(argv[3]);
        generate_mst_testcase(outfile, V, E);
    } else {
        printf("Generating standard MST benchmark datasets...\n");
        generate_mst_testcase("mst_10.txt", 10, 24);            // V=10[cite: 3, 4]
        generate_mst_testcase("mst_100.txt", 100, 280);         // V=100[cite: 3, 4]
        generate_mst_testcase("mst_10000.txt", 10000, 30000);   // V=10,000[cite: 3, 4]
        generate_mst_testcase("mst_50000.txt", 50000, 150000);  // V=50,000[cite: 3, 4]
        generate_mst_testcase("mst_100000.txt", 100000, 300000);// V=100,000[cite: 3, 4]
    }

    return 0;
}