// htab_bucket_count.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "private_htab.h"

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}
