CC = g++
CFLAGS = -g -Wall
SOURCE_DIR = src
OBJECT_DIR = obj
BINARY_DIR = bin

build-run: build run

build: main

run:
	$(BINARY_DIR)/main

main: Value.o Neuron.o main.o
	$(CC) $(CFLAGS) -o $(BINARY_DIR)/main $(OBJECT_DIR)/main.o $(OBJECT_DIR)/Value.o $(OBJECT_DIR)/Neuron.o

main.o: 
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/main.cpp -o $(OBJECT_DIR)/main.o

Value.o: $(SOURCE_DIR)/Value.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/Value.cpp -o $(OBJECT_DIR)/Value.o

Neuron.o: $(SOURCE_DIR)/Neuron.h $(SOURCE_DIR)/Value.h
	$(CC) $(CFLAGS) -c $(SOURCE_DIR)/Neuron.cpp -o $(OBJECT_DIR)/Neuron.o
