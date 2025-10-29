#include <string.h>
#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MAX 100
#define UP_ARROW '^'
#define LEFT_ARROW '<'
#define DIAGONAL_ARROW '\\'

char X[MAX];
char Y[MAX];
int L[MAX][MAX];
int sub1[MAX];
int leastSequence[MAX][MAX] = {0};

int maxleast(int a, int b) {
    return (a > b) ? a : b;
}
long long current_time_us()
{
    LARGE_INTEGER frequency, counter;
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&counter);
    return (counter.QuadPart * 1000000) / frequency.QuadPart;
}

void LCS() {
    int n = strlen(X);
    int m = strlen(Y);
    for (int i = 0; i <= n; i++) {
        L[i][0] = 0;
    }
    for (int j = 0; j <= m; j++) {
        L[0][j] = 0;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = maxleast(L[i - 1][j], L[i][j - 1]);
            }
        }
    }
}

void traverse() {
    int n = strlen(X);
    int m = strlen(Y);
    int i = n;
    int j = m;
    int c = L[n][m];
    while (c > 0) {
        if (X[i - 1] == Y[j - 1]) {
            leastSequence[i][j] = DIAGONAL_ARROW;
            sub1[c] = X[i - 1];
            c--;
            i--;
            j--;
        } else {
            if (L[i - 1][j] > L[i][j - 1]) {
                leastSequence[i][j] = UP_ARROW;
                i--;
            } else {
                leastSequence[i][j] = LEFT_ARROW;
                j--;
            }
        }
    }
}

int main() {
    int choice;
    while (1) {
        printf("\n=== Longest Common Subsequence Menu ===\n");
        printf("1. Find LCS of two strings\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                // Clear input buffer
                while (getchar() != '\n');
                
                printf("Enter X: ");
                scanf("%s", X);
                printf("Enter Y: ");
                scanf("%s", Y);
                
                int n = strlen(X);
                int m = strlen(Y);
                long long start_time = current_time_us();
                
                LCS();
                traverse();
                
                long long end_time = current_time_us();
                printf("Time taken: %lld μs\n", end_time - start_time);

                printf("\n     -1 "); 
                for (int j = 0; j < m; j++) {
                    printf("%3d ", j);
                }
                printf("\n        ");  
                for (int j = 0; j < m; j++) {
                    printf("%3c ", Y[j]);
                }
                printf("\n");

                for (int i = 0; i <= n; i++) {
                    if (i == 0) {
                        printf("-1  ");  
                    } else {
                        printf("%2d %c", i-1, X[i-1]);
                    }
                    
                    for (int j = 0; j <= m; j++) {
                        if (leastSequence[i][j] == DIAGONAL_ARROW) {
                            printf("%2c%d ", DIAGONAL_ARROW, L[i][j]);
                        } else if (leastSequence[i][j] == UP_ARROW) {
                            printf("%2c%d ", UP_ARROW, L[i][j]);
                        } else if (leastSequence[i][j] == LEFT_ARROW) {
                            printf("%2c%d ", LEFT_ARROW, L[i][j]);
                        } else {
                            printf("%3d ", L[i][j]);
                        }
                    }
                    printf("\n");
                }

                printf("\nLongest Common Subsequence: ");
                for (int i = 1; i <= L[n][m]; i++) {
                    printf("%c ", sub1[i]);
                }
                printf("\n");
                break;
            }
            case 2:
                printf("Exiting program...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}


