ifeq ($(CC), cc)
  CC=clang
endif

default: 
	$(CC) -o oneline -std=c11 -Wall -Wextra oneline.c

debug:
	$(CC) -o oneline -g -O0 -std=c11 -Wall -Wextra oneline.c

win32:
	$(CC) -o oneline.exe -std=c11 -Wall -Wextra oneline.c

.PHONY: clean
clean:
	-rm *.o oneline
