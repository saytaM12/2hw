// tail.c
// Řešení IJC-DU2, příklad 1), 18.4.2023
// Autor: Matyáš Oujezdský, FIT
// Přeloženo: clang version 10.0.0-4ubuntu1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_LINE_SIZE 4095

typedef struct cb {
    char **data;  // array of lines
    size_t size;  // size of the buffer
    size_t count; // current number of lines in buffer
    size_t start; // index of first line
    size_t end;   // index of last line
} cb_t;

// allocate neccesary memory and return pointer to circular buffer
cb_t *cb_create(size_t n) {
    cb_t *buffer = malloc(sizeof(cb_t));
    if (!buffer) {
        fputs("couldn't allocate memory for buffer\n", stderr);
        return NULL;
    }

    buffer->data = calloc(n, sizeof(char *));
    if (!buffer->data) {
        fputs("couldn't allocate memory for lines in buffer\n", stderr);
        free(buffer);
        return NULL;
    }

    buffer->size = n;
    buffer->count = 0;
    buffer->start = 0;
    buffer->end = 0;

    return buffer;
}

/*
input line to circular buffer at write pointer
and increase write pointer
*/
char *cb_put(cb_t *cb, char *line) {
    char *old_string = cb->data[cb->end];

    cb->data[cb->end++] = line;
    cb->end %= cb->size;
    if (cb->count < cb->size) {
        cb->count++;
    }
    if (old_string) {
        cb->start++;
        cb->start %= cb->size;
    }
    return old_string;
}

/*
return string at the read pointer of circural buffer
and increase read pointer
*/
char *cb_get(cb_t *cb) {
    if (cb->count == 0) {
        fputs("buffer is empty\n", stderr);
        return NULL;
    }
    char *curr_line = cb->data[cb->start++];
    cb->start %= cb->size;
    cb->count--;
    return curr_line;
}

// free every allocated part of circular buffer
void cb_free(cb_t *cb) {
    for (size_t i = 0; i < cb->size; ++i) {
        if (cb->data[i]) {
            free(cb->data[i]);
        }
    }
    free(cb->data);
    free(cb);
}

// reads file by character and at each \n sends the line to cb_put
void read_file(cb_t *cb, FILE *stream) {
    int tmp_char;
    char *tmp_string = malloc(MAX_LINE_SIZE);
    if (!tmp_string) {
        fputs("couldn't allocate memory for tmp_string", stderr);
        return;
    }

    bool exceeded = false;
    bool discard_rest = false;

    int i = 0;
    while ((tmp_char = fgetc(stream)) != EOF) {
        if (i + 1 >= MAX_LINE_SIZE) {
            if (!exceeded) {
                fputs("exceeded max line length\n", stderr);
                exceeded = true;
            }

            discard_rest = true;
        }

        if (!discard_rest) {
            tmp_string[i] = tmp_char;
        }

        // at \n end the string by '\0' and send the string to cb_put
        if (tmp_char == '\n') {
            tmp_string[i] = 0;
            tmp_string = cb_put(cb, tmp_string);
            if (!tmp_string) {
                tmp_string = malloc(MAX_LINE_SIZE);
            }
            i = 0;
        }

        else if (!discard_rest) {
            ++i;
        }
    }

    if (tmp_string) {
        free(tmp_string);
    }
}

// print help (kind of self-explainatory)
void print_help(char *file_name, FILE *stream) {
    fprintf(stream, "Usage: %s [OPTION] [FILE]\n", file_name);
    fprintf(stream, "Print the last 10 lines of each FILE to standard output.\n\n\
With no FILE, read standard input.\n\n\
Mandatory arguments to long options are mandatory for short options too.\n\n\
OPTION%30sFUNCTION\n", "");
    fprintf(stream, "-n, --number NUM%20soutput the last NUM lines (NUM must be > 0),\n\
%38sinstead of the last 10\n\n", "", "");
    fprintf(stream, "-h, --help%26sprints this help\n", "");
}

int main(int argc, char **argv) {

    size_t size = 10;
    FILE *stream = stdin;


    // make sure to read only first instance of -n or file names
    bool file_read = false;
    bool num_read = false;

    for (int i = 1; i < argc; i++) {
        // a argument -h or --help was passed, so print help
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            print_help(argv[0], stdout);
            return 0;
        }

        // a argument -n or --number was passed,
        // so chech next argument for number
        if ((strcmp(argv[i], "-n") == 0 ||
             strcmp(argv[i], "--number") == 0) && !num_read) {

            num_read = true;

            // check if there is a next argument and read it
            if (argc > i + 1) {
                size = atoi(argv[i + 1]);

                // this happens with numbers too big or negative
                if (size > LONG_MAX) {
                    print_help(argv[0], stderr);
                    return 1;
                }
            }

            // if the number is zero or not inputed
            if (size == 0 || argc <= i + 1) {
                print_help(argv[0], stderr);
                return 1;
            }

            // skip the number in the next loop cycle
            i++;
        }

        // open the file and set it to be read from
        else if (!file_read) {
            file_read = true;
            stream = fopen(argv[i], "r");
            if (!stream) {
                fprintf(stderr, "Couldn't open a file with name %s\n", argv[i]);
                return 1;
            }
        }
    }

    cb_t *cb = cb_create(size);
    if (!cb || !cb->data) {
        return 1;
    }
    read_file(cb, stream);
    while (cb->count) {
        printf("%s\n", cb_get(cb));
    }
    cb_free(cb);
}
