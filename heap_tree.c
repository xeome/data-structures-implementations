#include <stdio.h>
#include <malloc.h>

// Heap struct type
typedef struct Heap {
    int* data;
    int size;
    int capacity;
} Heap;

// Heap function prototypes
int is_empty(Heap* heap);
void insert(Heap* heap, int value);
int get_min(Heap* heap);
int extract_min(Heap* heap);
void sift_up(Heap* heap, int index);
void sift_down(Heap* heap, int index);
void remove_item(Heap* heap, int index);
void heapify(Heap* heap, int* array, int size);
void heap_sort(Heap* heap, int* array, int size);
int get_parent_index(int index);
int get_left_child_index(int index);
int get_right_child_index(int index);
void swap(int* array, int index1, int index2);
void print_heap(Heap* heap);
void free_heap(Heap* heap);

// Testing heap implementation
int main() {
    // Create heap
    Heap* heap = malloc(sizeof(Heap));

    // Initialize heap
    heap->size = 0;
    heap->capacity = 4;
    heap->data = malloc(sizeof(int) * heap->capacity);

    // Test heap functions
    printf("### Heap is empty: %d ###\n", is_empty(heap));
    printf("### Insert 1 ###\n");
    insert(heap, 1);
    print_heap(heap);
    printf("### Insert 2 ###\n");
    insert(heap, 2);
    print_heap(heap);
    printf("### Insert 3 ###\n");
    insert(heap, 3);
    print_heap(heap);
    printf("### Insert 4 ###\n");
    insert(heap, 4);
    print_heap(heap);
    printf("### Insert 5 ###\n");
    insert(heap, 5);
    print_heap(heap);
    printf("### Get min: %d ###\n", get_min(heap));
    printf("### Extract min: %d ###\n", extract_min(heap));
    print_heap(heap);
    printf("### Remove item at index 2 ###\n");
    remove_item(heap, 2);
    print_heap(heap);
    printf("### Heap sort ###\n");
    int array[] = {7, 6, 5, 4, 3, 2, 1};
    heap_sort(heap, array, 7);
    for (int i = 0; i < 7; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
    free_heap(heap);

    return 0;
}


int is_empty(Heap* heap) {
    return heap->size == 0;
}

void insert(Heap* heap, int value) {
    // Resize heap if necessary
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = realloc(heap->data, sizeof(int) * heap->capacity);
    }

    // Insert new value at the end of the heap
    heap->data[heap->size] = value;
    heap->size++;

    // Sift up the new value
    sift_up(heap, heap->size - 1);
}

int get_min(Heap* heap) {
    return heap->data[0];
}

int extract_min(Heap* heap) {
    // Get min value
    int min = heap->data[0];

    // Replace min value with last value in heap
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // Sift down the new value
    sift_down(heap, 0);

    return min;
}

void sift_up(Heap* heap, int index) {
    // Get parent index
    int parent = get_parent_index(index);

    // Check if parent is valid and if value at parent is greater than value at
    // index
    if (parent >= 0 && heap->data[parent] > heap->data[index]) {
        // Swap values
        swap(heap->data, parent, index);

        // Sift up again
        sift_up(heap, parent);
    }
}

void sift_down(Heap* heap, int index) {
    // Get left and right child indices
    int left = get_left_child_index(index);
    int right = get_right_child_index(index);

    // Get smallest child index
    int smallest = index;
    if (left < heap->size && heap->data[left] < heap->data[smallest]) {
        smallest = left;
    }
    if (right < heap->size && heap->data[right] < heap->data[smallest]) {
        smallest = right;
    }

    // Check if smallest child is valid and if value at smallest child is less
    // than value at index
    if (smallest != index) {
        // Swap values
        swap(heap->data, smallest, index);

        // Sift down again
        sift_down(heap, smallest);
    }
}

void remove_item(Heap* heap, int index) {
    // Replace value at index with last value in heap
    heap->data[index] = heap->data[heap->size - 1];
    heap->size--;

    // Sift down the new value
    sift_down(heap, index);
}

void heapify(Heap* heap, int* array, int size) {
    // Copy array into heap
    heap->size = size;
    heap->capacity = size;
    heap->data = malloc(sizeof(int) * heap->capacity);
    for (int i = 0; i < size; i++) {
        heap->data[i] = array[i];
    }

    // Sift down each parent node
    for (int i = (size - 2) / 2; i >= 0; i--) {
        sift_down(heap, i);
    }
}

void heap_sort(Heap* heap, int* array, int size) {
    // Heapify array
    heapify(heap, array, size);

    // Extract min value from heap and insert it into the array
    for (int i = 0; i < size; i++) {
        array[i] = extract_min(heap);
    }
}

int get_parent_index(int index) {
    return (index - 1) / 2;
}

int get_left_child_index(int index) {
    return 2 * index + 1;
}

int get_right_child_index(int index) {
    return 2 * index + 2;
}

void swap(int* array, int index1, int index2) {
    int temp = array[index1];
    array[index1] = array[index2];
    array[index2] = temp;
}

void print_heap(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

void free_heap(Heap* heap) {
    free(heap->data);
    free(heap);
}
