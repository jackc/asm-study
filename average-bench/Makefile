P=avg
OBJECTS=main.o avg.o avg_simd.o
CFLAGS = -g -Wall -Werror -O3 -I.
LDLIBS=
CC=gcc

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)

avg_simd.o: avg_simd.asm
	nasm -f elf64 avg_simd.asm
