#include <stdio.h>
#include <stdlib.h>

struct Node {
    char data;
    struct Node* next;
};

struct Queue {
    struct Node* front;
    struct Node* rear;
};

struct Node* createNode(char data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void enqueue(struct Queue* q, char data) {
    struct Node* newNode = createNode(data);
    if(q->rear == NULL) {
        q->front = q->rear = newNode;
        return;
    }
    q->rear->next = newNode;
    q->rear = newNode;
}

void dequeue(struct Queue* q) {
    if(q->front == NULL)
        return;
    struct Node* temp = q->front;
    q->front = q->front->next;
    if(q->front == NULL)
        q->rear = NULL;
    free(temp);
}

void printQueue(struct Queue* q) {
    if(q->front == NULL)
        return;
    struct Node* temp = q->front;
    while(temp != NULL) {
        printf("%c ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void reverseQueue(struct Queue* q) {
    if(q->front == NULL)
        return;
    struct Node* current = q->front;
    struct Node* prev = NULL;
    struct Node* next = NULL;
    while(current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    q->front = prev;
}

void freeQueue(struct Queue* q) {
    struct Node* temp = q->front;
    while(temp != NULL) {
        struct Node* next = temp->next;
        free(temp);
        temp = next;
    }
    q->front = q->rear = NULL;
}

int main() {
    struct Queue q = {NULL, NULL};
    int n, i;
    char data;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter %d characters:\n", n);
    for(i = 0; i < n; i++) {
        scanf(" %c", &data);
        enqueue(&q, data);
    }
    printf("Initial Queue: ");
    printQueue(&q);
    printf("Reversed Queue: ");
    reverseQueue(&q);
    printQueue(&q);
    printf("\n");
    freeQueue(&q);
    return 0;
}
