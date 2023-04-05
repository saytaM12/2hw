// htab_for_each.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "private_htab.h"

void htab_for_each(const htab_t *t, void (*f)(htab_pair_t *data)) {
    struct htab_item *tmp_ptr;
    for (size_t i = 0; i < t->arr_size; ++i) {
        tmp_ptr = t->arr_ptr[i];
        while (tmp_ptr) {
            f(&tmp_ptr->data);
            tmp_ptr = tmp_ptr->next;
        }
    }
}
