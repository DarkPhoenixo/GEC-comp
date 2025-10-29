#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MAX 20

int x[MAX], G[MAX][MAX], n;
int solutionCount = 0;
int solutions[MAX][MAX];

long long getMicrotime() {
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000000) / frequency.QuadPart;
}

void printCurrentState(int k, const char *state) {
    printf("\n%s ", state);
    for (int i = 1; i <= k; i++) {
        printf("x%d=%d ", i, x[i]);
    }
    printf("\n");
}

void displaySolutionMatrix() {
    printf("\nSolution Matrix:\n");
    for (int i = 0; i < solutionCount; i++) {
        printf("%c = {", 'A' + i, n);
        for (int j = 0; j < n; j++) {
            printf("%d", solutions[i][j]);
            if (j < n - 1) {
                printf(", ");
            }
        }
        printf(", 1}\n");
    }
}

void NextValue(int k) {
    int j;
    while (1) {
        x[k] = (x[k] + 1) % (n + 1);
        if (x[k] == 0) {
            printCurrentState(k, "Bounded: No valid vertex available");
            return;
        }
       
        if (G[x[k - 1]][x[k]] != 0) {
            for (j = 1; j < k; j++) {
                if (x[j] == x[k]) break;
            }
            if (j == k) {
                if ((k < n) || (k == n && G[x[n]][x[1]] != 0)) {
                    return;
                } else if (k == n) {
                    printCurrentState(k, "Bounded: No edge back to starting vertex");
                }
            } else {
                printCurrentState(k, "Bounded: Vertex already in path");
            }
        } else {
        }
    }
}



void Hamiltonian(int k) {
    while (1) {
        NextValue(k);
        if (x[k] == 0) return;
        if (k == n) {
            solutionCount++;
            printf("\nSolution %d found: ", solutionCount);
            for (int i = 1; i <= n; i++) {
                printf("%d ", x[i]);
                solutions[solutionCount - 1][i - 1] = x[i];
            }
            printf("%d\n", x[1]);
        } else {
            Hamiltonian(k + 1);
        }
    }
}

void inputGraph() {
    printf("Enter number of vertices (n, max %d): ", MAX - 1);
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

void displayGraph() {
    printf("\nAdjacency Matrix:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%d ", G[i][j]);
        }
        printf("\n");
    }
}

int main() {
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    int choice;

    do {
        printf("\n=== HAMILTONIAN CYCLE FINDER ===\n");
        printf("1. Input Graph\n");
        printf("2. Display Graph\n");
        printf("3. Find All Hamiltonian Cycles\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                inputGraph();
                for (int i = 1; i <= n; i++) x[i] = 0;
                x[1] = 1;
                solutionCount = 0;
                break;
            case 2:
                if (n == 0) {
                    printf("Please input a graph first.\n");
                } else {
                    displayGraph();
                }
                break;
            case 3:
                if (n == 0) {
                    printf("Please input a graph first.\n");
                } else {
                    printf("\nSearching for Hamiltonian cycles...\n");
                    printf("Starting with vertex 1\n");
                    solutionCount = 0;

                    long long startTime = getMicrotime();
                    Hamiltonian(2);
                    long long endTime = getMicrotime();

                    if (solutionCount == 0) {
                        printf("No Hamiltonian cycles found in the graph.\n");
                    } else {
                        printf("Total Hamiltonian cycles found: %d\n", solutionCount);
                    }
                    printf("Time taken: %lld microseconds\n", endTime - startTime);
                }
                  if (solutionCount == 0) {
                    printf("No solutions available. Please find solutions first.\n");
                } else {
                    displaySolutionMatrix();
                }
                break;
            case 4:
                printf("Exiting program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
