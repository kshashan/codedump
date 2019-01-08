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

void swap(int *a, int *b)
{
    int temp;

    temp = *a;
    *a = *b;
    *b = temp;

    return;
}

int heapify(int *a, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2; 

    if (left < n && a[largest] < a[left]) {
        largest = left;
    }

    if (right < n && a[largest] < a[right]) {
        largest = right;
    }

    if (i != largest) {
        swap(&a[i], &a[largest]);
        heapify(a, n, largest);
    }

    return 0;
}

int heap_sort(int *a, int n)
{
    int i;

    for (i = n/2 - 1; i >= 0; i--) {
        heapify(a, n, i);
    }

    for (i = n - 1; i >= 0; i--) {
        swap(&a[0], &a[i]);
        heapify(a, i, 0);
    }

    return 0;
}

void print_array(int *a, int n)
{
    int i;

    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");

    return;
}

// Complete the largestRectangle function below.
int main(void)
    int i, max = 0, temp_max = 0;
    int a[] = {7, 2, 4, 1, 3, 2};

    heap_sort(h, h_count);
    
    print_array(a, sizeof(a) / sizeof(int));
    
    return max;
}
