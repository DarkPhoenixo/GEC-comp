#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include <time.h>

#define MAX_KEYS 100
#define MAX_HEIGHT 100
#define MAX_WIDTH 255

struct node {
    int key;
    char* identifier;
    struct node *left, *right;
};

char treePrint[MAX_HEIGHT][MAX_WIDTH];
char* identifiers[MAX_KEYS];
clock_t start_time, end_time;

void startTimer() {
    start_time = clock();
}

void stopTimer() {
    end_time = clock();
    double time_us = ((double)(end_time - start_time) * 1000000.0) / CLOCKS_PER_SEC;
    printf("\nTime taken: %.0fμs\n", time_us);
}

void clearTreePrint() {
    for (int i = 0; i < MAX_HEIGHT; i++)
        for (int j = 0; j < MAX_WIDTH; j++)
            treePrint[i][j] = ' ';
}

void drawTree(struct node *root, int row, int col, int spacing) {
    if (root == NULL) return;

    char buf[50];
    sprintf(buf, "%s(%d)", root->identifier, root->key);
    int len = strlen(buf);
    for (int i = 0; i < len; i++)
        treePrint[row][col + i] = buf[i];

    if (root->left) {
        int i;
        for (i = 1; i < spacing; i++) {
            treePrint[row + i][col - i] = '/';
        }
        drawTree(root->left, row + spacing, col - spacing * 2, spacing);
    }

    if (root->right) {
        int i;
        for (i = 1; i < spacing; i++) {
            treePrint[row + i][col + len + i - 1] = '\\';
        }
        drawTree(root->right, row + spacing, col + len + spacing, spacing);
    }
}

void displayOBSTTopDown(struct node *root) {
    clearTreePrint();
    drawTree(root, 0, MAX_WIDTH / 2, 3);

    for (int i = 0; i < MAX_HEIGHT; i++) {
        int line_has_char = 0;
        for (int j = 0; j < MAX_WIDTH; j++) {
            if (treePrint[i][j] != ' ') line_has_char = 1;
        }
        if (line_has_char) {
            for (int j = 0; j < MAX_WIDTH; j++)
                putchar(treePrint[i][j]);
            putchar('\n');
        }
    }
}

struct node* buildTree(int r[][MAX_KEYS], int i, int j) {
    if (i >= j || r[i][j] == 0) return NULL;
    
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    int rootKey = r[i][j];
    newNode->key = rootKey;
    newNode->identifier = identifiers[rootKey];
    
    newNode->left = buildTree(r, i, rootKey - 1);
    newNode->right = buildTree(r, rootKey, j);
    
    return newNode;
}

// Function to display detailed step-by-step calculations
void displayStepByStepCalculations(float p[], float q[], int n, float w[][MAX_KEYS], float c[][MAX_KEYS], int r[][MAX_KEYS]) {
    printf("\n----- DETAILED STEP-BY-STEP CALCULATIONS -----\n");
    
    // Initialize base cases
    printf("\n--- Base Cases Initialization ---\n");
    for (int i = 0; i <= n; i++) {
        printf("w(%d,%d) = q(%d) = %.0f\n", i, i, i, q[i]);
        printf("c(%d,%d) = 0\n", i, i);
        printf("r(%d,%d) = 0\n", i, i);
    }
    
    // Calculate for length 1
    printf("\n--- Length 1 Calculations ---\n");
    for (int i = 0; i < n; i++) {
        int j = i + 1;
        printf("w(%d,%d) = p(%d) + q(%d) + w(%d,%d) = %.0f\n", i, j, j, j, i, i, w[i][j]);
        printf("c(%d,%d) = w(%d,%d) + min{c(%d,%d) + c(%d,%d)} = %.0f\n", i, j, i, j, i, j-1, j, j, c[i][j]);
        printf("r(%d,%d) = %d\n", i, j, r[i][j]);
    }
    
    // Calculate for lengths 2 and greater
    for (int m = 2; m <= n; m++) {
        printf("\n--- Length %d Calculations ---\n", m);
        for (int i = 0; i <= n - m; i++) {
            int j = i + m;
            printf("w(%d,%d) = p(%d) + q(%d) + w(%d,%d) = %.0f\n", i, j, j, j, i, j-1, w[i][j]);
            
            printf("c(%d,%d) = w(%d,%d) + min {", i, j, i, j);
            
            // Display all potential k values and their costs
            for (int k = r[i][j-1]; k <= r[i+1][j]; k++) {
                float cost = c[i][k-1] + c[k][j];
                printf("c(%d,%d) + c(%d,%d) = %.0f", i, k-1, k, j, cost);
                if (k < r[i+1][j])
                    printf(", ");
            }
            
            printf("} = %.0f\n", c[i][j] - w[i][j]);
            printf("Total c(%d,%d) = %.0f\n", i, j, c[i][j]);
            printf("r(%d,%d) = %d\n", i, j, r[i][j]);
        }
    }
}

void calculateOBST(float p[], float q[], int n, float w[][MAX_KEYS], float c[][MAX_KEYS], int r[][MAX_KEYS]) {
    int i, j, k, m;
    float t;
    
    for (i = 0; i <= n; i++) {
        w[i][i] = q[i];
        c[i][i] = 0;
        r[i][i] = 0;
    }
    
    for (i = 0; i < n; i++) {
        j = i + 1;
        w[i][j] = q[i] + p[j] + q[j];
        c[i][j] = q[i] + p[j] + q[j];
        r[i][j] = j;
    }
    
    printf("+---------+---------+---------+\n");
    printf("| i       | w[i][i] | c[i][i] | r[i][i] |\n");
    printf("+---------+---------+---------+\n");
    for (i = 0; i <= n; i++) {
        printf("| %d       | %.0f      | %.0f      | %d      |\n", i, w[i][i], c[i][i], r[i][i]);
    }
    printf("+---------+---------+---------+\n\n");
    
    for (m = 2; m <= n; m++) {
        for (i = 0; i <= n - m; i++) {
            j = i + m;
            w[i][j] = w[i][j-1] + p[j] + q[j];
            
            float min_cost = FLT_MAX;
            int min_k = i + 1;
            
            for (k = r[i][j-1]; k <= r[i+1][j]; k++) {
                t = c[i][k-1] + c[k][j];
                if (t < min_cost) {
                    min_cost = t;
                    min_k = k;
                }
            }
            
            c[i][j] = w[i][j] + min_cost;
            r[i][j] = min_k;
        }
    }
    
    printf("\n+-----------");
    for (int i = 0; i <= n; i++) {
        printf("+-----------");
    }
    printf("+\n|           ");
    for (int i = 0; i <= n; i++) {
        printf("| %-9d ", i);
    }
    printf("|\n+-----------");
    for (int i = 0; i <= n; i++) {
        printf("+-----------");
    }
    printf("+\n");
    
    for (int d = 0; d <= n; d++) {
        printf("| j-i=%-5d ", d);
        j = 0;
        printf("| w:%6.0f   ", w[j][d]);
        j++;
        for (int i = d + 1; i <= n; i++) {
            printf("| w:%6.0f   ", w[j][i]);
            j++;
        }
        printf("|\n|           ");
        j = 0;
        printf("| c:%6.0f   ", c[j][d]);
        j++;
        for (int i = d + 1; i <= n; i++) {
            printf("| c:%6.0f   ", c[j][i]);
            j++;
        }
        printf("|\n|           ");
        j = 0;
        printf("| r:%6d   ", r[j][d]);
        j++;
        for (int i = d + 1; i <= n; i++) {
            printf("| r:%6d   ", r[j][i]);
            j++;
        }
        printf("|\n+-----------");
        for (int i = 0; i <= n; i++) {
            printf("+-----------");
        }
        printf("+\n");
    }
    
    printf("\nCost of Optimal Binary Search Tree: %.0f\n", c[0][n]);
    printf("\nRoot of Optimal Binary Search Tree: %d\n", r[0][n]);
}

void freeTree(struct node* root) {
    if (root == NULL) return;
    
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

int main() {
    int n;
    float p[MAX_KEYS];
    float q[MAX_KEYS];
    float w[MAX_KEYS][MAX_KEYS];
    float c[MAX_KEYS][MAX_KEYS];
    int r[MAX_KEYS][MAX_KEYS];
    struct node* root = NULL;
    int choice;
    
    printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    
    while(1) {
        printf("\n----- OPTIMAL BINARY SEARCH TREE MENU -----\n");
        printf("1. Create a new OBST\n");
        printf("2. Display tables\n");
        printf("3. Display tree visualization\n");
        printf("4. Display detailed step-by-step calculations\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice) {
            case 1:
                printf("\nEnter the number of keys: ");
                scanf("%d", &n);
                
                printf("Enter the keys:\n");
                for (int i = 1; i <= n; i++) {
                    identifiers[i] = (char*)malloc(MAX_KEYS * sizeof(char));
                    printf("Key %d: ", i);
                    scanf("%s", identifiers[i]);
                }
                
                printf("Enter the probability of successful search:\n");
                for (int i = 1; i <= n; i++) {
                    printf("p[%d] = ", i);
                    scanf("%f", &p[i]);
                }
                
                printf("Enter the probability of unsuccessful search:\n");
                for (int i = 0; i <= n; i++) {
                    printf("q[%d] = ", i);
                    scanf("%f", &q[i]);
                }
                
                p[0] = 0.0;
                
                startTimer();
                calculateOBST(p, q, n, w, c, r);
                stopTimer();
                
                if (root != NULL) {
                    freeTree(root);
                }
                root = buildTree(r, 0, n);
                break;
                
            case 2:
                if (root == NULL) {
                    printf("\nPlease create an OBST first.\n");
                } else {
                    printf("\n----- OPTIMAL BST TABLES -----\n");
                    calculateOBST(p, q, n, w, c, r);
                }
                break;
                
            case 3:
                if (root == NULL) {
                    printf("\nPlease create an OBST first.\n");
                } else {
                    printf("\n----- GRAPHICAL REPRESENTATION OF OPTIMAL BST -----\n");
                    displayOBSTTopDown(root);
                }
                break;
                
            case 4:
                if (root == NULL) {
                    printf("\nPlease create an OBST first.\n");
                } else {
                    displayStepByStepCalculations(p, q, n, w, c, r);
                }
                break;
                
            case 5:
                if (root != NULL) {
                    freeTree(root);
                }
                for (int i = 1; i <= n; i++) {
                    if (identifiers[i] != NULL) {
                        free(identifiers[i]);
                    }
                }
                printf("\nThank you for using OBST program!\n");
                return 0;
                
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    
    return 0;
}
