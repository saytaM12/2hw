// htab_clear.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdlib.h>
#include "private_htab.h"


void htab_clear(htab_t *t) {
    struct htab_item *tmp_ptr;
    for (size_t i = 0; i < t->arr_size; ++i) {
        tmp_ptr = t->arr_ptr[i];
        while (tmp_ptr) {
            struct htab_item *curr_ptr = tmp_ptr;
            tmp_ptr = tmp_ptr->next;
            free((char*)curr_ptr->data.key);
            free(curr_ptr);
        }
    }

    t->size = 0;
}
