CC := clang
CFLAGS := -g -Wall -std=c11 -pedantic -DSTATISTICS -Wextra -O2 -fPIC
CREATEDIR := $(shell mkdir -p obj lib)

DEPENDENCIES:=$(shell $(CC) -MM *.c | sed -r 's/.*:.*/obj\/\0/' > dep.d)

.PHONY: all
all: tail wordcount wordcount-dynamic

-include dep.d

tail: obj/tail.o
	$(CC) $(CFLAGS) $^ -o $@

wordcount: obj/io.o obj/wordcount.o lib/libhtab.a
	$(CC) $(CFLAGS) $^ -o $@

wordcount-dynamic: obj/io.o obj/wordcount.o lib/libhtab.so
	$(CC) $(CFLAGS) $^ -o $@

obj/%.o: %.c
	$(CC) $(CFLAGS) $< -c -o $@

lib/libhtab.a: obj/htab_bucket_count.o obj/htab_clear.o obj/htab_erase.o obj/htab_find.o obj/htab_for_each.o obj/htab_free.o obj/htab_hash_function.o obj/htab_init.o obj/htab_lookup_add.o obj/htab_size.o obj/htab_statistics.o
	ar r $@ $^

lib/libhtab.so: obj/htab_bucket_count.o obj/htab_clear.o obj/htab_erase.o obj/htab_find.o obj/htab_for_each.o obj/htab_free.o obj/htab_hash_function.o obj/htab_init.o obj/htab_lookup_add.o obj/htab_size.o obj/htab_statistics.o
	$(CC) -shared $^ -o $@

.PHONY: clean
clean:
	-rm -r ./lib/ ./obj/ tail wordcount wordcount-dynamic dep.d
