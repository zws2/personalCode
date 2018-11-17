# All the targets
all: monte

# Dependencies and rule to make queue
monte: main.o
	gcc -o monte main.o -lm

# Dependencies and rule to make main.o
main.o: main.c
	gcc -c main.c

clean:
	rm monte main.o
