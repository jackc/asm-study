P=avg
OBJECTS=main.o avg.o avg_simd.o
CFLAGS = -g -Wall -Werror -O3 -I.
LDLIBS=
CC=gcc

$(P): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@ $(LDFLAGS) $(LDLIBS)
