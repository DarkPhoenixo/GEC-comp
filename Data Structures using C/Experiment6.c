#include <stdio.h>
#include <stdlib.h>
#define MAX 4
int front = -1;
int rear = -1;
int queue_arr[MAX];

int isFull() {
    return (rear == MAX - 1);
}

int isEmpty() {
    return (front == -1 || front > rear);
}

void insert(int data) {
    if (isFull()) {
        printf("Queue Overflow\n");
        return;
    }
    if (front == -1)
        front = 0;
    queue_arr[++rear] = data;
}

int delete() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return queue_arr[front++];
}

int peek() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return queue_arr[front];
}

void display() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    printf("The elements of the queue are:\n");
    for (int i = front; i <= rear; i++) {
        printf("%d ", queue_arr[i]);
    }
    printf("\n");
}

int main() {
    printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int option, data, item;
    do {
        printf("\nEnter the type of operation you want to perform on the queue:\n");
        printf("1. Insert an element in the queue\n");
        printf("2. Delete an element from the queue\n");
        printf("3. Peek the front element\n");
        printf("4. Display the queue elements\n");
        printf("5. Quit\n");
        printf("Enter your choice number:\n");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the data to insert:\n");
                scanf("%d", &data);
                insert(data);
                break;
            case 2:
                item = delete();
                printf("Deleted element is: %d\n", item);
                break;
            case 3:
                item = peek();
                printf("Front element is: %d\n", item);
                break;
            case 4:
                display();
                break;
            case 5:
                break;
            default:
                printf("Enter a valid option\n");
                break;
        }
    } while (option != 5);

    return 0;
}
