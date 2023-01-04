#include <stdio.h>
#include <stdlib.h>

// Vector struct
typedef struct {
    int size;
    int capacity;
    int* data;
} Vector;

// Vector function prototypes
int size(Vector* vector);
int capacity(Vector* vector);
int is_empty(Vector* vector);
int at(Vector* vector, int index);
void push(Vector* vector, int item);
void insert(Vector* vector, int index, int item);
void prepend(Vector* vector, int item);
int pop(Vector* vector);
void delete(Vector* vector, int index);
void remove_item(Vector* vector, int item);
int find(Vector* vector, int item);
void resize(Vector* vector, int new_capacity);
void print_vector(Vector* vector);

// Testing vector implementation
int main() {
    // Create vector
    Vector* vector = malloc(sizeof(Vector));

    // Initialize vector
    vector->size = 0;
    vector->capacity = 4;
    vector->data = malloc(sizeof(int) * vector->capacity);

    // Test vector functions
    print_vector(vector);
    push(vector, 1);
    push(vector, 2);
    push(vector, 3);
    push(vector, 4);
    push(vector, 5);
    printf("### Pushed 5 items {1, 2, 3, 4, 5} ###\n");
    print_vector(vector);

    printf("### Inserted 6 at index 2 ###\n");
    insert(vector, 1, 6);
    print_vector(vector);

    printf("### Prepend 7 ###\n");
    prepend(vector, 7);
    print_vector(vector);

    printf("### Pop ###\n");
    pop(vector);
    print_vector(vector);

    printf("### Delete at index 2 ###\n");
    delete (vector, 1);
    print_vector(vector);

    printf("### Remove item 3 ###\n");
    remove_item(vector, 3);
    print_vector(vector);

    printf("### Find item 2 and 3 ###\n");
    printf("Found 2 at index %d\n", find(vector, 2));
    printf("Found 3 at index %d\n", find(vector, 3));

    // Test if vector resizes after popping an item when size is 1/4 of capacity
    printf("### Pop until size is 1/4 of capacity ###\n");
    pop(vector);
    pop(vector);
    pop(vector);
    print_vector(vector);

    // Free vector
    free(vector->data);
    free(vector);

    return 0;
}

// Vector function definitions
int size(Vector* vector) {
    return vector->size;
}

int capacity(Vector* vector) {
    return vector->capacity;
}

int is_empty(Vector* vector) {
    return vector->size == 0;
}

int at(Vector* vector, int index) {
    if (index >= vector->size) {
        printf("Index out of bounds");
        return -1;
    }
    return vector->data[index];
}

void push(Vector* vector, int item) {
    if (vector->size == vector->capacity) {
        resize(vector, vector->capacity * 2);
    }
    vector->data[vector->size] = item;
    vector->size++;
}

void insert(Vector* vector, int index, int item) {
    if (index >= vector->size) {
        printf("Index out of bounds");
        return;
    }
    if (vector->size == vector->capacity) {
        resize(vector, vector->capacity * 2);
    }
    // Shift items to the right
    for (int i = vector->size; i > index; i--) {
        vector->data[i] = vector->data[i - 1];
    }
    vector->data[index] = item;
    vector->size++;
}

void prepend(Vector* vector, int item) {
    insert(vector, 0, item);
}

int pop(Vector* vector) {
    if (vector->size == 0) {
        printf("Vector is empty");
        return -1;
    }
    int item = vector->data[vector->size - 1];
    vector->size--;
    // Resize to half if size is 1/4 of capacity
    if (vector->size == vector->capacity / 4) {
        resize(vector, vector->capacity / 2);
    }
    return item;
}

void delete(Vector* vector, int index) {
    if (index >= vector->size) {
        printf("Index out of bounds");
        return;
    }
    // Shift items to the left
    for (int i = index; i < vector->size - 1; i++) {
        vector->data[i] = vector->data[i + 1];
    }
    vector->size--;
    if (vector->size == vector->capacity / 4) {
        resize(vector, vector->capacity / 2);
    }
}

void remove_item(Vector* vector, int item) {
    for (int i = 0; i < vector->size; i++) {
        if (vector->data[i] == item) {
            delete (vector, i);
            i--;
        }
    }
}

int find(Vector* vector, int item) {
    for (int i = 0; i < vector->size; i++) {
        if (vector->data[i] == item) {
            return i;
        }
    }
    return -1;
}

void resize(Vector* vector, int new_capacity) {
    int* new_data = (int*)malloc(new_capacity * sizeof(int));
    for (int i = 0; i < vector->size; i++) {
        new_data[i] = vector->data[i];
    }
    free(vector->data);
    vector->data = new_data;
    vector->capacity = new_capacity;
}

void print_vector(Vector* vector) {
    printf("Size: %d\n", vector->size);
    printf("Capacity: %d\n", vector->capacity);
    printf("Data: [");
    for (int i = 0; i < vector->size; i++) {
        printf("%d", vector->data[i]);
        if (i != vector->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}