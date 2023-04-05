CC := clang
CFLAGS := -g -Wall -std=c11 -pedantic -Wextra -O0 -fsanitize=address
CREATEDIR := $(shell mkdir -p obj)

.PHONY: all
all: tail wordcount #wordcount-dynamic
# a knihovny "libhtab.a", "libhtab.so

tail: obj/tail.o
	$(CC) $(CFLAGS) -lm $^ -o $@

wordcount: obj/io.o obj/htab.o obj/wordcount.o
	$(CC) $(CFLAGS) -lm $^ -o $@


#wordcount-dynamic: obj/wordcount.o obj/htab.o
#	$(CC) $(CFLAGS) -lm $^ -o $@

obj/wordcount.o: wordcount.c io.h htab.h
obj/io.o: io.c
obj/htab.o: htab.c htab.h
obj/tail.o: tail.c

obj/%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@


.PHONY: clean
clean:
	-rm -r ./obj/ tail wordcount
