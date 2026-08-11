CC = gcc
CFLAGS = -O3 -Wall

# Executables
TARGET_MASTER = master_wrapper.exe
TARGET_A1 = a1_solver.exe
TARGET_A2 = a2_solver.exe

# Sources & Includes
A1_INCLUDES = -Iassignment_01/CSR_Graph/include -Iassignment_01/Matrix_Multiplication/include
A1_SRCS = assignment_01/driver/main.c \
          assignment_01/driver/csr_driver.c \
          assignment_01/driver/gemm_driver.c \
          assignment_01/CSR_Graph/src/csr.c \
          assignment_01/Matrix_Multiplication/src/gemm_blocking.c \
          assignment_01/Matrix_Multiplication/src/gemm_simple.c

A2_INCLUDES = -Iassignment_02/include
A2_SRCS = $(wildcard assignment_02/src/*.c)

# Default rule: build everything
all: $(TARGET_MASTER) $(TARGET_A1) $(TARGET_A2)

$(TARGET_MASTER): master_wrapper.c
	$(CC) $(CFLAGS) master_wrapper.c -o $(TARGET_MASTER)

$(TARGET_A1): $(A1_SRCS)
	$(CC) $(CFLAGS) $(A1_INCLUDES) $(A1_SRCS) -o $(TARGET_A1)

$(TARGET_A2): $(A2_SRCS)
	$(CC) $(CFLAGS) $(A2_INCLUDES) $(A2_SRCS) -o $(TARGET_A2)

clean:
	rm -f $(TARGET_MASTER) $(TARGET_A1) $(TARGET_A2) *.o