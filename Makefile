CC := clang
CFLAGS := -g -Wall -std=c11 -pedantic -Wextra -O3 -fsanitize=address
CREATEDIR := $(shell mkdir -p obj)

.PHONY: all
all: tail #wordcount wordcount-dynamic
# a knihovny "libhtab.a", "libhtab.so

tail: obj/tail.o
	$(CC) $(CFLAGS) -lm $^ -o $@

#												\
wordcount: obj/wordcount.o obj/htab.o			\
	$(CC) $(CFLAGS) -lm $^ -o $@				\
												\
wordcount-dynamic: obj/wordcount.o obj/htab.o	\
	$(CC) $(CFLAGS) -lm $^ -o $@


obj/tail.o: src/tail.c

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $< -c -o $@


.PHONY: clean
clean:
	-rm -r ./obj/ primes primes-i steg-decode
