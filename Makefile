ifeq ($(CC), cc)
  CC=clang
endif

default: 
	$(CC) -o oneline -std=c11 -Wall -Wextra oneline.c

debug:
	$(CC) -o oneline_debug -g -O0 -std=c11 -Wall -Wextra oneline.c

win32:
	i586-mingw32msvc-gcc -o oneline.exe -static-libgcc -std=c99 -Wall -Wextra oneline.c

.PHONY: clean
clean:
	-rm *.o oneline oneline_debug oneline.exe
