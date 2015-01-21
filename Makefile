CC=clang

default: 
	$(CC) -o oneline -std=c11 -Wall -Wextra oneline.c

.PHONY: clean
clean:
	-rm *.o oneline
