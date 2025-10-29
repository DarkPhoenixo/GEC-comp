#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct node {
    char info;
    struct node* link;
};

struct node* top = NULL;

void push(char item) {
    struct node* tmp = (struct node*)malloc(sizeof(struct node));
    if (tmp == NULL) {
        printf("Stack Overflow\n");
        return;
    }
    tmp->info = item;
    tmp->link = top;
    top = tmp;
}

char pop() {
    if (top == NULL) {
        printf("Stack Underflow\n");
        return CHAR_MIN;
    }
    char item = top->info;
    struct node* p = top;
    top = top->link;
    free(p);
    return item;
}

int isValidParentheses(const char inp[]) {
    for (int i = 0; inp[i] != '\0'; i++) {
        if (inp[i] == '(' || inp[i] == '[' || inp[i] == '{') {
            push(inp[i]);
        } else if (inp[i] == ')' || inp[i] == ']' || inp[i] == '}') {
            if (top == NULL) {
                return 0;
            }
            char topChar = pop();
            if ((topChar == '(' && inp[i] != ')') ||
                (topChar == '[' && inp[i] != ']') ||
                (topChar == '{' && inp[i] != '}')) {
                return 0;
            }
        }
    }
    return top == NULL;
}

int main() {
      printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int choice;

    while (1) {
        printf("\n1. Check valid parentheses\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char inp[100];
            printf("Enter a string: ");
            scanf("%s", inp);
            if (isValidParentheses(inp)) {
                printf("==> %s has valid parentheses\n", inp);
            } else {
                printf("==> %s does not have valid parentheses\n", inp);
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
