// main.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"


void each(htab_pair_t *data) {
    printf("%s:\t%d\n", data->key, data->value);
}

int main() {
    char *s = malloc(255);
    htab_t *t = htab_init(10);

    while (read_word(s, 255, stdin)) {
        htab_lookup_add(t, s);
    }




    htab_for_each(t, each);


    free(s);
    htab_free(t);
}
