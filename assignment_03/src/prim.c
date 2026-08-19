#define __USE_MINGW_ANSI_STDIO 1

#include "../include/csr_graph.h"
#include "../include/mst.h"
#include <time.h>
#include <limits.h>

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
    int v;
    long long key;
} HeapNode;

typedef struct {
    HeapNode *array;
    int *pos;
    int capacity;
    int size;
} MinHeap;

static MinHeap* create_min_heap(int capacity) {
    MinHeap *heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->array = (HeapNode*)malloc(capacity * sizeof(HeapNode));
    heap->pos = (int*)malloc(capacity * sizeof(int));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

static void min_heapify(MinHeap *heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < heap->size && heap->array[left].key < heap->array[smallest].key)
        smallest = left;
    if (right < heap->size && heap->array[right].key < heap->array[smallest].key)
        smallest = right;

    if (smallest != idx) {
        heap->pos[heap->array[smallest].v] = idx;
        heap->pos[heap->array[idx].v] = smallest;
        
        HeapNode temp = heap->array[smallest];
        heap->array[smallest] = heap->array[idx];
        heap->array[idx] = temp;

        min_heapify(heap, smallest);
    }
}

static HeapNode extract_min(MinHeap *heap) {
    HeapNode root = heap->array[0];
    HeapNode last_node = heap->array[heap->size - 1];
    heap->array[0] = last_node;

    heap->pos[root.v] = -1;
    heap->pos[last_node.v] = 0;

    heap->size--;
    min_heapify(heap, 0);
    return root;
}

static void decrease_key(MinHeap *heap, int v, long long key) {
    int i = heap->pos[v];
    heap->array[i].key = key;

    while (i && heap->array[i].key < heap->array[(i - 1) / 2].key) {
        heap->pos[heap->array[i].v] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2].v] = i;

        HeapNode temp = heap->array[i];
        heap->array[i] = heap->array[(i - 1) / 2];
        heap->array[(i - 1) / 2] = temp;

        i = (i - 1) / 2;
    }
}

MSTResult run_prim_mst(const CSRGraph *csr) {
    MSTResult result;
    result.edges = (MSTEdge*)malloc((csr->V - 1) * sizeof(MSTEdge));
    result.edge_count = 0;
    result.total_weight = 0;

    double start_time = get_time_ms();

    int V = csr->V;
    int *parent = (int*)malloc(V * sizeof(int));
    long long *key = (long long*)malloc(V * sizeof(long long));
    bool *in_mst = (bool*)calloc(V, sizeof(bool));

    MinHeap *heap = create_min_heap(V);

    for (int v = 0; v < V; v++) {
        parent[v] = -1;
        key[v] = LLONG_MAX;
        heap->array[v].v = v;
        heap->array[v].key = key[v];
        heap->pos[v] = v;
    }

    key[0] = 0;
    heap->array[0].key = 0;
    heap->size = V;

    while (heap->size > 0) {
        HeapNode min_node = extract_min(heap);
        int u = min_node.v;
        in_mst[u] = true;

        if (parent[u] != -1) {
            result.edges[result.edge_count].u = parent[u];
            result.edges[result.edge_count].v = u;
            result.edges[result.edge_count].weight = min_node.key;
            result.edge_count++;
            result.total_weight += min_node.key;
        }

        for (int j = csr->row_ptr[u]; j < csr->row_ptr[u + 1]; j++) {
            int v = csr->col_idx[j];
            long long weight = csr->values[j];

            if (heap->pos[v] != -1 && !in_mst[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                decrease_key(heap, v, weight);
            }
        }
    }

    double end_time = get_time_ms();
    result.execution_time_ms = end_time - start_time;

    free(parent);
    free(key);
    free(in_mst);
    free(heap->array);
    free(heap->pos);
    free(heap);

    return result;
}

void free_mst_result(MSTResult *res) {
    if (res->edges) free(res->edges);
}