// htab_statistics.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include "private_htab.h"

void htab_statistics(const htab_t *t) {
    struct htab_item *tmp_ptr;
    size_t item_count = 0;
    double nonempty_count = 0;
    size_t min = 0;
    size_t max = 0;
    double avg = 0;
    for (size_t i = 0; i < t->arr_size; ++i) {
        if (!t->arr_ptr[i]) {
            continue;
        }

        tmp_ptr = t->arr_ptr[i];
        ++nonempty_count;

        item_count = 0;
        while (tmp_ptr) {
            ++item_count;
            tmp_ptr = tmp_ptr->next;
        }

        if (max < item_count) {
            max = item_count;
        }

        if (min > item_count || min == 0) {
            min = item_count;
        }
    }
    avg = t->size / nonempty_count;

    printf("min: %zu\n", min);
    printf("max: %zu\n", max);
    printf("avg: %lf\n", avg);

}
