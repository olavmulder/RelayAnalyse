CC = g++
PROJECT = RelayAnalyse

LIBS = `pkg-config --cflags --libs opencv4` 
FLAGS = -Wall -Wextra -g
SRC_LIST = $(wildcard src/*)

.PHONY: all test clear
all: $(PROJECT)

$(PROJECT): 
	$(CC) -o main main.cpp $(SRC_LIST) $(LIBS) $(FLAGS)
test:
	$(CC) -o test test.cpp $(SRC_LIST) $(LIBS) $(FLAGS)
clear:
	rm main test