// htab.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "htab.h"

struct htab_item {
    htab_pair_t data;
    struct htab_item *next;
};

struct htab {
    size_t size;
    size_t arr_size;
    struct htab_item **arr_ptr;
};

size_t htab_hash_function(htab_key_t str) {
    unsigned h = 0;     // musí mít 32 bitů
    const unsigned char *p;
    for(p = (const unsigned char*)str; *p != '\0'; p++)
        h = 65599 * h + *p;
    return h;
}

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

size_t htab_size(const htab_t *t) {
    return t->size;
}

size_t htab_bucket_count(const htab_t *t) {
    return t->arr_size;
}

htab_pair_t *htab_find(const htab_t *t, htab_key_t key) {
    size_t index = (htab_hash_function(key) % t->arr_size);
    struct htab_item *curr_item = t->arr_ptr[index];
    while (curr_item) {
        if (strcmp(curr_item->data.key, key) == 0) {
            return &(curr_item->data);
        }

        curr_item = curr_item->next;
    }
    return NULL;
}

htab_pair_t *htab_lookup_add(htab_t *t, htab_key_t key) {
    htab_pair_t *return_pair;
    if ((return_pair = htab_find(t, key))) {
        return_pair->value++;
        return return_pair;
    }

    struct htab_item *item_to_add = calloc(1, sizeof(struct htab_item));
    if (!item_to_add) {
        fputs("couldn't allocate memory for item to add", stderr);
        return NULL;
    }

    size_t key_size = strlen(key) + 1;
    char *key_to_add = malloc(key_size);
    if (!key_to_add) {
        fputs("couldn't allocate memory for key in item to add", stderr);
        free(item_to_add);
        return NULL;
    }

    t->size++;

    memcpy(key_to_add, key, key_size);
    struct htab_pair data_to_add = {.key = key_to_add, .value = 1};
    item_to_add->data = data_to_add;

    size_t index = (htab_hash_function(key) % t->arr_size);
    if (!t->arr_ptr[index]) {
        t->arr_ptr[index] = item_to_add;
        return return_pair;
    }

    item_to_add->next = t->arr_ptr[index]->next;
    t->arr_ptr[index]->next = item_to_add;

    return return_pair;
}

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


void htab_free(htab_t *t) {
    htab_clear(t);
    free(t->arr_ptr);
    free(t);
}

#ifdef STATISTICS

void htab_statistics(const htab_t *t) {
    struct htab_item *tmp_ptr;
    int item_count;
    int nonempty_count;
    int min = 0;
    int max = 0;
    double avg = 0;
    for (size_t i = 0; i < t->arr_size; ++i) {
        tmp_ptr = t->arr_ptr[i];

        if (tmp_ptr) {
            ++nonempty_count;
        }

        item_count = 0;
        while (tmp_ptr) {
            ++item_count;
            tmp_ptr = tmp_ptr->next;
        }

        if (max < item_count) {
            max = item_count;
        }

        if (min > item_count) {
            min = item_count;
        }
    }
    avg = nonempty_count / t->size;

}

#endif //STATISTICS
