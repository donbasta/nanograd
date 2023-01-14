CC = g++
CFLAGS = -g -Wall
SOURCE_DIR = src
OBJECT_DIR = obj
BINARY_DIR = bin
TEST_DIR = src/tests
TEST_OBJ_DIR = src/tests/obj
TEST_BIN_DIR = src/tests/bin
UTILS_DIR = src/utils

build-run: build run

build: main

run:
	$(BINARY_DIR)/main

main: Value.o Neuron.o Layer.o MLP.o main.o
	$(CC) $(CFLAGS) -o $(BINARY_DIR)/main $(OBJECT_DIR)/main.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o

main.o: 
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/main.cpp -o $(OBJECT_DIR)/main.o

Value.o: $(SOURCE_DIR)/Value.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/Value.cpp -o $(OBJECT_DIR)/Value.o

Neuron.o: $(SOURCE_DIR)/Neuron.h $(SOURCE_DIR)/Value.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/Neuron.cpp -o $(OBJECT_DIR)/Neuron.o

Layer.o: $(SOURCE_DIR)/Layer.h $(SOURCE_DIR)/Neuron.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/Layer.cpp -o $(OBJECT_DIR)/Layer.o

MLP.o: $(SOURCE_DIR)/MLP.h $(SOURCE_DIR)/Layer.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/MLP.cpp -o $(OBJECT_DIR)/MLP.o

.PHONY: test clean
clean:
	rm $(BINARY_DIR)/*.o

# tests

test: build-test run-test

build-test: utils Value.o Neuron.o Layer.o MLP.o test_neuron.o test_value.o all_test.o all-test 
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/MLP.cpp -o $(OBJECT_DIR)/MLP.o

utils: $(UTILS_DIR)/double_utils.h
	$(CC) $(CFLAGS) -c $(UTILS_DIR)/double_utils.cpp -o $(TEST_OBJ_DIR)/double_utils.o

test_neuron.o: $(TEST_DIR)/test_neuron.h $(SOURCE_DIR)/Neuron.h $(SOURCE_DIR)/Value.h $(UTILS_DIR)/double_utils.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_neuron.cpp -o $(TEST_OBJ_DIR)/test_neuron.o

test_value.o: $(TEST_DIR)/test_value.h $(SOURCE_DIR)/Value.h $(UTILS_DIR)/double_utils.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_value.cpp -o $(TEST_OBJ_DIR)/test_value.o

all_test.o: $(TEST_DIR)/test_neuron.h $(TEST_DIR)/test_value.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/all_test.cpp -o $(TEST_OBJ_DIR)/all_test.o

all-test: $(TEST_DIR)/test_neuron.h $(TEST_DIR)/test_value.h
	$(CC) $(CFLAGS) -o $(TEST_BIN_DIR)/test $(TEST_OBJ_DIR)/all_test.o $(TEST_OBJ_DIR)/test_value.o $(TEST_OBJ_DIR)/test_neuron.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o $(TEST_OBJ_DIR)/double_utils.o

run-test: 
	$(TEST_BIN_DIR)/test
