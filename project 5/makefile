# All the targets
all: lcs

# Dependencies and rule to make queue
lcs: main.o
	gcc -o lcs main.o

# Dependencies and rule to make main.o
main.o: main.c
	gcc -c main.c

clean:
	rm lcs main.o
