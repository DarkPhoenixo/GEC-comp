#include <stdio.h>
#include <time.h>

void display_matrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
       printf("| ");
        for (int j = 0; j < 2; j++) {
            printf("%d   ", matrix[i][j]);
        }
         printf("| ");
        printf("\n");
    }
}


void strassen_multi(int a[2][2], int b[2][2], int c[2][2]) {
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int p, q, r, s, t, u, v;

    p = (a[0][0] + a[1][1]) * (b[0][0] + b[1][1]);
    q = (a[1][0] + a[1][1]) * b[0][0];
    r = a[0][0] * (b[0][1] - b[1][1]);
    s = a[1][1] * (b[1][0] - b[0][0]);
    t = (a[0][0] + a[0][1]) * b[1][1];
    u = (a[1][0] - a[0][0]) * (b[0][0] + b[0][1]);
    v = (a[0][1] - a[1][1]) * (b[1][0] + b[1][1]);
   printf ( " P = %d \n Q = %d \n R = %d \n S = %d \n T = %d \n U = %d \n V = %d \n", p, q, r, s, t, u, v);
    c[0][0] = p + s - t + v;
    c[0][1] = r + t;
    c[1][0] = q + s;
    c[1][1] = p - q + r + u;

    printf ( " The result of matrix multiplication is : \n");
    display_matrix(c);

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by Strassen's matrix multiplication: %f seconds\n", cpu_time_used);
}


void input_matrix(int matrix[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("Enter the element at position (%d, %d): ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}

int main() {

          printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

    int a[2][2], b[2][2], c[2][2];
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input matrices\n");
        printf("2. Multiply matrices using Strassen's algorithm\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Input matrix A:\n");
                input_matrix(a);
                printf("Input matrix B:\n");
                input_matrix(b);
                break;
            case 2:
                strassen_multi(a, b, c);
                printf("Matrices multiplied successfully.\n");
                break;
            case 3:
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
