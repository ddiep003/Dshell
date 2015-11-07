ErrorFlags = -Wall -Werror -ansi -pedantic
G++ = g++

all: rshell

rshell: src/main.cpp src/rshell.h
	mkdir bin
	$(G++) src/main.cpp $(ErrorFlags) -o bin/rshell  
	
clean:
	rm -rf bin