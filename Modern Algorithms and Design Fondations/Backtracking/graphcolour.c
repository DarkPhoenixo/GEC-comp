#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>

#define MAX 20

int n, m;
int x[MAX], G[MAX][MAX];
int solution_count = 0;
int nodeCount = 0;
int solutions[MAX][MAX]; 

void print_current_state(int k, const char *state) {
    printf("\n%s ", state);
    for (int i = 1; i <= k; i++) {
        printf("x%d=%d ", i, x[i]);
    }
    printf("\n\n");
}

void NextValue(int k) {
    int j;
    while (1) {
        x[k] = (x[k] + 1) % (m + 1);
        if (x[k] == 0) {
            return;
        }
        for (j = 1; j <= n; j++) {
            if (G[k][j] && x[k] == x[j]) {
                print_current_state(k, "Bounded");
                break;
            }
        }
        if (j == n + 1) {
            return;
        }
    }
}

void mColoring(int k) {
    while (1) {
        NextValue(k);
        if (x[k] == 0) {
            return; 
        }
        if (k == n) {
            solution_count++;
            printf("Solution %d: ", solution_count);
            for (int i = 1; i <= n; i++) {
                printf("x%d=%d ", i, x[i]);
                solutions[solution_count - 1][i - 1] = x[i]; 
            }
            printf("\n");
        } else {
            mColoring(k + 1);
        }
    }
}

void printSolutionMatrix() {
    printf("\nSolution Matrix:\n");
    for (int i = 0; i < solution_count; i++) {
        printf("%c: x[1..%d] = {", 'A' + i, n);
        for (int j = 0; j < n; j++) {
            printf("%d", solutions[i][j]);
            if (j < n - 1) {
                printf(", ");
            }
        }
        printf("}\n");
    }
}

void inputGraph() {
    printf("Enter number of vertices (n, max 20): ");
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            G[i][j] = 0;
        }
    }

    printf("Enter the adjacency matrix (1 for edge, 0 for no edge):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("Edge between %d and %d (1/0): ", i, j);
            scanf("%d", &G[i][j]);
        }
    }
}

int main() {
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    int choice;

    do {
        printf("\n=== GRAPH COLORING ALGORITHM ===\n");
        printf("1. Input Graph\n");
        printf("2. Set Number of Colors\n");
        printf("3. Display All m-Colorings (DFS Order)\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputGraph();
                break;
            case 2:
                printf("Enter the number of colors (m): ");
                scanf("%d", &m);
                break;
            case 3:
                if (n == 0 || m == 0) {
                    printf("Please input graph and set number of colors first.\n");
                } else {
                    for (int i = 1; i <= n; i++) x[i] = 0;
                    solution_count = 0;

                    LARGE_INTEGER frequency, start, end;
                    QueryPerformanceFrequency(&frequency);
                    QueryPerformanceCounter(&start);

                    printf("ALGORITHM ):\n");
                    mColoring(1);

                    QueryPerformanceCounter(&end);
                    double elapsedTime = (double)(end.QuadPart - start.QuadPart) * 1000000.0 / frequency.QuadPart;

                    if (solution_count == 0) {
                        printf("No valid colorings found.\n");
                    }
                    if (solution_count == 0) {
                        printf("No solutions available..\n");
                    } else {
                        printSolutionMatrix();
                    }

                    printf("\nExecution Time: %.2f microseconds\n", elapsedTime);
                }
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 5);

    return 0;
}
