#include <stdio.h>
#include <malloc.h>

// Queue struct type
typedef struct Queue {
    int* data;
    int size, capacity, front, back;
} Queue;

void enqueue(Queue* queue, int data);
int dequeue(Queue* queue);
int empty(Queue* queue);
int full(Queue* queue);

int main() {
    // Create queue
    Queue* queue = malloc(sizeof(Queue));
    // Initialize queue
    queue->size = 0;
    queue->capacity = 4;
    queue->front = 0;
    queue->back = 0;
    queue->data = malloc(sizeof(int) * queue->capacity);
    // Test queue functions
    enqueue(queue, 1);
    enqueue(queue, 2);
    enqueue(queue, 3);
    enqueue(queue, 4);
    enqueue(queue, 5);
    printf("### Enqueued 5 items {1, 2, 3, 4, 5} ###\n");
    printf("### Dequeued %d ###\n", dequeue(queue));
    printf("### Dequeued %d ###\n", dequeue(queue));
    printf("### Dequeued %d ###\n", dequeue(queue));
    printf("### Dequeued %d ###\n", dequeue(queue));
    printf("### Dequeued %d ###\n", dequeue(queue));
    printf("### Dequeued %d ###\n", dequeue(queue));

    // Free queue
    free(queue->data);
    free(queue);

    return 0;
}

inline void enqueue(Queue* queue, int data) {
    if (full(queue)) {
        printf("Queue is full\n");
        return;
    }
    queue->back = (queue->back + 1) % queue->capacity;
    queue->data[queue->back] = data;
    queue->size++;
}
int dequeue(Queue* queue) {
    if (empty(queue)) {
        printf("Queue is empty\n");
        return -1;
    }
    int data = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size--;
    return data;
}
int empty(Queue* queue) {
    return queue->size == 0;
}
int full(Queue* queue) {
    return queue->size == queue->capacity;
}
