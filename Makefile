CC=gcc
CFLAGS=-Iincludes

all:
	$(CC) $(CFLAGS) src/*.c src/server/*.c -o a.out && ./a.out
