CC = g++
CFLAGS = -g -Wall
SOURCE_DIR = src
OBJECT_DIR = obj
BINARY_DIR = bin

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

.PHONY: clean
clean:
	rm $(BINARY_DIR)/*.o
