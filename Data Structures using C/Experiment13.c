#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node *next, *prev;
};

struct Node *createNode(int value) {
    struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

struct Node *insertNodes(struct Node *start, int n) {
    struct Node *temp = NULL;
    int value;
    for (int i = 0; i < n; i++) {
        printf("Enter value for node %d: ", i + 1);
        scanf("%d", &value);
        struct Node *newNode = createNode(value);
        if (start == NULL) {
            start = newNode;
            temp = start;
        } else {
            temp->next = newNode;
            newNode->prev = temp;
            temp = newNode;
        }
    }
    return start;
}

void printList(struct Node *start) {
    struct Node *temp = start;

    // Print start pointer in a box pointing to the first node
    printf("\n  start\n");
    printf("----------\n");
    printf("|%8p|\n", start);
    printf("----------\n");
    printf("     |               \n");
    if (start != NULL) {
        printf("     V               \n\n");
    }

    while (temp != NULL) {
        if (temp->prev == NULL) {
            printf("  -----------------------------------------    \n");
            printf(" | Prev: NULL   | Data: %d | Next: %p |     %p \n", temp->data, temp->next, temp);
            printf("  -----------------------------------------    \n");
        } else if (temp->next == NULL) {
            printf("  -----------------------------------------    \n");
            printf(" | Prev: %p | Data: %d | Next:  NULL  |     %p \n", temp->prev, temp->data, temp);
            printf("  -----------------------------------------    \n");
        } else {
            printf("  -----------------------------------------    \n");
            printf(" | Prev: %p | Data: %d | Next: %p |     %p \n", temp->prev, temp->data, temp->next, temp);
            printf("  -----------------------------------------    \n");
        }

        if (temp->next != NULL) {
            printf("          ^                        |\n");
            printf("          |                        v\n");
        }
        temp = temp->next;
    }
    printf("\nNULL\n");
}


struct Node *swapAlternateNodes(struct Node *start) {
    if (start == NULL || start->next == NULL || start->next->next == NULL) {
        return start;  // No swap needed if fewer than 3 nodes
    }

    struct Node *current = start;
    struct Node *previous = NULL;
    
    while (current != NULL && current->next != NULL && current->next->next != NULL) {
        struct Node *first = current;
        struct Node *second = current->next;
        struct Node *third = current->next->next;
        struct Node *fourth = third->next;

        // Adjust pointers to swap first and third nodes
        if (previous != NULL) {
            previous->next = third;
        } else {
            start = third;  // Update start if first node is being swapped
        }
        
        third->prev = previous;
        third->next = second;
        second->prev = third;

        first->next = fourth;
        if (fourth != NULL) {
            fourth->prev = first;
        }

        first->prev = second;
        second->next = first;

        // Move pointers forward
        previous = first;
        current = fourth;
    }

    return start;  // Return the new start of the list
}



int main() {
        printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    struct Node *start = NULL;
    int choice, n;

    while(1) {
        printf("\nMenu:\n");
        printf("1. Insert nodes\n");
        printf("2. Display list\n");
        printf("3. Swap alternate nodes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter number of nodes to insert: ");
                scanf("%d", &n);
                start = insertNodes(start, n);
                break;

            case 2:
                printf("List:\n");
                printList(start);
                break;

            case 3:
            printf("*******************************\n");
            printf("Circular Linked List\n");
            printf("*******************************\n\n\n");
                printf("List before swapping alternate nodes:\n");
                printList(start);
                start = swapAlternateNodes(start);
                printf("List after swapping alternate nodes:\n");
                printList(start);
                break;

            case 4:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

