#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *link;
};

struct node *createlist(struct node *point) {
    int n, data;
    printf("Enter the number of nodes\n");
    scanf("%d", &n);
    point = NULL;
    if (n == 0) {
        return point;
    }

    printf("Enter the element to be inserted\n");
    scanf("%d", &data);
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;
    p->link = NULL;
    point = p;
    struct node *last = p;

    for (int i = 2; i <= n; i++) {
        printf("Enter the element to be inserted\n");
        scanf("%d", &data);
        struct node *p = (struct node *)malloc(sizeof(struct node));
        p->info = data;
        p->link = NULL;
        last->link = p;
        last = p;
    }

    return point;
}

void display(struct node *point) {
    if (point == NULL) {
        printf("The list is empty\n");
        return;
    }
    struct node *p = point;
    int i = 0;
    while (p != NULL) {
        i++;
        printf("%d ", p->info);
        p = p->link;
    }
    printf("\n");
}

void count(struct node *point) {
    int i = 0;
    struct node *p = point;
    while (p != NULL) {
        i++;
        p = p->link;
    }
    printf("There are %d nodes in the list\n", i);
}

struct node *addatbeg(struct node *start, int data)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;
    p->link = start;
    start = p;
    return start;
}

struct node *addatend(struct node *start, int data)
{
    struct node *p = (struct node *)malloc(sizeof(struct node));
    p->info = data;
    p->link = NULL;
    if (start == NULL)
    {
        start = p;
        return start;
    }
    struct node *ptr = start;
    while (ptr->link != NULL)
    {
        ptr = ptr->link;
    }
    ptr->link = p;
    return start;
}

struct node *Union(struct node *point, struct node *start) {
    struct node *p = point;
    struct node *uni = NULL;
    while (p != NULL) {
        uni = addatend(uni, p->info);
        p = p->link;
    }
    struct node *q = start;
    while (q != NULL) {
        struct node *temp = uni;
        int found = 0;
        while (temp != NULL) {
            if (temp->info == q->info) {
                found = 1;
                break;
            }
            temp = temp->link;
        }
        if (!found) {
            uni = addatend(uni, q->info);
        }
        q = q->link;
    }
    return uni;
}

struct node *intersection(struct node *point, struct node *start) {
    struct node *p = point;
    struct node *q = start;
    struct node *intersec = NULL;

    while (q != NULL) {
        struct node *temp = p;
        int found = 0;
        while (temp != NULL) {
            if (temp->info == q->info) {
                found = 1;
                break;
            }
            temp = temp->link; }
        if (found) {
            intersec = addatend(intersec, q->info); }
    q = q->link;
    }
    return intersec;
}

struct node *differ(struct node *point, struct node *start) {
    struct node *p = point;
    struct node *diff = NULL;

    while (p != NULL) {
        struct node *temp = start;
        int found = 0;
        while (temp != NULL) {
            if (temp->info == p->info) {
                found = 1;
                break;
            }
            temp = temp->link;
        }
        if (!found) {
            diff = addatend(diff, p->info);
        }
        p = p->link;
    }
    return diff;
}

int main() {
    struct node *point = NULL;
    struct node *start = NULL;
    struct node *uni = NULL ;
    struct node *intersect = NULL ;
    struct node *difference = NULL ;
    
    printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int option;

    do {
        printf("\nEnter the type of operation you want to perform on the first list\n");
        printf("1. Create a list\n");
        printf("2. Display the list\n");
        printf("3. Count the elements of the list\n");
        printf("4. Quit\n");
        printf("Enter your choice number\n");
        scanf("%d", &option);

        switch (option) {
        case 1:
            point = createlist(point);
            break;
        case 2:
            printf("The linked list:\n");
            display(point);
            break;
        case 3:
            count(point);
            break;
        case 4:
            break;
        default:
            printf("Enter a valid option\n");
            break;
        }
    } while (option != 4);

    option = 0; 
    do {
        printf("\nEnter the type of operation you want to perform on the second list\n");
        printf("1. Create a list\n");
        printf("2. Display the list\n");
        printf("3. Count the number of nodes in the list\n");
        printf("4. Quit\n");
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
            break;
        default:
            printf("Enter a valid option\n");
            break;
        }
    } while (option != 4);

    printf("The first list is \n");
    display(point);
    printf("\nThe second list is \n");
    display(start);

    printf("\nThe union of two lists is \n");
    uni = Union(point, start);
    display(uni);

    printf("\nThe intersection of two lists is \n");
    intersect = intersection(point, start);
    display(intersect);

    printf("\nThe difference of two lists is \n");
    difference = differ(point, start);
    display(difference);

    return 0;
}