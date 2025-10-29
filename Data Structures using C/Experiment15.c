#include <stdio.h>
#include <stdlib.h>

struct node {
    int info;
    struct node *link;
};

// Function to add the first node to an empty list
struct node* addFirstNode(struct node* last, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    last = temp;
    temp->info = data;
    temp->link = last; // Points to itself in a single-node list
    return last;
}

// Function to add a new node at the end of the list
struct node* addNodeAtEnd(struct node* last, int data) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if (temp == NULL) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    temp->info = data;
    temp->link = last->link;
    last->link = temp;
    last = temp;
    return last;
}

// Function to create a list with multiple nodes
struct node* createList(struct node* last) {
    int data, numberOfNodes;
    printf("Enter the number of nodes to insert: ");
    scanf("%d", &numberOfNodes);
    for (int i = 0; i < numberOfNodes; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);
        if (last == NULL) {
            last = addFirstNode(last, data);
        } else {
            last = addNodeAtEnd(last, data);
        }
    }
    return last;
}

// Function to display the list in circular format
void displayCLL(struct node *last)
{
    if (last == NULL)
    {
        printf("\n last\n");
        printf("------\n");
        printf("|NULL|\n");
        printf("------\n");
        return;
    }
    struct node *p = last->link;
    printf("\n");

    p = last->link;
    do
    {
        printf("                     ");
        p = p->link;
    } while (p != last->link);

    printf("   last\n");

    p = last->link;
    do
    {
        printf("                     ");

        p = p->link;
    } while (p != last->link);
    printf("----------\n");

    p = last->link;
    do
    {
        if(p==last){
            printf("             |-------");
        }
        else
            printf("                     ");

        p = p->link;
    } while (p != last->link);

    printf("|%8p|\n", last);

    p = last->link;
    do
    {
        if(p==last){
            printf("             V       ");
        }
        else
            printf("                     ");

        p = p->link;
    } while (p != last->link);
    printf("----------\n");
    

    printf("      ");
    p = last->link;
    do
    {
        printf("----------------     ");
        p = p->link;
    } while (p != last->link);
    printf("\n");

    printf("  |-->");
    p = last->link;
    do
    {
        if (p == last)
        {
            printf("| %3d |%8p|------", p->info, p->link);
        }
        else
        {
            printf("| %3d |%8p|---> ", p->info, p->link);
        }
        p = p->link;
    } while (p != last->link);
    printf("|");
    printf("\n");
   

    printf("  |   ");
    p = last->link;
    do
    {
        printf("----------------     ");
        p = p->link;
    } while (p != last->link);
    printf(" |");

    printf("\n");
    printf("  |    ");
    p = last->link;
    do
    {
        printf("   %8p          ", p);
        p = p->link;
    } while (p != last->link);
    printf("|");
    printf("\n");
    printf("  |___");
    p = last->link;
    do
    {
        printf("_____________________", p);
        p = p->link;
    } while (p != last->link);
    printf("_|");
    printf("\n\n");
}

// Function to delete every alternate node from the list
struct node* deleteAlternateNodes(struct node* last) {
    if (last == NULL || last->link == last) {
        return last; // Empty list or single-node list
    }

    struct node *ptr = last->link;
    struct node *tmp;

    while (ptr != last && ptr->link != last) {
        tmp = ptr->link; 
        ptr->link = tmp->link; 
        free(tmp); 
        ptr = ptr->link;
    }

    if (ptr->link == last) {
        tmp = last;
        ptr->link = last->link;
        free(tmp);
        last = ptr;
    }

    return last;
}

// Function to delete a node with specific data
struct node* deleteNode(struct node* last, int data) {
    if (last == NULL) {
        return last;
    }
    struct node* tmp,*p;
    if(last == last->link && last->info == data){
        tmp = last;
        last = NULL;
        free(tmp);
        return last;}
    if(last->link->info == data){
        tmp = last->link;
        last->link = tmp->link;
        free(tmp);
        return last; }
    p = last->link;
    while (p->link != last) {
        if (p->link->info == data) {
            tmp = p->link;
            p->link = tmp->link;
            free(tmp);
            return last; }
        p = p->link;}
    if (last->info == data) {
        tmp = last;
        p->link = last->link;
        last = p;
        free(tmp);}
    return last;
}

struct node* deleteList(struct node* last) {
    struct node *ptr = last->link;
    struct node *tmp;
    while (ptr != last) {
        tmp = ptr;
        ptr = ptr->link;
        free(tmp); }
    free(last);
    last = NULL;
    return last;}

int main() {
      printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int choice, data;
    struct node* last = NULL;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert multiple nodes\n");
        printf("2. Display list\n");
        printf("3. Delete alternate nodes\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                last = createList(last);
                break;
            case 2:
            printf("*******************************\n");
            printf("Circular Linked List\n");
            printf("*******************************\n\n\n");
                printf("\nList:\n");
                displayCLL(last);
                break;
            case 3:
            printf("\nCircular Linked list before deleting alternate nodes:\n");
               displayCLL(last);
                 last = deleteAlternateNodes(last);
                printf("\nCircular Linked list after deleting alternate nodes:\n");
                displayCLL(last);
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

