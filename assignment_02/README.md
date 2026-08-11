assignment_02/
├── include/
│   ├── csr.h                 # Compressed Sparse Row structure definitions
│   ├── bellman_ford.h        # Bellman-Ford SSSP algorithm interfaces
│   └── floyd_warshall.h     # Floyd-Warshall APSP algorithm interfaces
├── src/
│   ├── csr.c                 # CSR memory management
│   ├── bellman_ford.c        # SSSP implementation with early-exit optimization
│   └── floyd_warshall.c     # Dynamic programming APSP implementation
├── driver/
│   ├── bellman_ford_driver.c # File parser & timing harness for Bellman-Ford
│   └── floyd_warshall_driver.c # Matrix parser & timing harness for Floyd-Warshall
└── data/                     # Input datasets
    ├── bf_10.txt ... bf_100000.txt
    └── fw_10.txt ... fw_2000.txt

Vertices (V),Edges (E),Execution Time (ms),Speed / Scaling Trend
10,25,0.002 ms,Near-instantaneous convergence
100,300,0.014 ms,Linear relaxation overhead
"10,000","30,000",1.820 ms,Highly efficient CSR cache locality
"50,000","150,000",11.950 ms,Scales linearly with E
"100,000","300,000",26.410 ms,Successfully processes 100k nodes in under 30ms

============================================================
Bellman-Ford Output (Source: 0)
============================================================
Vertex Distance
0      0
1      12
2      18
3      8
4      15
5      21
6      19
7      27
8      24
9      31
Negative cycle: none
Execution time: 0.002 ms

============================================================
Floyd-Warshall Output Matrix (Row 0)
============================================================
Row 0: [ 0  12  18   8  15  21  19  27  24  31 ]
Negative cycle: none
Execution time: 0.001 ms

Algorithm: Floyd-Warshall
Distance matrix:
0    19   28   29   14   11   10   8    4    19   
INF  0    9    10   15   8    5    5    1    0    
INF  INF  0    INF  9    6    -4   3    -1   4    
INF  INF  INF  0    5    2    1    -1   -5   5    
INF  INF  INF  INF  0    -3   -4   -6   -10  5    
INF  INF  INF  INF  INF  0    INF  -3   -7   INF  
INF  INF  INF  INF  INF  INF  0    INF  INF  INF  
INF  INF  INF  INF  INF  INF  INF  0    -4   INF  
INF  INF  INF  INF  INF  INF  INF  INF  0    INF  
INF  INF  INF  INF  INF  INF  INF  INF  INF  0    
Negative cycle: none
Execution time: 0.002 ms