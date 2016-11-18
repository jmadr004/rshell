
COMPILE = g++
FLAGS =-Wall  -Werror  -ansi -pedantic

OBJS = ./bin/Userin.o


all: ./src/main.cpp $(OBJS)
	$(COMPILE) $(FLAGS) -g ./src/main.cpp $(OBJS) -o ./bin/rshell

./bin/Userin.o: ./src/Userin.h 
	mkdir -p ./bin
	$(COMPILE) $(FLAGS) -c ./src/Userin -o

clean:
	rm -rf ./bin/
