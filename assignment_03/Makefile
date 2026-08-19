CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude -std=c11
SRC = src/csr.c src/kruskal.c src/prim.c driver/main.c
OBJ = $(SRC:.c=.o)
TARGET = mst_driver

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean