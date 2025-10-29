#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <ctype.h>

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
    tmp->info = tolower(item);  // Convert to lowercase for case-insensitivity
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

int isPalindrome(const char str[]) {
    int i = 0;
    while (str[i] != '\0') {
        push(str[i]);
        i++;
    }

    i = 0;
    while (top != NULL) {
        char ch = pop();
        if (tolower(str[i]) != ch) { // Compare case-insensitively
            return 0;
        }
        i++;
    }

    return 1;
}

int main() {
      printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int choice;

    while (1) {
        printf("\n1. Check if a string is a palindrome\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            char str[100];
            printf("Enter a string: ");
            scanf("%s", str);
            if (isPalindrome(str)) {
                printf("==> %s is a palindrome\n", str);
            } else {
                printf("==> %s is not a palindrome\n", str);
            }
        } else if (choice == 2) {
            break;
        } else {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
