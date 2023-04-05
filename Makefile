CC := clang
CFLAGS := -g -Wall -std=c11 -pedantic -DSTATISTICS -Wextra -O0 -fsanitize=address
CREATEDIR := $(shell mkdir -p obj)

.PHONY: all
all: tail wordcount #wordcount-dynamic
# a knihovny "libhtab.a", "libhtab.so

cpp: src/to_je_jedno.cpp
	clang++ -O3 $^ -o $@

tail: obj/tail.o
	$(CC) $(CFLAGS) -lm $^ -o $@

wordcount: obj/io.o obj/htab.o obj/wordcount.o
	$(CC) $(CFLAGS) -lm $^ -o $@


#wordcount-dynamic: obj/wordcount.o obj/htab.o
#	$(CC) $(CFLAGS) -lm $^ -o $@

obj/wordcount.o: src/wordcount.c src/io.h src/htab.h
obj/io.o: src/io.c
obj/htab.o: src/htab.c src/htab.h
obj/tail.o: src/tail.c

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -o $@


.PHONY: clean
clean:
	-rm -r ./obj/ tail wordcount cpp
