# Compiler and flags
CC = gcc
CFLAGS = -Wall -I../source
LDFLAGS = -lm

# Source files
SRC = main.c Init.c Close.c TestComputeBondForce.c TestComputePairForce.c assert_double_within.c ../source/ComputeBondForce.c \
      ../source/ComputePairForce.c  	

# Output binary
OUT = test

# Default rule
all: $(OUT)

# Build rule
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Run tests
run: $(OUT)
	./$(OUT)

# Clean
clean:
	rm -f $(OUT)

