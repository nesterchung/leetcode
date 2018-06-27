#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
 *  heap in logic is a binary tree, and can be implements as a array
 *          0
 *         / \
 *        1   2
 *       /\   /\
 *      3 4   5 6
 * 
 *  [0 1 2 3 4 5 6]
 *  if current node is 1, then we can easy to calculate the index of left child as `1 * 2 + 1`, 
 *  and right child as `1 * 2 + 2` so the function is  left(index) = index*2+1, right(index) = left(index) + 1 
 *  and if node is 3, access parent by parent(index) = (index-1) / 2 
 */
typedef struct heap {
    int capacity;
    int *arr;
    int size;
} heap;

heap* heap_create();
void heap_destroy(heap*);

int parent_index(int);
int left_index(int);
int right_index(int);

int heap_parent(heap*, int);
int has_left(heap*, int);
int has_right(heap*, int);

int heap_item(heap*, int);
int heap_left(heap*, int);
int heap_right(heap*, int);

void heap_add(heap*, int);
int heap_peak(heap*);
int heap_poll(heap*);

void heapify_up(heap*);
void heapify_down(heap* h);

void ensureExtraCapacity(heap* h);
int* arrayCopyOf(int*, int, int);
void swap(int*, int, int);

void print(heap *h) {
    int i;
    for(i = 0; i < h->size; i++) {
        printf("%d ", h->arr[i]);
    }
    printf("\n");
}

int main(void) {
    heap* h = heap_create();

    int i;
    for(i = 0; i < 10; i++) {
        heap_add(h, 10-i);
    }

    while(h->size > 0) {
        printf("%d ", heap_poll(h));
    }
    printf("\n");
    heap_destroy(h);
    return 0;
}

heap* heap_create() {
    heap* ret = malloc(sizeof(heap));
    if (!ret)
        return NULL;
    ret->capacity = 16;
    ret->arr = malloc(sizeof(int)*ret->capacity);
    ret->size = 0;

    return ret;
}

void heap_destroy(heap* h) {
    free(h->arr);
    free(h);
}


int parent_index(int index) {
    return (index - 1) / 2;
}
int left_index(int index) {
    return (index * 2) + 1;
}

int right_index(int index) {
    return (index * 2) + 2;
}

int has_parent(int index) {
    return index > 0;
}

int has_left(heap*h, int index) {
    return left_index(index) < h->size;
}

int has_right(heap*h, int index) {
    return right_index(index) < h->size;
}

int heap_parent(heap *h, int index) {
    return heap_item(h, parent_index(index));
}

int heap_item(heap *h, int index) {
    return h->arr[index];
}

int heap_left(heap *h, int index) {
    return heap_item(h, left_index(index));
}

int heap_right(heap *h, int index) {
    return heap_item(h, right_index(index));
}


void heap_add(heap* h, int a) {
    ensureExtraCapacity(h);
    h->arr[h->size++] = a;
    heapify_up(h);
}

int heap_peak(heap *h) {
    if (h->size == 0) {
        return -1;
    }
    return h->arr[0];
}

int heap_poll(heap *h) {
    if (h->size == 0) {
        return -1;
    }

    int ret = h->arr[0];

    h->arr[0] = h->arr[h->size - 1];
    h->size--;

    heapify_down(h);

    return ret;
}

void heapify_down(heap* h) {
    int index = 0;
    while (has_left(h, index)) {
        //find the smaller child index
        int smaller_child_index = left_index(index);
        if (has_right(h, index) && heap_right(h, index) < heap_left(h, index)) {
            smaller_child_index = right_index(index);
        }

        if (heap_item(h, smaller_child_index) < heap_item(h, index)) {
            swap(h->arr, smaller_child_index, index);
            index = smaller_child_index;
        } else {
            break;
        }
    }
}

void heapify_up(heap* h) {
    int index = h->size - 1;
    while(has_parent(index) && heap_parent(h, index) > heap_item(h, index)) {
        swap(h->arr, index, parent_index(index));
        index = parent_index(index);
    }
}

void ensureExtraCapacity(heap* h) {
    if (h->size == h->capacity) {
        h->arr = arrayCopyOf(h->arr, h->capacity, h->capacity * 2);
    }
}

void swap(int *arr, int a, int b) {
    int c = arr[a];
    arr[a] = arr[b];
    arr[b] = c;
}

int* arrayCopyOf(int arr[], int len1, int len2) {
    int *ret = malloc(sizeof(int) * len2);
    memcpy(ret, arr, sizeof(int) * len1);
    return ret;
}


