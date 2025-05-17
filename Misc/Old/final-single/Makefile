# Compiler and flags
CC = gcc
CFLAGS = -Wall -I../source
LDFLAGS = -lm

# Sources for the test binary
SRC = main.c \
      ../source/ComputeBondForce.c

# Output binary
OUT = test

# Default rule: just build
all: $(OUT)

# Build rule
$(OUT): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

# Run tests (after building)
run: $(OUT)
	./$(OUT)

# Clean up build output
clean:
	rm -f $(OUT)

