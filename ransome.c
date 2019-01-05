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

/* Hash table implementation */
#define MAX_ITEMS 30000

struct Item {
  char *key;
    int quantity;
};

int generateHash(char *key);

struct Item *search(char *key, struct Item **hashArray) {
    int index = generateHash(key);
    if (strcmp(hashArray[index]->key, key) == 0) {
        return hashArray[index];
    }
    else {
        // Move in the array until you find the item
        int looped = 0;
        while (strcmp(hashArray[index]->key, key) != 0) {
            ++index;

            // If we haven't looped wrap around
            if (!looped) {
                if (index == MAX_ITEMS) {
                    index %= MAX_ITEMS;
                    looped = 1;
                }
            }
            // If we have looped
            else {
                // And we reach the last element
                if (index == MAX_ITEMS - 1) break;
            }
        }
        if (strcmp(hashArray[index]->key, key) == 0)
            return hashArray[index];
        else
            return NULL;
    }
}

int generateHash(char *key) {
    unsigned long hash = 5381;
    int c;

    while ((c = *(key++)))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    // After this line, the hash has become an index
    int new_hash = (int)(hash % MAX_ITEMS);
    return new_hash;
}

void insert(char *key, struct Item **hashArray) {
    struct Item *item = malloc(sizeof(struct Item));
    assert(item != NULL);
    item->key = malloc(sizeof(char) * 6);
    strcpy(item->key, key);
    item->quantity = 1;

    int index = generateHash(key);

    // If the word has already been inserted into the array
    if (strcmp(hashArray[index]->key, key) == 0) {
        hashArray[index]->quantity+=1;
    }
    else {
        // Move in the array until you find an empty/deleted cell or the previous item
        while (hashArray[index]->key[0] != -1 && strcmp(hashArray[index]->key, key) != 0) {
            ++index;

            // Wrap around
            index %= MAX_ITEMS;
        }
        if (strcmp(hashArray[index]->key, key) == 0) 
            hashArray[index]->quantity+=1;
        else
            hashArray[index] = item;
    }
}

struct Item **newHashArray() {
    struct Item *dummyItem = NULL;
    dummyItem = malloc(sizeof(struct Item));
    assert(dummyItem != NULL);
    dummyItem->key = malloc(sizeof(char) * 6);
    assert(dummyItem->key != NULL);
    memset(dummyItem->key, 0, sizeof(char) * 6);
    dummyItem->key[0] = 255;
    dummyItem->quantity = -1;

    struct Item **hashArray = malloc(sizeof(struct Item *) * MAX_ITEMS);
    assert(hashArray != NULL);
    for (int i = 0; i < MAX_ITEMS; i++) {
        hashArray[i] = dummyItem;
    }
    return hashArray;
}
/* Hash table implementation */

// Complete the checkMagazine function below.
void checkMagazine(int magazine_count, char** magazine, int note_count, char** note) {
    int i;
    struct Item **mag = NULL;
    struct Item *wnote;
    
    if (magazine == NULL || note == NULL)
        goto no;

    if (magazine_count > 30000 || note_count > 30000)
        goto no;

    if (note_count > magazine_count)
        goto no;

    mag = newHashArray(); 
    for (i = 0; i < magazine_count; i++) {
        insert(magazine[i], mag);
    }

    for (i = 0; i < note_count; i++) {
        wnote = search(note[i], mag);
        if (wnote == NULL)
            goto no;
        if (wnote->quantity == 0)
            goto no;
        
        wnote->quantity--;
    }
yes:
    printf("Yes");
    return;
no:
    printf("No");
    return;
}

int main()
{
    char** mn = split_string(readline());

    char* m_endptr;
    char* m_str = mn[0];
    int m = strtol(m_str, &m_endptr, 10);

    if (m_endptr == m_str || *m_endptr != '\0') { exit(EXIT_FAILURE); }

    char* n_endptr;
    char* n_str = mn[1];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char** magazine_temp = split_string(readline());

    char** magazine = malloc(m * sizeof(char*));

    for (int i = 0; i < m; i++) {
        char* magazine_item = *(magazine_temp + i);

        *(magazine + i) = magazine_item;
    }

    int magazine_count = m;

    char** note_temp = split_string(readline());

    char** note = malloc(n * sizeof(char*));

    for (int i = 0; i < n; i++) {
        char* note_item = *(note_temp + i);

        *(note + i) = note_item;
    }

    int note_count = n;

    checkMagazine(magazine_count, magazine, note_count, note);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '\0';
    }

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
