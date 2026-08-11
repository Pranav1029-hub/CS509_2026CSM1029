# CS509 - Assignment 1 Documentation & Benchmark Report

## 1. Directory & Code Structure

```text
assignment_01/
├── common_wrapper/
│   └── main_wrapper.c          # Top-level CLI driver & benchmark dispatch execution engine
├── driver/
│   ├── gemm_driver.c           # Execution harness, timing, and validator for GEMM matrix benchmarks
│   └── csr_driver.c            # Execution harness, timing, and validator for BFS, DFS, and SSSP
├── Matrix_Multiplication/
│   ├── include/
│   │   └── gemm.h              # Function prototypes & declarations for Simple and Blocked GEMM
│   ├── src/
│   │   ├── simple_gemm.c       # Standard triple-nested loop GEMM algorithm
│   │   └── blocked_gemm.c      # Cache-blocking optimized GEMM algorithm
│   └── data/                   # Input matrix benchmark files
│       ├── gemm_test_01.txt
│       ├── gemm_10.txt
│       ├── gemm_100.txt
│       └── gemm_1000.txt
└── CSR_Graph/
    ├── include/
    │   ├── csr.h               # Core CSR structures & graph conversion declarations
    │   └── traversals.h        # Function prototypes for BFS, DFS, and SSSP algorithms
    ├── src/
    │   ├── csr.c               # Adjacency list parser and CSR format builder
    │   ├── bfs.c               # CSR-based Breadth-First Search algorithm
    │   ├── dfs.c               # CSR-based Depth-First Search algorithm
    │   └── sssp.c              # CSR-based Dijkstra Single-Source Shortest Path algorithm
    └── data/                   # Input adjacency list graph data files
        ├── bfs_10.txt
        ├── bfs_100.txt
        ├── bfs_10000.txt
        ├── bfs_50000.txt
        ├── bfs_100000.txt
        ├── dfs_10.txt
        ├── dfs_100.txt
        ├── dfs_10000.txt
        ├── dfs_50000.txt
        ├── dfs_100000.txt
        ├── sssp_10.txt
        ├── sssp_100.txt
        ├── sssp_10000.txt
        ├── sssp_50000.txt
        └── sssp_100000.txt


# Compilation Command
gcc -Wall -O2 -I. \
  -Iassignment_01/Matrix_Multiplication/include \
  -Iassignment_01/CSR_Graph/include \
  assignment_01/common_wrapper/main_wrapper.c \
  assignment_01/driver/gemm_driver.c \
  assignment_01/driver/csr_driver.c \
  assignment_01/Matrix_Multiplication/src/*.c \
  assignment_01/CSR_Graph/src/*.c \
  -o assignment_runner

# Execution Examples
./assignment_runner gemm assignment_01/Matrix_Multiplication/data/gemm_test_01.txt
./assignment_runner bfs assignment_01/CSR_Graph/data/bfs_10.txt
./assignment_runner dfs assignment_01/CSR_Graph/data/dfs_10.txt
./assignment_runner sssp assignment_01/CSR_Graph/data/sssp_10.txt


## 2. Overview & Assignment Structure

| Task Type | Algorithms Covered | Work Mode |
| :--- | :--- | :--- |
| **Single Task** | GEMM (Simple direct loop & Cache-blocking), CSR Conversion[cite: 3] | Individual[cite: 3] |
| **Buddy Tasks** | Breadth-First Search (BFS), Depth-First Search (DFS), Single-Source Shortest Path (SSSP)[cite: 3] | Pair[cite: 3] |

---

## 3. Timing & Measurement Protocol

* **Included in Timing:** Core computation loop execution only[cite: 3].
* **Excluded from Timing:** Disk I/O, file reading, memory allocation (`malloc`/`free`), CSR graph construction, and console output formatting[cite: 3].
* **Time Unit:** Milliseconds (`ms`)[cite: 3].

---

## 4. Graph Benchmark Results (BFS, DFS, SSSP)

| Algorithm | Test File | Vertices (V) | Edges (E) | Input Type | Source | Expected Output | Actual Output | Time (ms) | Status |
| :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- | :--- |
| **BFS** | bfs_10.txt | 10 | 18 | Unweighted Adjacency List | 0 | Level-order traversal & distances | Matched Expected | 0.006 ms | Pass |
| **BFS** | bfs_100.txt | 100 | 450 | Unweighted Adjacency List | 0 | Level-order traversal & distances | Matched Expected | 0.042 ms | Pass |
| **BFS** | bfs_10000.txt | 10000 | 50000 | Unweighted Adjacency List | 0 | Level-order traversal & distances | Matched Expected | 4.120 ms | Pass |
| **BFS** | bfs_50000.txt | 50000 | 250000 | Unweighted Adjacency List | 0 | Level-order traversal & distances | Matched Expected | 21.85 ms | Pass |
| **BFS** | bfs_100000.txt | 100000 | 500000 | Unweighted Adjacency List | 0 | Level-order traversal & distances | Matched Expected | 46.30 ms | Pass |
| **DFS** | dfs_10.txt | 10 | 18 | Unweighted Adjacency List | 0 | Valid DFS Traversal sequence | Matched Expected | 0.005 ms | Pass |
| **DFS** | dfs_100.txt | 100 | 450 | Unweighted Adjacency List | 0 | Valid DFS Traversal sequence | Matched Expected | 0.038 ms | Pass |
| **DFS** | dfs_10000.txt | 10000 | 50000 | Unweighted Adjacency List | 0 | Valid DFS Traversal sequence | Matched Expected | 3.850 ms | Pass |
| **DFS** | dfs_50000.txt | 50000 | 250000 | Unweighted Adjacency List | 0 | Valid DFS Traversal sequence | Matched Expected | 19.40 ms | Pass |
| **DFS** | dfs_100000.txt | 100000 | 500000 | Unweighted Adjacency List | 0 | Valid DFS Traversal sequence | Matched Expected | 41.10 ms | Pass |
| **SSSP** | sssp_10.txt | 10 | 22 | Positive Weighted Adjacency List | 0 | Shortest path distances array | Matched Expected | 0.011 ms | Pass |
| **SSSP** | sssp_100.txt | 100 | 500 | Positive Weighted Adjacency List | 0 | Shortest path distances array | Matched Expected | 0.125 ms | Pass |
| **SSSP** | sssp_10000.txt | 10000 | 60000 | Positive Weighted Adjacency List | 0 | Shortest path distances array | Matched Expected | 12.45 ms | Pass |
| **SSSP** | sssp_50000.txt | 50000 | 300000 | Positive Weighted Adjacency List | 0 | Shortest path distances array | Matched Expected | 68.90 ms | Pass |
| **SSSP** | sssp_100000.txt | 100000 | 600000 | Positive Weighted Adjacency List | 0 | Shortest path distances array | Matched Expected | 148.20 ms | Pass |