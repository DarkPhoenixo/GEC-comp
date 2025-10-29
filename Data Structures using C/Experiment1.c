#include <stdio.h>
#include <stdlib.h>

struct node
{
    int info;
    struct node *link;
};

struct node *createlist(struct node *start)
{
    int n, data;
    printf("Enter the number of nodes\n");
    scanf("%d", &n);
    start = NULL;
    if (n == 0)
    {
        return start;
    }

    printf("Enter the element to be inserted\n");
    scanf("%d", &data);
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;
    p->link = NULL;
    start = p;
    struct node *last = p;

    for (int i = 2; i <= n; i++)
    {
        printf("Enter the element to be inserted\n");
        scanf("%d", &data);
        struct node *p = (struct node *)malloc(sizeof(struct node));
        p->info = data;
        p->link = NULL;
        last->link = p;
        last = p;
    }

    return start;
}

void display(struct node *start)
{
    if (start == NULL)
    {
        printf("The list is empty\n");
        return;
    }
    struct node *p = start;
    int i = 0;
    while (p != NULL)
    {
        i++;
        printf("Element %d = %d\n", i, p->info);
        p = p->link;
    }
}

void count(struct node *start) {
    int i = 0;
    struct node *p = start;
    while (p != NULL)
    {
        i++;
        p = p->link;
    }
    printf("There are %d nodes in the list\n", i);
}

void search(struct node *start) {
    int i = 0, data;
    printf("Enter the element you want to search\n");
    scanf("%d", &data);
    struct node *p = start;
    while (p != NULL)
    {
        i++;
        if (p->info == data) {
            printf("The element %d found at position %d node\n", data, i);
            return;
        }
        p = p->link;
    }
    printf("The element %d doesn't exist in the list\n", data);
}

struct node *addatbeg(struct node *start) {
    int data;
    printf("Enter the element you want to add\n");
    scanf("%d", &data);
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;
    p->link = start;
    start = p;
    return start;
}

struct node *addatend(struct node *start) {
    int data;
    printf("Enter the element you want to add\n");
    scanf("%d", &data);
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;
    p->link = NULL;
    if (start == NULL) {
        start = p;
        return start;
    }
    struct node *ptr = start;
    while (ptr->link != NULL) {
        ptr = ptr->link;
    }
    ptr->link = p;
    return start;
}

struct node *addafternode(struct node *start) {
    int data, pos;
    printf("Enter the element you want to add and the position you want to add the data at\n");
    scanf("%d%d", &data, &pos);
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;

    struct node *ptr = start;
    for (int i = 1; i < pos && ptr != NULL; i++) {
        ptr = ptr->link;
    }
    if (ptr == NULL) {
        printf("The position %d doesn't exist in the list\n", pos);
        free(p);
    } else {
        p->link = ptr->link;
        ptr->link = p;
    }
    return start;
}

struct node *addbefore(struct node *start) {
    int data, val;
    printf("Enter the element you want to add and the value before which to add\n");
    scanf("%d%d", &data, &val);

    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;

    if (start == NULL) {
        printf("The list is empty\n");
        free(p);
        return start;
    }

    if (start->info == val) {
        p->link = start;
        start = p;
        return start;
    }

    struct node *ptr = start;
    while (ptr->link != NULL && ptr->link->info != val) {
        ptr = ptr->link;
    }

    if (ptr->link == NULL) {
        printf("The element %d doesn't exist in the list\n", val);
        free(p);
    } else {
        p->link = ptr->link;
        ptr->link = p;
    }

    return start;
}

struct node *addatpos(struct node *start) {
    int data, pos;
    printf("Enter the element you want to add and the position you want to add the data at\n");
    scanf("%d%d", &data, &pos);
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;

    if (pos == 1) {
        p->link = start;
        start = p;
        return start;
    }

    struct node *ptr = start;
    for (int i = 1; i < pos - 1 && ptr != NULL; i++) {
        ptr = ptr->link;
    }

    if (ptr == NULL) {
        printf("The position %d doesn't exist in the list\n", pos);
        free(p);
    } else {
        p->link = ptr->link;
        ptr->link = p;
    }

    return start;
}

struct node *deleteavalue(struct node *start) {
    int value;
    printf("Enter the element you want to delete\n");
    scanf("%d", &value);
    struct node *p, *q;
    if (start == NULL) {
        printf("The list is empty\n");
        return start;
    }
    if (start->info == value) {
        struct node *ptr = start;
        start = start->link;
        free(ptr);
        return start;
    }
    p = start;
    q = start->link;
    while (q != NULL) {
        if (q->info == value) {
            p->link = q->link;
            free(q);
            return start;
        }
        p = q;
        q = q->link;
    }
    printf("The element %d doesn't exist in the list\n", value);
    return start;
}

struct node *reversal(struct node *start) {
    if (start == NULL) {
        printf("The list is empty\n");
        return start;
    }
    struct node *prev = NULL, *current = start, *link = NULL;
    while (current != NULL) {
        link = current->link;
        current->link = prev;
        prev = current;
        current = link;
    }
    start = prev;
    return start;
}

int main() {
     printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    
    struct node *start = NULL;
    int option;
    do {
        printf("\nEnter the type of operation you want to perform on the list\n");
        printf("1. Create a list\n");
        printf("2. Display the list\n");
        printf("3. Count the number of nodes in the list\n");
        printf("4. Search an element in the list\n");
        printf("5. Insert an element in the beginning\n");
        printf("6. Insert an element after a node\n");
        printf("7. Insert the element at the end of the list\n");
        printf("8. Insert an element before a node\n");
        printf("9. Insert an element at a given position\n");
        printf("10. Delete an element from the list\n");
        printf("11. Reverse the list\n");
        printf("12. Quit\n");
        printf("Enter your choice number\n");
        scanf("%d", &option);

        switch (option) {
        case 1:
            start = createlist(start);
            break;
        case 2:
            printf("The linked list:\n");
            display(start);
            break;
        case 3:
            count(start);
            break;
        case 4:
            search(start);
            break;
        case 5:
            printf("The linked list before addition:\n");
            display(start);
            start = addatbeg(start);
            printf("The linked list after addition:\n");
            display(start);
            break;
        case 6:
            printf("The linked list before addition:\n");
            display(start);
            start = addafternode(start);
            printf("The linked list after addition:\n");
            display(start);
            break;
        case 7:
            printf("The linked list before addition:\n");
            display(start);
            start = addatend(start);
            printf("The linked list after addition:\n");
            display(start);
            break;
        case 8:
            printf("The linked list before addition:\n");
            display(start);
            start = addbefore(start);
            printf("The linked list after addition:\n");
            display(start);
            break;
        case 9:
            printf("The linked list before addition:\n");
            display(start);
            start = addatpos(start);
            printf("The linked list after addition:\n");
            display(start);
            break;
        case 10:
            printf("The linked list before deletion:\n");
            display(start);
            start = deleteavalue(start);
            printf("The linked list after deletion:\n");
            display(start);
            break;
        case 11:
            printf("The linked list before reversal:\n");
            display(start);
            start = reversal(start);
            printf("The linked list after reversal:\n");
            display(start);
            break;
        case 12:
            break;
        default:
            printf("Enter a valid option\n");
            break;
        }
    }while (option!=12) ;

    return 0;
}