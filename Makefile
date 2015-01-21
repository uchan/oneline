ifeq ($(CC), cc)
  CC=clang
endif

default: 
	$(CC) -o oneline -std=c11 -Wall -Wextra oneline.c

.PHONY: clean
clean:
	-rm *.o oneline
