// htab_init.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include "private_htab.h"

htab_t *htab_init(const size_t n) {
    htab_t *t = malloc(sizeof(htab_t));
    if (!t) {
        fputs("couldn't allocate memory for hash tab", stderr);
        return NULL;
    }

    t->arr_ptr = calloc(n, sizeof(struct htab_item*));
    if (!t->arr_ptr) {
        fputs("couldn't allocate memory for array of pointers", stderr);
        free(t);
        return NULL;
    }

    t->size = 0;
    t->arr_size = n;

    return t;
}
