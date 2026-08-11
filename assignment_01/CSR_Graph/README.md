Set-Location "..\CSR Graph"

# 1. Compile the CSR runner
gcc -Wall -Wextra -O2 -Iinclude src/main.c src/csr.c -o csr_runner.exe

gcc -Wall -O2 -I. -Iassignment_01/Matrix_Multiplication/include -Iassignment_01/CSR_Graph/include assignment_01/common_wrapper/main_wrapper.c assignment_01/driver/gemm_driver.c assignment_01/driver/csr_driver.c assignment_01/Matrix_Multiplication/src/*.c assignment_01/CSR_Graph/src/*.c -o assignment_runner.exe


# 2. Compile and run the graph test file generator
gcc -O2 generate_csr_tests.c -o gen_csr.exe
.\gen_csr.exe
Remove-Item gen_csr.exe

# 3. Run test cases
.\csr_runner.exe data/csr_10.txt
.\csr_runner.exe data/csr_100.txt