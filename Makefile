CC = g++
CFLAGS = --std=c++17 -Wall -Werror -pedantic
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework
DEPS = Checkers.hpp
PROGRAM = checkers
OBJECTS = Checkers.o main.o

.PHONY: all clean

all: $(PROGRAM)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -c $<

$(PROGRAM): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

Checkers.o: Checkers.cpp
	$(CC) $(CFLAGS) -c Checkers.cpp

Checkers:Checkers.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

main: main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	rm *.o $(PROGRAM)

lint:
	cpplint *.cpp *.hpp