#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int info;
    struct node* link;
};

struct node* front = NULL;
struct node* rear = NULL;




void insert(int data) {
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    if (tmp == NULL) {
        printf("Queue Overflow\n");
        return;
    }
    tmp->info = data;
    tmp->link = NULL;
    if (front == NULL) {
        front = tmp;
    } else {
        rear->link = tmp;
    }
    rear = tmp;
}

int delete() {
    if (front == NULL) {
        printf("Queue Underflow\n");
        return INT_MIN;
    }
    struct node* tmp = front;
    int data = tmp->info;
    front = front->link;
    free(tmp);
    return data;
}


void displayQueue() {
    if (front==NULL)
    {
    printf("\n front           rear\n");
    printf("------          ------\n");
    printf("|NULL|          |NULL|\n");
    printf("------          ------\n\n");
        return;
    }
    printf("\n   front");
    printf("             ");
    for (struct node* i = front; i !=NULL; i=i->link)
    {
        printf("                     ");
    }
    printf("             ");
    printf("rear\n");
    printf("----------");
    printf("             ");
    for (struct node* i = front; i !=NULL; i=i->link)
    {
        printf("                      ");
    }
    printf("       ");
    printf("----------\n");

    printf("|%8p|",front);
     printf("          ");
  
    for (struct node* i = front; i !=NULL; i=i->link)
    {
        printf("                      ");
    }
    printf("          ");
    
    printf("|%8p|\n",rear);
    printf("----------");
    printf("             ");
    for (struct node* i = front; i !=NULL; i=i->link)
    {
        printf("                      ");
    }
    printf("       ");
    printf("----------\n");    printf("     |               ");
    for (struct node* p = front; p !=NULL; p=p->link)
    {
        printf("----------------     ");
    }
    printf("                 |\n");
    printf("     |-------------->");
    

    for (struct node* p =front; p !=NULL; p=p->link)
    {
        if (p->link!=NULL)
        {
            printf("| %3d |%8p|---> ",p->info,p->link);
        }
        else{
            printf("| %3d |%8s| ",p->info,"NULL");

        }
    }
        printf("<--------------------|")
    ;
    printf("\n");
    printf("                     ");
    for (struct node* p = front; p !=NULL; p=p->link)
    {
        printf("----------------     ");
    }
    printf("\n");
    printf("                     ");

    
    for (struct node* p = front; p !=NULL; p=p->link)
    {
        printf("    %8p         ",p);
    }
    printf("\n\n");
}



int main() {
   printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
int choice;
    int data;
    
    while (1) {

        printf("1. Insert element\n");
        printf("2. Delete element\n");
        printf("3. Display queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf(" %d", &data);
                insert(data);
                break;
            case 2:
                data = delete();
                if (data != INT_MIN) {
                    printf("Deleted element: %c\n", data);
                }
                break;
            case 3:
                displayQueue();
                break;
            case 4:
                exit(0);
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
