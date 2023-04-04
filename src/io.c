// main.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>


int read_word(char *s, int max, FILE *f) {
    int tmp_char;

    bool exceeded = false;
    bool discard_rest = false;

    int i = 0;
    while ((tmp_char = fgetc(f)) != EOF && isspace(tmp_char))
        ;

    if (tmp_char == EOF) {
        return i;
    }

    do {
        if (i + 1 >= max) {
            if (!exceeded) {
                fputs("exceeded max word length\n", stderr);
                exceeded = true;
            }

            discard_rest = true;
        }

        if (!discard_rest) {
            s[i] = tmp_char;
            ++i;
        }
    } while ((tmp_char = fgetc(f)) != EOF && !isspace(tmp_char));

    s[i] = 0;

    return i;
}
