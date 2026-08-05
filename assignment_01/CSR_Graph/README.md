Set-Location "..\CSR Graph"

# 1. Compile the CSR runner
gcc -Wall -Wextra -O2 -Iinclude src/main.c src/csr.c -o csr_runner.exe

# 2. Compile and run the graph test file generator
gcc -O2 generate_csr_tests.c -o gen_csr.exe
.\gen_csr.exe
Remove-Item gen_csr.exe

# 3. Run test cases
.\csr_runner.exe data/csr_10.txt
.\csr_runner.exe data/csr_100.txt