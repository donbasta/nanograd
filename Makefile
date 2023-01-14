CC = g++
CFLAGS = -g -Wall
SOURCE_DIR = src
OBJECT_DIR = obj
BINARY_DIR = bin
TEST_DIR = src/tests
TEST_OBJ_DIR = src/tests/obj
TEST_BIN_DIR = src/tests/bin
UTILS_DIR = src/utils

LAYERS_DIR = src/layers

build-run: build run

build: main

run:
	$(BINARY_DIR)/main

main: utils Value.o Neuron.o Layer.o MLP.o main.o
	$(CC) $(CFLAGS) -o $(BINARY_DIR)/main $(OBJECT_DIR)/main.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o $(OBJECT_DIR)/double_utils.o $(OBJECT_DIR)/gen_data.o

main.o: 
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/main.cpp -o $(OBJECT_DIR)/main.o

Value.o: $(SOURCE_DIR)/Value.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/Value.cpp -o $(OBJECT_DIR)/Value.o

Neuron.o: $(LAYERS_DIR)/Neuron.h $(SOURCE_DIR)/Value.h
	$(CC) $(CFLAGS) -c $(LAYERS_DIR)/Neuron.cpp -o $(OBJECT_DIR)/Neuron.o

Layer.o: $(LAYERS_DIR)/Layer.h $(LAYERS_DIR)/Neuron.h
	$(CC) $(CFLAGS) -c $(LAYERS_DIR)/Layer.cpp -o $(OBJECT_DIR)/Layer.o

MLP.o: $(LAYERS_DIR)/MLP.h $(LAYERS_DIR)/Layer.h
	$(CC) $(CFLAGS) -c $(LAYERS_DIR)/MLP.cpp -o $(OBJECT_DIR)/MLP.o

.PHONY: test clean
clean:
	rm $(BINARY_DIR)/*.o

# tests

test: build-test run-test

build-test: utils Value.o Neuron.o Layer.o MLP.o test_neuron.o test_value.o test_layer.o all_test.o all-test 

utils: $(UTILS_DIR)/double_utils.h $(UTILS_DIR)/gen_data.h
	$(CC) $(CFLAGS) -c $(UTILS_DIR)/double_utils.cpp -o $(OBJECT_DIR)/double_utils.o
	$(CC) $(CFLAGS) -c $(UTILS_DIR)/gen_data.cpp -o $(OBJECT_DIR)/gen_data.o

test_neuron.o: $(TEST_DIR)/test_neuron.h $(LAYERS_DIR)/Neuron.h $(SOURCE_DIR)/Value.h $(UTILS_DIR)/double_utils.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_neuron.cpp -o $(TEST_OBJ_DIR)/test_neuron.o

test_value.o: $(TEST_DIR)/test_value.h $(SOURCE_DIR)/Value.h $(UTILS_DIR)/double_utils.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_value.cpp -o $(TEST_OBJ_DIR)/test_value.o

test_layer.o: $(TEST_DIR)/test_layer.h $(LAYERS_DIR)/Layer.h $(SOURCE_DIR)/Value.h $(UTILS_DIR)/double_utils.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/test_layer.cpp -o $(TEST_OBJ_DIR)/test_layer.o

all_test.o: $(TEST_DIR)/test_neuron.h $(TEST_DIR)/test_value.h
	$(CC) $(CFLAGS) -c $(TEST_DIR)/all_test.cpp -o $(TEST_OBJ_DIR)/all_test.o

all-test: $(TEST_DIR)/test_neuron.h $(TEST_DIR)/test_value.h
	$(CC) $(CFLAGS) -o $(TEST_BIN_DIR)/test $(TEST_OBJ_DIR)/all_test.o $(TEST_OBJ_DIR)/test_value.o $(TEST_OBJ_DIR)/test_neuron.o $(TEST_OBJ_DIR)/test_layer.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o $(OBJECT_DIR)/double_utils.o $(OBJECT_DIR)/gen_data.o

run-test: 
	$(TEST_BIN_DIR)/test
