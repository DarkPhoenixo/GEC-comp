#include <stdio.h>

int main() {
    int n, first = 0, second = 1, next, i = 0;

    printf("Enter the number of terms: ");
    scanf("%d", &n);

    printf("Fibonacci Series: ");

    if (n <= 0) {
        printf("Invalid input. Please enter a positive integer greater than 0.\n");
        goto last;
    }

    if (n == 1) {
        printf("%d", first);
        goto last;
    }

    if (n == 2) {
        printf("%d %d", first, second);
        goto last;
    }

    printf("%d %d ", first, second);

next_term:
    next = first + second;
    first = second;
    second = next;
    printf("%d ", next);

    i++;
    if (i < n - 2)
        goto next_term;

last:
    return 0;
}






