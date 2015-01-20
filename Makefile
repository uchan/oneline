default:
	gcc -o oneline -Wall -Wextra oneline.c

.PHONY: clean
clean:
	-rm *.o oneline
