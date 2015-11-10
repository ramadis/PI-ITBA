COMPILER=gcc
OUTPUT_FILE=2048
FILES=2048Front.c 2048Back.h 2048Back.c
FLAGS=--pedantic -Wall
all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES) $(FLAGS)
clean:
	rm $(OUTPUT_FILE)
