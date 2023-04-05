// htab_erase.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "private_htab.h"

bool htab_erase(htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    struct htab_item *curr_item = t->arr_ptr[index];
    struct htab_item *last_item;

    if (!curr_item) {
        return false;
    }

    if (strcmp(curr_item->data.key, key) == 0) {
        t->arr_ptr[index] = curr_item->next;
        free((char*)curr_item->data.key);
        free(curr_item);
        t->size--;
        return true;
    }

    while (curr_item) {
        if (strcmp(curr_item->data.key, key) == 0) {
            last_item->next = curr_item->next;
            free((char*)curr_item->data.key);
            free(curr_item);
            t->size--;
            return true;
        }
        last_item = curr_item;
        curr_item = curr_item->next;
    }
    return false;
}
