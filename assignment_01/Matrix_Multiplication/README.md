gcc -Wall -Wextra -O2 -Iinclude src/main.c src/gemm_simple.c src/gemm_blocking.c -o gemm_runner.exe
# Compile generator
gcc -O2 generate_tests.c -o gen_tests.exe

# Run generator
.\gen_tests.exe

# Run 10x10 Matrix Test
.\gemm_runner.exe data/gemm_10.txt

# Run 100x100 Matrix Test
.\gemm_runner.exe data/gemm_100.txt

# Run 1000x1000 Matrix Test
.\gemm_runner.exe data/gemm_1000.txt