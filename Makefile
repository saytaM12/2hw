CC := clang
CFLAGS := -g -Wall -std=c11 -pedantic -DSTATISTICS -Wextra -O2
CREATEDIR := $(shell mkdir -p obj)

DEPENDENCIES:=$(shell $(CC) -MM *.c | sed -r 's/.*:.*/obj\/\0/' > dep.d)

-include dep.d

.PHONY: all
all: tail wordcount wordcount-dynamic
# a knihovny "libhtab.a", "libhtab.so

cpp: to_je_jedno.cpp
	clang++ -O3 $^ -o $@

tail: obj/tail.o
	$(CC) $(CFLAGS) -lm $^ -o $@

wordcount: obj/io.o obj/htab.o obj/wordcount.o libhtab.a
	$(CC) $(CFLAGS) -lm $^ -o $@

wordcount-dynamic: obj/wordcount-dynamic.o obj/htab.o libhtab.so
	$(CC) $(CFLAGS) -lm $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

lib/libhtab.a: obj/htab_bucket_count.o obj/htab_clear.o obj/htab_erase.o obj/htab_find.o obj/htab_for_each.o obj/htab_free.o obj/htab_hash_function.o obj/htab_init.o obj/htab_lookup_add.o obj/htab_size.o obj/htab_statistics.o
	ar r $@ $^

lib/libhtab.so: obj/htab_bucket_count.o obj/htab_clear.o obj/htab_erase.o obj/htab_find.o obj/htab_for_each.o obj/htab_free.o obj/htab_hash_function.o obj/htab_init.o obj/htab_lookup_add.o obj/htab_size.o obj/htab_statistics.o
	$(CC) -shared $^ -o $@

.PHONY: clean
clean:
	-rm -r ./obj/ tail wordcount cpp *.o
