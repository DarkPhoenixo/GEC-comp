#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100
#define INF 99999 
#define INFINITY INF

int p[MAX][MAX];

void printMatrixWithChanges(int n, int A[MAX][MAX], int prev[MAX][MAX], char* title) {
    printf("%s\n", title);
    
    printf("%-3s| ", title);
    for (int j = 1; j <= n; j++) {
        printf("%-3d ", j);
    }
    printf("\n");
    
    printf("---|");
    for (int j = 1; j <= n; j++) {
        printf("----");
    }
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("%-3d| ", i);
        for (int j = 1; j <= n; j++) {
            if (A[i][j] >= INF) {
                printf("INF ");
            } 
            else if (prev != NULL && A[i][j] != prev[i][j]) {
                printf("[%-2d] ", A[i][j]);
            } 
            else {
                printf("%-3d ", A[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void printPMatrix(int n, int p[MAX][MAX], int k) {
    char title[10];
    sprintf(title, "P%d", k);
    
    printf("%s\n", title);
    
    printf("%-3s| ", title);
    for (int j = 1; j <= n; j++) {
        printf("%-3d ", j);
    }
    printf("\n");
    
    printf("---|");
    for (int j = 1; j <= n; j++) {
        printf("----");
    }
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("%-3d| ", i);
        for (int j = 1; j <= n; j++) {
            if (p[i][j] == -1) {
                printf("-   ");
            } else {
                printf("%-3d ", p[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

void allPaths(int n, int cost[MAX][MAX], int A[MAX][MAX], int p[MAX][MAX]) {
    int prev[MAX][MAX];
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
    // Initialize A⁰ with the cost matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A[i][j] = cost[i][j];
            if (i == j) {
                p[i][j] = -1;
            } else if (cost[i][j] < INF) {
                p[i][j] = i;
            } else {
                p[i][j] = -1;
            }
        }
    }
    
    printMatrixWithChanges(n, A, NULL, "A0");
    printPMatrix(n, p, 0);
    
    // Floyd-Warshall algorithm
    for (int k = 1; k <= n; k++) {
        // Save previous matrix for highlighting changes
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                prev[i][j] = A[i][j];
            }
        }
        
        // Update distances
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i][k] < INF && A[k][j] < INF) {
                    int newDist = A[i][k] + A[k][j];
                    if (newDist < A[i][j]) {
                        A[i][j] = newDist;
                        p[i][j] = p[k][j];
                    }
                }
            }
        }
        
        // Print matrix with changes highlighted
        char title[10];
        sprintf(title, "A%d", k);
        printMatrixWithChanges(n, A, prev, title);
        printPMatrix(n, p, k);
    }
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nAllPaths algorithm execution time: %f seconds\n", cpu_time_used);
}




char *getPath(int p[MAX][MAX], int i, int j) {
    if (i == j) {
        char *path = (char *)malloc(10 * sizeof(char)); 
        sprintf(path, "%d", i);
        return path;
    }
    if (p[i][j] == -1) {
        char *path = (char *)malloc(10 * sizeof(char));
        sprintf(path, "No path");
        return path;
    }
    char *intermediatePath = getPath(p, i, p[i][j]);
    char *path = (char *)malloc((strlen(intermediatePath) + 10) * sizeof(char));      
    sprintf(path, "%s->%d", intermediatePath, j);
    free(intermediatePath);
    return path;
}


// Function definition for AllPair algorithm
void AllPair(int cost[MAX][MAX], int A[MAX][MAX], int p[MAX][MAX], int n) {
    // Initialize p matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j || cost[i][j] == INF)
                p[i][j] = -1;
            else
                p[i][j] = i;
        }
    }
    
    // Floyd-Warshall algorithm
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (A[i][k] < INF && A[k][j] < INF && A[i][k] + A[k][j] < A[i][j]) {
                    A[i][j] = A[i][k] + A[k][j];
                    p[i][j] = p[k][j];
                }
            }
        }
    }
}

void runAllPair(int n, int cost[MAX][MAX]) {
    int A[MAX][MAX], p[MAX][MAX];
    
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
    // Initialize A with the cost matrix
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            A[i][j] = cost[i][j];
        }
    }
    
    AllPair(cost, A, p, n);
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("\nAllPair algorithm execution time: %f seconds\n", cpu_time_used);
}

void inputGraph(int *n, int cost[MAX][MAX]) {
    printf("Enter number of vertices (n, max %d): ", MAX-1);
    scanf("%d", n);
    
    printf("\nEnter the cost matrix (%d for infinity):\n", INF);
    
    for (int i = 1; i <= *n; i++) {
        for (int j = 1; j <= *n; j++) {
            printf("cost[%d][%d]: ", i, j);
            scanf("%d", &cost[i][j]);
            if (i == j) cost[i][j] = 0;  // Diagonal is 0
        }
    }
}

void displayMenu() {
    printf("\n===== AllPaths Algorithm Menu =====\n");
    printf("1. Input Graph\n");
    printf("2. Run AllPaths Algorithm\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
}

void printHeader() {
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    printf(" All-Pairs Shortest Path\n");
    printf("============================================\n");
}

int main() {
    int n = 0;
    int cost[MAX][MAX];
    int A[MAX][MAX];
    int p[MAX][MAX];
    int choice;
    int graphEntered = 0;
    
    printHeader();
    
    do {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                inputGraph(&n, cost);
                graphEntered = 1;
                break;
            case 2:
                if (graphEntered) {
                    printf("\nRunning AllPaths algorithm...\n\n");
                    allPaths(n, cost, A, p);
                    
                    printf("Final Shortest Paths:\n");
                    printf("+---------+---------+---------+------------------+\n");
                    printf("| Source  | Dest    | Length  | Path             |\n");
                    printf("+---------+---------+---------+------------------+\n");
                    for (int i = 1; i <= n; i++) {
                        for (int j = 1; j <= n; j++) {
                            char *path = getPath(p, i, j);
                            if (A[i][j] == INFINITY)
                                printf("| %-7d | %-7d | %-7s | %-16s |\n", i, j, "∞", path);
                            else
                                printf("| %-7d | %-7d | %-7d | %-16s |\n", i, j, A[i][j], path);
                            free(path);
                        }
                    }
                    printf("+---------+---------+---------+------------------+\n");
                } else {
                    printf("\nPlease input a graph first (Option 1).\n");
                }
                break;
            case 3:
                printf("\nExiting program.\n");
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 3);
    
    return 0;
}
