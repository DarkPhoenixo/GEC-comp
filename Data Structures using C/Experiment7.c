#include <stdio.h>
#include <stdlib.h>
#define MAX 4

int front = -1;
int rear = -1;
int cqueue_arr[MAX];

// Check if the queue is full
int isFull() {
    return (front == (rear + 1) % MAX) || (front == 0 && rear == MAX - 1);
}

// Check if the queue is empty
int isEmpty() {
    return (front == -1);
}

// Insert data into the circular queue
void insertcqueue(int data) {
    if (isFull()) {
        printf("Circular Queue Overflow\n");
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear = (rear + 1) % MAX;
    cqueue_arr[rear] = data;
}

// Delete data from the circular queue
int deletecqueue() {
    if (isEmpty()) {
        printf("Circular Queue Underflow\n");
        exit(1);
    }
    int data = cqueue_arr[front];
    if (front == rear) {
        front = rear = -1; // Queue is now empty
    } else {
        front = (front + 1) % MAX;
    }
    return data;
}

// Peek the front element
int peek() {
    if (isEmpty()) {
        printf("Queue Underflow\n");
        exit(1);
    }
    return cqueue_arr[front];
}

// Display all elements of the circular queue
void displaycqueue() {
    if (isEmpty()) {
        printf("Queue is Empty\n");
        return;
    }
    printf("The elements of the queue are:\n");
    int i = front;
    while (1) {
        printf("%d ", cqueue_arr[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
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
        printf("\nMenu:\n");
        printf("1. Insert an element into the circular queue\n");
        printf("2. Delete an element from the circular queue\n");
        printf("3. Peek the front element\n");
        printf("4. Display the circular queue elements\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                printf("Enter the data to insert: ");
                scanf("%d", &data);
                insertcqueue(data);
                break;
            case 2:
                item = deletecqueue();
                printf("Deleted element is: %d\n", item);
                break;
            case 3:
                item = peek();
                printf("Front element is: %d\n", item);
                break;
            case 4:
                displaycqueue();
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
                break;
        }
    } while (option != 5);

    return 0;
}

