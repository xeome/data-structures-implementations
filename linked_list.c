#include <stdio.h>
#include <malloc.h>

// Node struct type
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Linked list struct type
typedef struct LinkedList {
    Node* head;
    Node* tail;
    int size;
} LinkedList;

// Linked list function prototypes
int size(LinkedList* list);
int empty(LinkedList* list);
int value_at(LinkedList* list, int index);
void push_front(LinkedList* list, int value);
int pop_front(LinkedList* list);
void push_back(LinkedList* list, int value);
int pop_back(LinkedList* list);
int front(LinkedList* list);
int back(LinkedList* list);
void insert(LinkedList* list, int index, int value);
void erase(LinkedList* list, int index);
int value_n_from_end(LinkedList* list, int n);
void reverse(LinkedList* list);
void remove_value(LinkedList* list, int value);
void swap(LinkedList* list, int index1, int index2);
void print_list(LinkedList* list);
void free_list(LinkedList* list);

// Testing linked list implementation
int main() {
    // Create linked list
    LinkedList* list = malloc(sizeof(LinkedList));

    // Initialize linked list
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    // Test linked list functions
    print_list(list);
    push_front(list, 1);
    push_front(list, 2);
    push_front(list, 3);
    push_front(list, 4);
    push_front(list, 5);
    printf("### Pushed 5 items {5, 4, 3, 2, 1} ###\n");
    print_list(list);

    printf("### Pop front ###\n");
    pop_front(list);
    print_list(list);

    printf("### Push back 6 ###\n");
    push_back(list, 6);
    print_list(list);

    printf("### Pop back ###\n");
    pop_back(list);
    print_list(list);

    printf("### Front ###\n");
    printf("%d\n", front(list));

    printf("### Back ###\n");
    printf("%d\n", back(list));

    printf("### Insert 7 at index 2 ###\n");
    insert(list, 2, 7);
    print_list(list);

    printf("### Erase at index 2 ###\n");
    erase(list, 2);
    print_list(list);

    printf("### Value 2 from end ###\n");
    printf("%d\n", value_n_from_end(list, 2));

    printf("### Reverse ###\n");
    reverse(list);
    print_list(list);

    printf("### Remove value 1 ###\n");
    remove_value(list, 1);
    print_list(list);

    printf("### Swap index 0 and 2 ###\n");
    swap(list, 0, 2);
    print_list(list);

    // Free memory
    free_list(list);

    return 0;
}

// Linked list function definitions
int size(LinkedList* list) {
    return list->size;
}

int empty(LinkedList* list) {
    return list->size == 0;
}

int value_at(LinkedList* list, int index) {
    if (index >= size(list)) {
        printf("Index out of bounds\n");
        return -1;
    }
    Node* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

void push_front(LinkedList* list, int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    if (list->size == 1) {
        list->tail = new_node;
    }
}

int pop_front(LinkedList* list) {
    if (empty(list)) {
        printf("List is empty\n");
        return -1;
    }
    Node* temp = list->head;
    list->head = list->head->next;
    int value = temp->data;
    free(temp);
    list->size--;
    return value;
}

void push_back(LinkedList* list, int value) {
    Node* new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    if (empty(list)) {
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

int pop_back(LinkedList* list) {
    if (empty(list)) {
        printf("List is empty\n");
        return -1;
    }

    Node* current = list->head;
    for (int i = 0; i < list->size - 2; i++) {
        current = current->next;
    }
    Node* temp = list->tail;
    list->tail = current;
    list->tail->next = NULL;
    int value = temp->data;
    free(temp);
    list->size--;
    return value;
}

int front(LinkedList* list) {
    if (empty(list)) {
        printf("List is empty\n");
        return -1;
    }
    return list->head->data;
}

int back(LinkedList* list) {
    if (empty(list)) {
        printf("List is empty\n");
        return -1;
    }
    return list->tail->data;
}

void insert(LinkedList* list, int index, int value) {
    if (index >= size(list)) {
        printf("Index out of bounds\n");
        return;
    }
    Node* new_node = malloc(sizeof(Node));
    new_node->data = value;
    Node* current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

void erase(LinkedList* list, int index) {
    if (index >= size(list)) {
        printf("Index out of bounds\n");
        return;
    }
    Node* current = list->head;
    for (int i = 0; i < index - 1; i++) {
        current = current->next;
    }
    Node* temp = current->next;
    current->next = current->next->next;
    free(temp);
    list->size--;
}

int value_n_from_end(LinkedList* list, int n) {
    if (n >= size(list)) {
        printf("Index out of bounds\n");
        return -1;
    }
    Node* current = list->head;
    for (int i = 0; i < list->size - n - 1; i++) {
        current = current->next;
    }
    return current->data;
}

void reverse(LinkedList* list) {
    Node* current = list->head;
    Node* prev = NULL;
    Node* next = NULL;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void remove_value(LinkedList* list, int value) {
    Node* current = list->head;
    Node* prev = NULL;
    while (current != NULL) {
        if (current->data == value) {
            if (prev == NULL) {
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            list->size--;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void swap(LinkedList* list, int index1, int index2) {
    if (index1 >= size(list) || index2 >= size(list)) {
        printf("Index out of bounds\n");
        return;
    }
    Node* current1 = list->head;
    Node* current2 = list->head;
    for (int i = 0; i < index1; i++) {
        current1 = current1->next;
    }
    for (int i = 0; i < index2; i++) {
        current2 = current2->next;
    }
    int temp = current1->data;
    current1->data = current2->data;
    current2->data = temp;
}

void print_list(LinkedList* list) {
    Node* current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

void free_list(LinkedList* list) {
    Node* current = list->head;
    Node* temp = NULL;
    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }
    free(list);
}