

#include <stdio.h>
#include <stdlib.h>
#define MAX 4
int top = -1 ;
int stack_arr[MAX] ;

int isFull(){
if(top==MAX-1){
    return 1 ;
} return 0 ;
}
int isEmpty(){
if(top==-1){
    return 1 ;
} return 0 ;
}

void push (int data){
    if (isFull()){
        printf ("Stack Overflow\n") ;
        return ;
    }
    top++ ;
    stack_arr[top] = data ;
    return ;
}

int pop (){
    if (isEmpty()){
        printf ("Stack Underflow\n") ;
      exit(1);
    }
    int data = stack_arr[top] ;
    top-- ;
    return data ;
}

int peek (){
    if (isEmpty()){
        printf ("Stack Underflow\n") ;
      exit(1);
    }
    return stack_arr[top];
}

void display (){
 if (isEmpty()){
        printf ("Stack Empty\n") ;
      return;}
      printf ("The elements of the stack are \n") ;
for (int i=top;i>=0;i--){
printf (" %d \n",stack_arr[i]) ;

}

}

int main () {
       printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
 int option,data;
    do {
        printf("\nEnter the type of operation you want to perform on the list\n");
        printf("1. Push a element in the stack\n");
        printf("2. Pop a element in the stack\n");
        printf("3. Peek the top element\n");
        printf("4. Display the stack elements\n");
        printf("5. Quit\n");
        printf("Enter your choice number\n");
        scanf("%d", &option);

        switch (option) {
        case 1:
        printf("Enter the data to push\n") ;
        scanf("%d",&data);
         push(data) ;
            break;
        case 2:
          pop ();
            break;
        case 3:
            peek();
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
    }while (option!=5) ;


    return 0 ;
}