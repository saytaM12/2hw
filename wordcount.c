// wordcount.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include "io.h"
#include "htab.h"

#define MAX_WORD_SIZE 255

void each(htab_pair_t *data) {
    printf("%s\t%d\n", data->key, data->value);
}

int main() {
    char *s = malloc(MAX_WORD_SIZE);
    htab_t *t = htab_init(10000);

    while (read_word(s, MAX_WORD_SIZE, stdin)) {
        htab_lookup_add(t, s);
    }

    htab_for_each(t, each);

    #ifdef STATISTICS

    htab_statistics(t);

    #endif // STATISTICS

    free(s);
    htab_free(t);
}
