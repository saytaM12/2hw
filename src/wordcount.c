// main.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"


int main() {
    char *s = malloc(255);
    htab_t *t = htab_init(10);
    htab_pair_t *pair;

    while (read_word(s, 255, stdin)) {
        htab_lookup_add(t, s);
    }

    pair = htab_find(t, s);
    printf("%s, %d\n", pair->key, pair->value);
    free(s);
    htab_free(t);
}
