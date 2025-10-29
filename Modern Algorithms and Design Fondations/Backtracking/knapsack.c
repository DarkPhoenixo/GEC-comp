#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 100

int w[MAX_ITEMS];
int p[MAX_ITEMS];
int x[MAX_ITEMS];
int y[MAX_ITEMS];
int n, m;
int fw = 0, fp = 0; 
int bound_nodes = 0;

typedef enum {
    NORMAL,
    BOUNDED,
    NON_FEASIBLE,
    SOLUTION
} State;

float Bound(int cp, int cw, int k) {
    float b = cp;
    float c = cw;
    
    for (int i = k; i < n; i++) { 
        if (c + w[i] <= m) {
            b += p[i];
            c += w[i];
        } else {
            b += ((float)(m - c) / w[i]) * p[i];
            break;
        }
    }
    
    bound_nodes++;
    return b;
}

void printNode(int k, int cp, int cw, State state, float bound_value) {
    if (state == NORMAL) {
        return; 
    }
    printf("Node: k = %d, cp = %d, cw = %d, Bound = %.2f, State = ", k+1, cp, cw, bound_value);
    switch (state) {
        case BOUNDED:
            printf("BOUNDED\n");
            break;
        case NON_FEASIBLE:
            printf("NON-FEASIBLE\n");
            break;
        case SOLUTION:
            printf("SOLUTION\n");
            break;
        default:
            break;
    }
}

void BKnap(int k, int cp, int cw) {
    float node_bound;
    
    
    if (cw + w[k - 1] <= m) { 
        y[k - 1] = 1;
        
        if (k < n) {
            node_bound = Bound(cp + p[k - 1], cw + w[k - 1], k);
            if (node_bound > fp) {
                printNode(k, cp + p[k - 1], cw + w[k - 1], NORMAL, node_bound);
                BKnap(k + 1, cp + p[k - 1], cw + w[k - 1]);
            } else {
                printNode(k, cp + p[k - 1], cw + w[k - 1], BOUNDED, node_bound);
            }
        } else if (k == n) {
          
            if (cp + p[k - 1] > fp) {
                fp = cp + p[k - 1];
                fw = cw + w[k - 1];
                for (int j = 0; j < n; j++) {
                    x[j] = y[j];
                }
                printNode(k, cp + p[k - 1], cw + w[k - 1], SOLUTION, (float)fp);
            }
        }
    } else {
       
        printNode(k, cp + p[k - 1], cw + w[k - 1], NON_FEASIBLE, 0.0);
    }
    
   
    y[k - 1] = 0;
    if (k < n) {
        node_bound = Bound(cp, cw, k);
        if (node_bound > fp) {
           
            BKnap(k + 1, cp, cw);
        } else {
            printNode(k, cp, cw, BOUNDED, node_bound);
        }
    } else if (k == n && cp > fp) {
       
        fp = cp;
        fw = cw;
        for (int j = 0; j < n; j++) {
            x[j] = y[j];
        }
        printNode(k, cp, cw, SOLUTION, (float)fp);
    }
}

long long current_timestamp() {
    clock_t t = clock();
    long long microseconds = (long long)(t * 1000000.0 / CLOCKS_PER_SEC);
    return microseconds;
}

int main() {
 
    
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    int choice;
    
    do {
        printf("\n------- Knapsack Problem Using Backtracking -------\n");
        printf("1. Enter input data\n");
        printf("2. Solve Knapsack Problem\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("Enter number of items: ");
                scanf("%d", &n);
                
                printf("Enter knapsack capacity: ");
                scanf("%d", &m);
                
                printf("Enter weights of items:\n");
                for (int i = 0; i < n; i++) {
                    printf("Weight of item %d: ", i + 1);
                    scanf("%d", &w[i]);
                }
                
                printf("Enter profits of items:\n");
                for (int i = 0; i < n; i++) {
                    printf("Profit of item %d: ", i + 1);
                    scanf("%d", &p[i]);
                }
                break;
                
            case 2:
                bound_nodes = 0;
                fp = 0;
                fw = 0;
                
                for (int i = 0; i < n; i++) {
                    x[i] = 0;
                    y[i] = 0;
                }
                
                long long start_time = current_timestamp();
                BKnap(1, 0, 0); 
                long long end_time = current_timestamp();
                
                printf("\n----- Solution -----\n");
                printf("\nSolution vector: ");
                for (int i = 0; i < n; i++) {
                  printf("x%d = %d", i + 1, x[i]);
                  if (i < n - 1) {
                   printf(", ");
                    }
                     }
                  printf("\n");

                printf("Items included in knapsack:\n");
                for (int i = 0; i < n; i++) {
                    if (x[i] == 1) {
                        printf("Item %d (Weight: %d, Profit: %d)\n", i + 1, w[i], p[i]);
                    }
                }
                
                printf("\nMaximum profit: %d\n", fp);
                printf("Final weight: %d\n", fw);
                printf("Time taken: %lld microseconds\n", end_time - start_time);
                break;
                
            case 3:
                printf("Exiting program. Goodbye!\n");
                break;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
    
    return 0;
}
