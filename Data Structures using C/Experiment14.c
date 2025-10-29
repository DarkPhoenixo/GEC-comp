#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *link;
};

struct node *initializeList(struct node *last, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = temp;
    last = temp;
    return last;
}

struct node *insertAtStart(struct node *last, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = last->link;
    last->link = temp;
    return last;
}

struct node *insertAtEnd(struct node *last, int data) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->info = data;
    temp->link = last->link;
    last->link = temp;
    last = temp;
    return last;
}

struct node *insertAfter(struct node *last, int data, int item) {
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    struct node *ptr = last->link;
    do {
        if (ptr->info == item) {
            temp->info = data;
            temp->link = ptr->link;
            ptr->link = temp;
            if (ptr == last) {
                last = temp;
            }
            return last;
        }
        ptr = ptr->link;
    } while (ptr != last->link);
    printf("Item not found\n");
    return last;
}

struct node *insertBefore(struct node *last, int item, int data) {
    struct node *temp, *p;
    if (last == NULL) {
        printf("List is empty\n");
        return last;
    }
    if (last->link->info == item) {
        last = insertAtEnd(last, data);
        return last;
    }
    p = last->link;
    while (p->link != last) {
        if (p->link->info == item) {
            temp = (struct node *)malloc(sizeof(struct node));
            temp->info = data;
            temp->link = p->link;
            p->link = temp;
            return last;
        }
        p = p->link;
    }
    if (last->info == item) {
        last = insertAtEnd(last, data);
        return last;
    }
    printf("Item not found\n");
    return last;
}

struct node *searchElement(struct node *last, int item) {
    struct node *p = last->link;
    do {
        if (p->info == item) {
            return p;
        }
        p = p->link;
    } while (p != last->link);
    return NULL;
}

int getNodeCount(struct node *last) {
    struct node *p = last->link;
    int count = 0;
    do {
        count++;
        p = p->link;
    } while (p != last->link);
    return count;
}

struct node *createCircularList(struct node *last) {
    int n, data;
    last = NULL;
    printf("How many nodes? ");
    scanf("%d", &n);
    if (n == 0) {
        return last;
    }
    printf("Enter first element: ");
    scanf("%d", &data);
    last = initializeList(last, data);
    for (int i = 2; i <= n; i++) {
        printf("Enter next element: ");
        scanf("%d", &data);
        last = insertAtEnd(last, data);
    }
    return last;
}

void displayCircularList(struct node *last) {
    if (last == NULL) {
        printf("List is empty\n");
        return;
    }
    struct node *p = last->link;
    printf("\nCircular Linked List:\n");
    do {
        printf(" %d ->", p->info);
        p = p->link;
    } while (p != last->link);
    printf(" %d (back to start)\n", last->link->info);
}

struct node *deleteNode(struct node *last, int data) {
    if (last == NULL) {
        return last;
    }
    struct node *temp, *p;
    if (last->link == last && last->info == data) {
        temp = last;
        last = NULL;
        free(temp);
        return last;
    }
    if (last->link->info == data) {
        temp = last->link;
        last->link = temp->link;
        free(temp);
        return last;
    }
    p = last->link;
    while (p->link != last) {
        if (p->link->info == data) {
            temp = p->link;
            p->link = temp->link;
            free(temp);
            return last;
        }
        p = p->link;
    }
    if (last->info == data) {
        temp = last;
        p->link = last->link;
        last = p;
        free(temp);
    }
    return last;
}

struct node *reverseList(struct node *last) {
    struct node *prev, *current, *next;
    if (last == NULL) {
        return last;
    }
    prev = last;
    current = last->link;
    do {
        next = current->link;
        current->link = prev;
        prev = current;
        current = next;
    } while (current != last->link);
    last->link = prev;
    last = last->link;
    return last;
}

int main() {
  printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
      
    struct node *last = NULL;
    int option, data, item;

    do {
        printf("\nMenu:\n");
        printf("1. Create Circular List\n");
        printf("2. Show List\n");
        printf("3. Insert at Start\n");
        printf("4. Insert at End\n");
        printf("5. Insert After Element\n");
        printf("6. Insert Before Element\n");
        printf("7. Remove Node\n");
        printf("8. Find Element\n");
        printf("9. Get Node Count\n");
        printf("10. Reverse List\n");
        printf("11. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                last = createCircularList(last);
                break;
            case 2:
                displayCircularList(last);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                last = insertAtStart(last, data);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                last = insertAtEnd(last, data);
                break;
            case 5:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter the element after which to insert: ");
                scanf("%d", &item);
                last = insertAfter(last, data, item);
                break;
            case 6:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter the element before which to insert: ");
                scanf("%d", &item);
                last = insertBefore(last, item, data);
                break;
            case 7:
                printf("Enter data to delete: ");
                scanf("%d", &data);
                last = deleteNode(last, data);
                break;
            case 8:
                printf("Enter data to search: ");
                scanf("%d", &data);
                struct node *foundNode = searchElement(last, data);
                if (foundNode != NULL) {
                    printf("Data found.\n");
                } else {
                    printf("Data not found.\n");
                }
                break;
            case 9:
                printf("Total nodes: %d\n", getNodeCount(last));
                break;
            case 10:
                last = reverseList(last);
                printf("List reversed.\n");
                break;
            case 11:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option! Try again.\n");
        }
    } while (option != 11);

    return 0;
}
