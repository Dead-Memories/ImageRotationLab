CFLAGS=--std=c18 -Wall -pedantic -Isrc/ -ggdb -Wextra -Werror -DDEBUG
CC=gcc

all: image_rotate

bmp_io.o: image/bmp/bmp_io.c
	$(CC) -c $(CFLAGS) $< -o $@

bmp_header.o: image/bmp/bmp_header.c
	$(CC) -c $(CFLAGS) $< -o $@

rotate.o: image/image_operations/rotate.c
	$(CC) -c $(CFLAGS) $< -o $@

file.o: file_operations/file.c
	$(CC) -c $(CFLAGS) $< -o $@

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o $@

image_rotate: main.o bmp_header.o bmp_io.o rotate.o file.o
	$(CC) -o image_rotate $^

clean:
	rm -f main.o bmp_header.o bmp_io.o rotate.o file.o image_rotate
