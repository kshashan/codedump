#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

struct stack {
  int *s;
  int size;
  int sp;
};

static struct stack *createstack(size_t size) {
  struct stack *st = NULL;

  if (size == 0)
    return NULL;

  st = malloc(sizeof(struct stack));

  st->s = malloc(size);
  st->size = size;
  st->sp = -1;

  return st;
}

static void destroystack(struct stack *st) {
  if (st == NULL)
    return;

  free(st->s);
  free(st);

  return;
}

static int push(struct stack *st, int val) {
  if (st == NULL)
    return -1;

  if (st->sp == (st->size / sizeof(int)))
    return -2;

  st->sp++;
  st->s[st->sp] = val;

  return 0;
}

static int pop(struct stack *st, int *val) {
  if (st == NULL)
    return -1;

  if (st->sp < 0)
    return -2;

  *val = st->s[st->sp];
  st->sp--;

  return 0;
}

static int isstackempty(struct stack *st) {
  if (st)
    if (st->sp == -1)
      return 1;

  return 0;
}

static int top(struct stack *st)
{
    return st->s[st->sp];
}

// Complete the largestRectangle function below.
long largestRectangle(int h_count, int* h) {
    int i = 0, n = h_count, *a = h, t;
    int area = 0, max = 0;
    struct stack *st = NULL;

    st = createstack(n * sizeof(int));

    while(i <= n) {
        if ( i != n && (isstackempty(st) || a[i] >= a[top(st)])) {
            push(st, i);
            printf("i %d\n", i);
        } else {
            /* pop until get top <= a[i] */
            while ((i == n || a[i] <= a[top(st)]) && !isstackempty(st)) {
                pop(st, &t);
                if (isstackempty(st))
                    area = a[t] * i;
                else
                    area = a[t] * (i - top(st) -1);
                if (area > max)
                    max = area;
            }
            push(st, i);
        }
        i++;
    }
 
    destroystack(st);

    return max;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* n_endptr;
    char* n_str = readline();
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** h_temp = split_string(readline());

    int* h = malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        char* h_item_endptr;
        char* h_item_str = *(h_temp + i);
        int h_item = strtol(h_item_str, &h_item_endptr, 10);

        if (h_item_endptr == h_item_str || *h_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(h + i) = h_item;
    }

    int h_count = n;

    long result = largestRectangle(h_count, h);

    fprintf(fptr, "%ld\n", result);

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
