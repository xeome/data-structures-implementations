#include <stdio.h>
#include <malloc.h>

/* Implementation:
 * size() - returns number of data elements in list
 * empty() - bool returns true if empty
 * value_at(index) - returns the value of the nth item (starting at 0 for first)
 * push_front(value) - adds an item to the front of the list
 * pop_front() - remove front item and return its value
 * push_back(value) - adds an item at the end
 * pop_back() - removes end item and returns its value
 * front() - get value of front item
 * back() - get value of end item
 * insert(index, value) - insert value at index, so current item at that index is pointed to by new item at index
 * erase(index) - removes node at given index
 * value_n_from_end(n) - returns the value of the node at nth position from the end of the list
 * reverse() - reverses the list
 * remove_value(value) - removes the first item in the list with this value
 * */

// Node struct
struct node {
    int data;
    struct node *next;
};

// Linked list struct
struct linked_list {
    struct node *head;
    struct node *tail;
    int size;
};

// Linked list function prototypes
int size(struct linked_list *list);
int empty(struct linked_list *list);
int value_at(struct linked_list *list, int index);
void push_front(struct linked_list *list, int value);
int pop_front(struct linked_list *list);
void push_back(struct linked_list *list, int value);
int pop_back(struct linked_list *list);
int front(struct linked_list *list);
int back(struct linked_list *list);
void insert(struct linked_list *list, int index, int value);
void erase(struct linked_list *list, int index);
int value_n_from_end(struct linked_list *list, int n);
void reverse(struct linked_list *list);
void remove_value(struct linked_list *list, int value);
void print_list(struct linked_list *list);

// Testing linked list implementation
int main(){
    // Create linked list
    struct linked_list *list = malloc(sizeof(struct linked_list));

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

    // Free memory
    free(list);

    return 0;
}

// Linked list function definitions
int size(struct linked_list *list){
    return list->size;
}

int empty(struct linked_list *list){
    return list->size == 0;
}

int value_at(struct linked_list *list, int index){
    if (index >= list->size){
        printf("Index out of bounds\n");
        return -1;
    }
    struct node *current = list->head;
    for (int i = 0; i < index; i++){
        current = current->next;
    }
    return current->data;
}

void push_front(struct linked_list *list, int value){
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = list->head;
    list->head = new_node;
    list->size++;
    if (list->size == 1){
        list->tail = new_node;
    }
}

int pop_front(struct linked_list *list){
    if (list->size == 0){
        printf("List is empty\n");
        return -1;
    }
    struct node *temp = list->head;
    list->head = list->head->next;
    int value = temp->data;
    free(temp);
    list->size--;
    return value;
}

void push_back(struct linked_list *list, int value){
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    new_node->next = NULL;
    if (list->size == 0){
        list->head = new_node;
        list->tail = new_node;
    } else {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    list->size++;
}

int pop_back(struct linked_list *list){
    if (list->size == 0){
        printf("List is empty\n");
        return -1;
    }
    struct node *current = list->head;
    while (current->next != list->tail){
        current = current->next;
    }
    struct node *temp = list->tail;
    list->tail = current;
    list->tail->next = NULL;
    int value = temp->data;
    free(temp);
    list->size--;
    return value;
}

int front(struct linked_list *list){
    if (list->size == 0){
        printf("List is empty\n");
        return -1;
    }
    return list->head->data;
}

int back(struct linked_list *list){
    if (list->size == 0){
        printf("List is empty\n");
        return -1;
    }
    return list->tail->data;
}

void insert(struct linked_list *list, int index, int value){
    if (index >= list->size){
        printf("Index out of bounds\n");
        return;
    }
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = value;
    struct node *current = list->head;
    for (int i = 0; i < index - 1; i++){
        current = current->next;
    }
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
}

void erase(struct linked_list *list, int index){
    if (index >= list->size){
        printf("Index out of bounds\n");
        return;
    }
    struct node *current = list->head;
    for (int i = 0; i < index - 1; i++){
        current = current->next;
    }
    struct node *temp = current->next;
    current->next = current->next->next;
    free(temp);
    list->size--;
}

int value_n_from_end(struct linked_list *list, int n){
    if (n >= list->size){
        printf("Index out of bounds\n");
        return -1;
    }
    struct node *current = list->head;
    for (int i = 0; i < list->size - n - 1; i++){
        current = current->next;
    }
    return current->data;
}


void reverse(struct linked_list *list){
    struct node *current = list->head;
    struct node *prev = NULL;
    struct node *next = NULL;
    while (current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    list->head = prev;
}

void remove_value(struct linked_list *list, int value){
    struct node *current = list->head;
    struct node *prev = NULL;
    while (current != NULL){
        if (current->data == value){
            if (prev == NULL){
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

void print_list(struct linked_list *list){
    struct node *current = list->head;
    while (current != NULL){
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}
