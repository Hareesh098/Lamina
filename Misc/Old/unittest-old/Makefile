CC      = gcc -O3 -g -Wall -Wextra
INCLUDE = -I/usr/include/mpich-3.2-x86_64/
LIBS    = -lm

# Source files for the unit test
UNIT_TEST_SOURCES = TestComputeBondForce.c ../source/ComputeBondForce.c
UNIT_TEST_OBJECTS = TestComputeBondForce.o ComputeBondForce.o

# Output executable for the test
UNIT_TEST_EXEC = TestComputeBondForce

# Compilation rule for the unit test
$(UNIT_TEST_EXEC): $(UNIT_TEST_OBJECTS)
	$(CC) -o $(UNIT_TEST_EXEC) $(UNIT_TEST_OBJECTS) $(LIBS) $(INCLUDE)

# Compile source files into object files
TestComputeBondForce.o: TestComputeBondForce.c
	$(CC) -c TestComputeBondForce.c -o TestComputeBondForce.o $(INCLUDE)

ComputeBondForce.o: ../source-v10/ComputeBondForce.c
	$(CC) -c ../source-v10/ComputeBondForce.c -o ComputeBondForce.o $(INCLUDE)

# Run the test
test: $(UNIT_TEST_EXEC)
	./$(UNIT_TEST_EXEC)

# Cleanup
.PHONY: clean
clean:
	rm -rf $(UNIT_TEST_EXEC) $(UNIT_TEST_OBJECTS)

