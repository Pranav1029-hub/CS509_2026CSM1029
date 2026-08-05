CC = gcc
CFLAGS = -Wall -Wextra -O2 -I. -IMatrix_Multiplication/include -ICSR_Graph/include

# Source files
SRCS = common_wrapper/main_wrapper.c \
       driver/gemm_driver.c \
       driver/csr_driver.c \
       Matrix_Multiplication/src/gemm_simple.c \
       Matrix_Multiplication/src/gemm_blocking.c \
       CSR_Graph/src/csr.c

OBJS = $(SRCS:.c=.o)
TARGET = assignment_runner

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET) *.exe

.PHONY: all clean