# include<stdio.h>
#include<limits.h>
#include<stdlib.h>

struct node{
    int info;
    struct node* link;
};

struct node* top=NULL;

void push(int item){
    struct node* tmp;
    tmp=(struct node *)malloc(sizeof(struct node));
    if (tmp==NULL)
    {
        printf("Stack Overflow\n");
        return;
    }
    tmp->info=item;
    tmp->link=top;
    top=tmp;
}

int pop(){
    if (top==NULL)
    {
        printf("Stack Underflow\n");
        return INT_MIN;
    }
    int item=top->info;
    struct node*p=top;
    top=top->link;
    free(p);
    return item;
}

int peek(){
    if (top==NULL)
    {
        printf("Stack Underflow\n");
        return INT_MIN;
    }
    return top->info;
}

void display(){
    if (top==NULL)
    {
        printf("Stack Empty\n");
        return;
    }

    printf("     ----------   ");

    for (struct node* p = top; p !=NULL; p=p->link)
    {
        printf(" -------------      ");
    }
    printf("\n");
    printf("start|%8u|-->",top);

    for (struct node* p = top; p !=NULL; p=p->link)
    {
        if (p->link!=NULL)
        {
            printf("|%3d||%u|---> ",p->info,p->link);
        }
        else{
            printf("|%3d||%8s| ",p->info,"NULL");

        }

    }
    printf("\n");

        printf("     ----------   ");

    for (struct node* p = top; p !=NULL; p=p->link)
    {
        printf(" -------------      ");
    }
    printf("\n");
    printf("                   ");

    for (struct node* p = top; p !=NULL; p=p->link)
    {
        printf("   %8u         ",p);
    }
    printf("\n");
    
}

int main(){
      printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int choice, item;
    while (1)
    {
        printf ("*****MENU******\n") ;
        printf("1. Push");
        printf("\n2. Pop");
        printf("\n3. Peek");
        printf("\n4. Display");
        printf("\n5. Exit");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("\nEnter the element to push: ");
            scanf("%d", &item);
            push(item);
            break;
        case 2:
            item = pop();
            if (item != INT_MIN)
                printf("\nPopped element: %d", item);
            break;
        case 3:
            item = peek();
            if (item != INT_MIN)
                printf("\nTop element: %d", item);
            break;
        case 4:
            display();
            break;
        case 5:
            exit(0);
        default:
            printf("\nInvalid choice! Please enter a valid option.");
        }
    }



return 0;
}