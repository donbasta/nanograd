CXX = g++
CXXFLAGS = -g -Wall
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
	echo "hello world"

main:
	echo "hello world"

# Build binaries of various programs

playground: utils Value.o Neuron.o Layer.o MLP.o playground.o
	mkdir -p $(BINARY_DIR)
	$(CXX) $(CXXFLAGS) -o $(BINARY_DIR)/playground $(OBJECT_DIR)/playground.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o $(OBJECT_DIR)/double_utils.o $(OBJECT_DIR)/gen_data.o
	$(BINARY_DIR)/playground

playground.o: 
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/bins/playground.cpp -o $(OBJECT_DIR)/playground.o

linear-regression: utils losses Value.o Neuron.o Layer.o MLP.o linear-regression.o
	mkdir -p $(BINARY_DIR)
	$(CXX) $(CXXFLAGS) -o $(BINARY_DIR)/linear-regression $(OBJECT_DIR)/linear-regression.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o $(OBJECT_DIR)/double_utils.o $(OBJECT_DIR)/gen_data.o $(OBJECT_DIR)/mean_squared_error.o
	$(BINARY_DIR)/linear-regression

linear-regression.o:
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/bins/linear-regression.cpp -o $(OBJECT_DIR)/linear-regression.o

# Libraries and Classes

Value.o: $(SOURCE_DIR)/engines/Value.h
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/engines/Value.cpp -o $(OBJECT_DIR)/Value.o

Neuron.o: $(LAYERS_DIR)/Neuron.h $(SOURCE_DIR)/engines/Value.h
	$(CXX) $(CXXFLAGS) -c $(LAYERS_DIR)/Neuron.cpp -o $(OBJECT_DIR)/Neuron.o

Layer.o: $(LAYERS_DIR)/Layer.h $(LAYERS_DIR)/Neuron.h
	$(CXX) $(CXXFLAGS) -c $(LAYERS_DIR)/Layer.cpp -o $(OBJECT_DIR)/Layer.o

MLP.o: $(LAYERS_DIR)/MLP.h $(LAYERS_DIR)/Layer.h
	$(CXX) $(CXXFLAGS) -c $(LAYERS_DIR)/MLP.cpp -o $(OBJECT_DIR)/MLP.o

utils: $(UTILS_DIR)/double_utils.h $(UTILS_DIR)/gen_data.h
	$(CXX) $(CXXFLAGS) -c $(UTILS_DIR)/double_utils.cpp -o $(OBJECT_DIR)/double_utils.o
	$(CXX) $(CXXFLAGS) -c $(UTILS_DIR)/gen_data.cpp -o $(OBJECT_DIR)/gen_data.o

losses: $(SOURCE_DIR)/losses/losses.h
	$(CXX) $(CXXFLAGS) -c $(SOURCE_DIR)/losses/mean_squared_error.cpp -o $(OBJECT_DIR)/mean_squared_error.o

# Tests

.PHONY: test clean

test: build-test run-test

build-test: utils Value.o Neuron.o Layer.o MLP.o test_neuron.o test_value.o test_layer.o all_test.o all-test 

test_neuron.o: $(TEST_DIR)/test_neuron.h $(LAYERS_DIR)/Neuron.h $(SOURCE_DIR)/engines/Value.h $(UTILS_DIR)/double_utils.h
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/test_neuron.cpp -o $(TEST_OBJ_DIR)/test_neuron.o

test_value.o: $(TEST_DIR)/test_value.h $(SOURCE_DIR)/engines/Value.h $(UTILS_DIR)/double_utils.h
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/test_value.cpp -o $(TEST_OBJ_DIR)/test_value.o

test_layer.o: $(TEST_DIR)/test_layer.h $(LAYERS_DIR)/Layer.h $(SOURCE_DIR)/engines/Value.h $(UTILS_DIR)/double_utils.h
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/test_layer.cpp -o $(TEST_OBJ_DIR)/test_layer.o

all_test.o: $(TEST_DIR)/test_neuron.h $(TEST_DIR)/test_value.h
	$(CXX) $(CXXFLAGS) -c $(TEST_DIR)/all_test.cpp -o $(TEST_OBJ_DIR)/all_test.o

all-test: $(TEST_DIR)/test_neuron.h $(TEST_DIR)/test_value.h
	$(CXX) $(CXXFLAGS) -o $(TEST_BIN_DIR)/test $(TEST_OBJ_DIR)/all_test.o $(TEST_OBJ_DIR)/test_value.o $(TEST_OBJ_DIR)/test_neuron.o $(TEST_OBJ_DIR)/test_layer.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o $(OBJECT_DIR)/Layer.o $(OBJECT_DIR)/MLP.o $(OBJECT_DIR)/double_utils.o $(OBJECT_DIR)/gen_data.o

run-test: 
	$(TEST_BIN_DIR)/test

# Clean 

clean:
	rm -r $(BINARY_DIR)