#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <windows.h>

#define MAX_SIZE 100

typedef struct Node {
    int s;
    int k;
    int r;
    int x[MAX_SIZE];
    char status; 
    struct Node *lchild;
    struct Node *rchild;
} Node;

int w[MAX_SIZE];
int m;
int n;
int solutionCount = 0;
int x[MAX_SIZE] = {0};
Node* root = NULL;

void printVector() {
    printf("(");
    for (int i = 1; i <= n; i++) {
        printf("%d", x[i]);
        if (i < n) printf(",");
    }
    printf(")\n");
}

Node* SumOfSub(int s, int k, int r) {
    Node* tmp = (Node*)malloc(sizeof(Node));
    tmp->s = s;
    tmp->k = k;
    tmp->r = r;
    tmp->lchild = NULL;
    tmp->rchild = NULL;
    tmp->status = 'N';
    
    for (int i = 1; i <= n; i++) {
        tmp->x[i] = x[i];
    }
    
    if (s == m) {
        tmp->status = 'S';
        solutionCount++;
        printf("Node(s=%d, k=%d, r=%d) Solution\n", s, k, r);
        printf("Vector: ");
        printVector();
        return tmp;
    }
    
    if (k > n) return tmp;

    x[k] = 1;
    if (s + w[k] <= m) {
        if (s + w[k] == m) {
            tmp->status = 'S';
            solutionCount++;
            printf("Node(s=%d, k=%d, r=%d) Solution\n", s + w[k], k + 1, r - w[k]);
            printf("Vector: ");
            printVector();
            
            tmp->lchild = (Node*)malloc(sizeof(Node));
            tmp->lchild->s = s + w[k];
            tmp->lchild->k = k + 1;
            tmp->lchild->r = r - w[k];
            tmp->lchild->status = 'S';
            tmp->lchild->lchild = NULL;
            tmp->lchild->rchild = NULL;
            
          
            for (int i = 1; i <= n; i++) {
                tmp->lchild->x[i] = x[i];
            }
        }
        else if (s + w[k] + r - w[k] >= m && k < n && s + w[k] + w[k+1] <= m) {
            tmp->lchild = SumOfSub(s + w[k], k + 1, r - w[k]);
        } else {
            printf("Node(s=%d, k=%d, r=%d) Bounded\n", s + w[k], k + 1, r - w[k]);
        }
    } else {
        printf("Node(s=%d, k=%d, r=%d) Bounded\n", s + w[k], k + 1, r - w[k]);
    }

    x[k] = 0;
    if (s + r - w[k] >= m && k < n && s + w[k+1] <= m) {
        tmp->rchild = SumOfSub(s, k + 1, r - w[k]);
    } else if (k <= n) {
        printf("Node(s=%d, k=%d, r=%d) Bounded\n", s, k + 1, r - w[k]);
    }

    return tmp;
}

void print_solutions(Node *root) {
    if (root == NULL) return;
    
    if (root->status == 'S' && root->s == m) {
        printf("Solution Node(s=%d, k=%d, r=%d): ", root->s, root->k, root->r);
        printf("(");
        for (int i = 1; i <= n; i++) {
            printf("%d", root->x[i]);
            if (i < n) printf(",");
        }
        printf(")\n");
    }
    
    print_solutions(root->lchild);
    print_solutions(root->rchild);
}

int calculateTotal(int w[], int n) {
    int total = 0;
    for (int i = 1; i <= n; i++) {
        total += w[i];
    }
    return total;
}

long long getMicrotime() {
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    
    QueryPerformanceFrequency(&frequency);
    QueryPerformanceCounter(&start);
    
    return (start.QuadPart * 1000000) / frequency.QuadPart;
}

void inputData() {
    printf("\nEnter the number of elements in set: ");
    scanf("%d", &n);
    
    printf("Enter the target sum (m): ");
    scanf("%d", &m);
    
    printf("Enter %d elements: ", n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i]);
        x[i] = 0;
    }
    
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            if (w[j] > w[j + 1]) {
                int temp = w[j];
                w[j] = w[j + 1];
                w[j + 1] = temp;
            }
        }
    }
    
   
}

void solveSubsetSum() {
    if (n == 0) {
        printf("\nPlease input data first (Option 1).\n");
        return;
    }
    
    int total = calculateTotal(w, n);
    
    if (w[1] > m || total < m) {
        printf("No solution exists.\n");
        return;
    }
    
    solutionCount = 0;
    printf("\nLEAF NODES: \n");
    
    long long startTime = getMicrotime();
    root = SumOfSub(0, 1, total);
    long long endTime = getMicrotime();
    long long executionTime = endTime - startTime;
    
    printf("\nTime taken: %lldμs\n", executionTime);
    
    if (solutionCount > 0) {
        printf("\nAll Solutions:\n");
        print_solutions(root);
        printf("\nTotal number of solutions: %d\n", solutionCount);
    } else {
        printf("\nNo solutions found.\n");
    }
}

int main() {
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    int choice;
    
    while (1) {
        printf("\n=== Sum of Subsets Menu ===\n");
        printf("1. Input data\n");
        printf("2. Find subsets with given sum\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                inputData();
                break;
                
            case 2:
                solveSubsetSum();
                break;
                
            case 3:
                printf("\nExiting program. Goodbye!\n");
                exit(0);
                
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
