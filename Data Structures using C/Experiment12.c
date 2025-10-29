#include <stdio.h>
#include <stdlib.h>

struct Node {
    int value;
    struct Node* previous;
    struct Node* next;
};

struct Node* initList(struct Node* start, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = data;
    newNode->previous = NULL;
    newNode->next = NULL;
    start = newNode;
    return start;
}

struct Node* insertAtBeginning(struct Node* start, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->value = data;
    newNode->previous = NULL;
    newNode->next = start;
    start->previous = newNode;
    start = newNode;
    return start;
}

struct Node* insertAtEnd(struct Node* start, int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tempNode = start;
    while (tempNode->next != NULL) {
        tempNode = tempNode->next;
    }
    newNode->value = data;
    newNode->previous = tempNode;
    newNode->next = NULL;
    tempNode->next = newNode;
    return start;
}

struct Node* insertAfter(struct Node* start, int data, int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    struct Node* tempNode = start;
    while (tempNode != NULL) {
        if (tempNode->value == item) {
            newNode->value = data;
            newNode->previous = tempNode;
            newNode->next = tempNode->next;
            if (tempNode->next != NULL) {
                tempNode->next->previous = newNode;
            }
            tempNode->next = newNode;
            return start;
        }
        tempNode = tempNode->next;
    }
    printf("Item not found\n");
    return start;
}

struct Node* insertBefore(struct Node* start, int item, int data) {
    struct Node* newNode;
    struct Node* tempNode = start;
    if (start == NULL) {
        printf("\nThe list is empty\n");
        return start;
    }
    if (start->value == item) {
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->value = data;
        newNode->next = start;
        start = newNode;
        return start;
    }
    while (tempNode->next != NULL) {
        if (tempNode->next->value == item) {
            newNode = (struct Node*)malloc(sizeof(struct Node));
            newNode->value = data;
            newNode->next = tempNode->next;
            tempNode->next = newNode;
            return start;
        }
        tempNode = tempNode->next;
    }
    printf("\nItem not found\n");
    return start;
}

struct Node* createList(struct Node* start) {
    int numElements, data;
    printf("How many elements would you like to add? ");
    scanf("%d", &numElements);
    if (numElements == 0) {
        return start;
    }
    printf("Enter the first element: ");
    scanf("%d", &data);
    start = initList(start, data);
    for (int i = 1; i < numElements; i++) {
        printf("Enter the next element: ");
        scanf("%d", &data);
        start = insertAtEnd(start, data);
    }
    return start;
}

void printList(struct Node* start) {
    if (start == NULL) {
        printf("\nThe list is empty\n");
        return;
    }
    struct Node* tempNode = start;
    while (tempNode != NULL) {
        printf("%d ", tempNode->value);
        tempNode = tempNode->next;
    }
    printf("\n");
}

int countNodes(struct Node* start) {
    int count = 0;
    for (struct Node* tempNode = start; tempNode != NULL; tempNode = tempNode->next) {
        count++;
    }
    return count;
}

struct Node* search(struct Node* start, int item) {
    struct Node* tempNode = start;
    while (tempNode != NULL) {
        if (tempNode->value == item) {
            return tempNode;
        }
        tempNode = tempNode->next;
    }
    return NULL;
}

struct Node* removeNode(struct Node* start, int data) {
    struct Node* tempNode = start;
    struct Node* prevNode = NULL;
    while (tempNode != NULL) {
        if (tempNode->value == data) {
            if (prevNode != NULL) {
                prevNode->next = tempNode->next;
            } else {
                start = tempNode->next;
            }
            if (tempNode->next != NULL) {
                tempNode->next->previous = prevNode;
            }
            free(tempNode);
            return start;
        }
        prevNode = tempNode;
        tempNode = tempNode->next;
    }
    printf("Element not found\n");
    return start;
}

struct Node* reverseList(struct Node* start) {
    struct Node* tempNode = NULL;
    struct Node* current = start;
    while (current != NULL) {
        tempNode = current->previous;
        current->previous = current->next;
        current->next = tempNode;
        current = current->previous;
    }
    if (tempNode != NULL) {
        start = tempNode->previous;
    }
    return start;
}

struct Node* swapAlternateNodes(struct Node* start) {
    if (start == NULL || start->next == NULL) {
        return start;
    }

    struct Node* tempNode1 = start;
    struct Node* tempNode2 = start->next;
    start = tempNode2;
    struct Node* temp;

    while (1) {
        temp = tempNode2->next;
        tempNode2->next = tempNode1;
        tempNode2->previous = tempNode1->previous;
        tempNode1->previous = tempNode2;
        tempNode1->next = temp;
        if (temp == NULL || temp->next == NULL) {
            break;
        }
        tempNode1->next = temp->next;
        tempNode1 = temp;
        tempNode2 = tempNode1->next;
    }
    return start;
}

int main() {
     printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int option, data, item;
    struct Node* start = NULL;

    do {
        printf("\n\n****** OPTIONS ******\n");
        printf("1. Initialize List\n");
        printf("2. Display List\n");
        printf("3. Count Nodes\n");
        printf("4. Search for Element\n");
        printf("5. Add to Empty List\n");
        printf("6. Insert at Start\n");
        printf("7. Insert at End\n");
        printf("8. Insert After Element\n");
        printf("9. Insert Before Element\n");
        printf("10. Delete an Element\n");
        printf("11. Reverse List\n");
        printf("12. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                start = createList(start);
                break;
            case 2:
                printList(start);
                break;
            case 3:
                printf("Total nodes: %d\n", countNodes(start));
                break;
            case 4:
                printf("Enter the element to search for: ");
                scanf("%d", &item);
                struct Node* searchResult = search(start, item);
                if (searchResult != NULL) {
                    printf("Element found at address %p\n", searchResult);
                } else {
                    printf("Element not found\n");
                }
                break;
            case 5:
                printf("Enter the value to add: ");
                scanf("%d", &data);
                start = initList(start, data);
                break;
            case 6:
                printf("Enter the value to add: ");
                scanf("%d", &data);
                start = insertAtBeginning(start, data);
                break;
            case 7:
                printf("Enter the value to add: ");
                scanf("%d", &data);
                start = insertAtEnd(start, data);
                break;
            case 8:
                printf("Enter the value to add: ");
                scanf("%d", &data);
                printf("Enter the element to insert after: ");
                scanf("%d", &item);
                start = insertAfter(start, data, item);
                break;
            case 9:
                printf("Enter the value to add: ");
                scanf("%d", &data);
                printf("Enter the element to insert before: ");
                scanf("%d", &item);
                start = insertBefore(start, item, data);
                break;
            case 10:
                printf("Enter the element to delete: ");
                scanf("%d", &data);
                start = removeNode(start, data);
                break;
            case 11:
                start = reverseList(start);
                printf("List reversed\n");
                break;
            default:
                printf("Invalid option\n");
                break;
        }
    } while (option != 12);

    return 0;
}
