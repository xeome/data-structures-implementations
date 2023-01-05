#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_TREE_HT 100

typedef struct MinHeapNode {
    char data;
    unsigned frequency;
    struct MinHeapNode *left, *right;
} MinHeapNode;

typedef struct MinHeap {
    unsigned size, capacity;
    MinHeapNode* array[1024];
} MinHeap;

MinHeapNode* new_node(char data, unsigned freq) {
    MinHeapNode* temp;
    int rv = posix_memalign((void**)&temp, 16, sizeof(MinHeapNode));
    assert(rv == 0);
    *temp = (MinHeapNode){data, freq, NULL, NULL};
    return temp;
}

MinHeap* create_min_heap(unsigned capacity) {
    return &(MinHeap){0, capacity};
}

void swap(MinHeapNode** a, MinHeapNode** b) {
    MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

void min_heapify(MinHeap* min_heap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < min_heap->size &&
        min_heap->array[left]->frequency < min_heap->array[smallest]->frequency)
        smallest = left;
    if (right < min_heap->size && min_heap->array[right]->frequency <
                                      min_heap->array[smallest]->frequency)
        smallest = right;
    if (smallest != idx) {
        swap(&min_heap->array[smallest], &min_heap->array[idx]);
        min_heapify(min_heap, smallest);
    }
}

bool is_size_one(MinHeap* min_heap) {
    return min_heap->size == 1;
}

MinHeapNode* extract_min(MinHeap* min_heap) {
    MinHeapNode* temp = min_heap->array[0];
    min_heap->array[0] = min_heap->array[--min_heap->size];
    min_heapify(min_heap, 0);
    return temp;
}

void insert(MinHeap* min_heap, MinHeapNode* min_heap_node) {
    int i = min_heap->size++;
    while (i &&
           min_heap_node->frequency < min_heap->array[(i - 1) / 2]->frequency) {
        min_heap->array[i] = min_heap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    min_heap->array[i] = min_heap_node;
}

MinHeap* create_and_build_min_heap(char* data, int* freq, int size) {
    MinHeap* min_heap = create_min_heap(size);
    for (int i = 0; i < size; i++)
        min_heap->array[i] = new_node(data[i], freq[i]);
    min_heap->size = size;
    for (int i = (min_heap->size - 2) / 2; i >= 0; i--)
        min_heapify(min_heap, i);
    return min_heap;
}

MinHeapNode* build_huffman_tree(char* data, int* freq, int size) {
    MinHeapNode *left, *right, *top;
    MinHeap* min_heap = create_and_build_min_heap(data, freq, size);
    while (!is_size_one(min_heap)) {
        left = extract_min(min_heap);
        right = extract_min(min_heap);
        top = new_node('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insert(min_heap, top);
    }
    return extract_min(min_heap);
}

void huffman_codes_util(MinHeapNode* root,
                        int* arr,
                        int top,
                        char** codes,
                        int* freq) {
    if (root->left) {
        arr[top] = 0;
        huffman_codes_util(root->left, arr, top + 1, codes, freq);
    }
    if (root->right) {
        arr[top] = 1;
        huffman_codes_util(root->right, arr, top + 1, codes, freq);
    }
    if (!root->left && !root->right) {
        codes[root->data] = calloc(MAX_TREE_HT, sizeof(char));
        for (int i = 0; i < top; i++)
            codes[root->data][i] = arr[i] + '0';
        codes[root->data][top] = '\0';
    }
}

void huffman_codes(char* data, int* freq, int size, char** codes) {
    MinHeapNode* root = build_huffman_tree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    huffman_codes_util(root, arr, top, codes, freq);
}

void print_codes(char* data, int* freq, int size) {
    char* codes[256] = {0};
    huffman_codes(data, freq, size, codes);
    for (int i = 0; i < size; i++)
        printf("%c: %s\n", data[i], codes[data[i]]);
}

int main() {
    char arr[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int freq[] = {5, 9, 12, 13, 16, 45};
    int size = sizeof(arr) / sizeof(arr[0]);
    print_codes(arr, freq, size);
    return 0;
}
