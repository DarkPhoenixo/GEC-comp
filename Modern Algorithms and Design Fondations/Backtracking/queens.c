#include <stdio.h>
#include <math.h>
#include <time.h>  

#define MAX_N 12
int x[MAX_N + 1];
int solution_count = 0;
int first_solution_shown = 0;

void displayBoard(int n) {
    printf("\n");
    for (int i = 1; i <= n; i++) {
        printf("|");
        for (int j = 1; j <= n; j++) {
            if (x[i] == j)
                printf(" Q ");
            else
                printf(" . ");
        }
        printf("|\n");
    }
    printf("\n");
}

int Place(int k, int i) {
    for (int j = 1; j < k; j++) {
        if (x[j] == i || abs(x[j] - i) == abs(j - k))
            return 0;
    }
    return 1;
} 

void NQueens(int k, int n) {
    for (int i = 1; i <= n; i++) {
        if (Place(k, i)) {
            x[k] = i;
            if (k == n) {
                solution_count++;
                if (!first_solution_shown) {
                    displayBoard(n);
                    first_solution_shown = 1;
                }
            } else {
                NQueens(k + 1, n);
            }
        }
    }
}

void solveNQueens(int n) {
    if (n < 4 || n > MAX_N) {
        printf("Please enter a value between 4 and %d.\n", MAX_N);
        return;
    }
    
    solution_count = 0;
    first_solution_shown = 0;
    
    printf("\n%d-Queens Problem:\n", n);
    printf("One solution:");
    
    // Start timing
    clock_t start = clock();
    
    NQueens(1, n);
    
    // End timing
    clock_t end = clock();
    double time_taken = ((double)(end - start) / CLOCKS_PER_SEC) * 1000000; // Convert to microseconds
    
    printf("Total number of solutions for %d-Queens: %d\n", n, solution_count);
    printf("Time taken: %.2f microseconds\n", time_taken);
    printf("----------------------------------------\n");
}

void displayMenu() {
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    printf("\nN-Queens Problem Solver\n");
    printf("1. Solve for a specific N (4-%d)\n", MAX_N);
    printf("2. Solve for all N from 4 to %d\n", MAX_N);
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    int choice, n;
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter the value of N (4-%d): ", MAX_N);
                scanf("%d", &n);
                solveNQueens(n);
                break;
                
            case 2:
                printf("Solving for all N from 4 to %d:\n", MAX_N);
                for (int i = 4; i <= MAX_N; i++) {
                    solveNQueens(i);
                }
                break;
                
            case 3:
                printf("Exiting program.\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    
    return 0;
}
