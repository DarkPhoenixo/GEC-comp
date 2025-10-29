#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITEMS 100
#define MAX_CAPACITY 1000

typedef struct {
    float p;  // profit
    float w;  // weight
} PW;

int b[MAX_ITEMS+1];  

clock_t start_timer() {
    return clock();
}

double end_timer(clock_t start_time) {
    clock_t end_time = clock();
    return ((double)(end_time - start_time)) / CLOCKS_PER_SEC * 1000; // in milliseconds
}
float dpknap(float p[], float w[], int n, int m, PW pair[], int x[]) {
    int i, j, k, h, next;
    float pp, ww;
    
    h = 0;
    pair[0].p = 0;
    pair[0].w = 0;
    
    b[0] = 0;
    b[1] = 1;
    
    printf("\n|------------------------------------------");
    printf("\n| DYNAMIC PROGRAMMING APPROACH             ");
    printf("\n|------------------------------------------");
    
    // Print initial subset S0
    printf("\n| S%-2d: (%.0f,%.0f)                          |", 0, pair[0].p, pair[0].w);
    
    for (i = 1; i <= n; i++) {
        k = 0;
        next = h + 1;
        
        for (j = 0; j <= h; j++) {
            pp = pair[j].p + p[i];
            ww = pair[j].w + w[i];
            
            if (ww <= m) {
                while ((k <= h) && (pair[k].w <= ww)) {
                    k = k + 1;
                }
                
                if ((k <= h) && (pair[k].w == ww)) {
                    if (pp < pair[k].p) {
                        pp = pair[k].p;
                    }
                } else {
                    if (pp > pair[next - 1].p) {
                        pair[next].p = pp;
                        pair[next].w = ww;
                        next = next + 1;
                    }
                }
                
                while ((k <= h) && (pair[k].p <= pair[next - 1].p)) {
                    k = k + 1;
                }
            }
        }
        
        while ((k <= h) && (pair[k].p <= pair[next - 1].p)) {
            pair[next].p = pair[k].p;
            pair[next].w = pair[k].w;
            next = next + 1;
            k = k + 1;
        }
        
        h = next - 1;
        b[i+1] = next;
        
        // Print full subset Si
        printf("\n| S%-2d: ", i);
        for (j = 0; j < b[i+1]; j++) {
            printf("(%.0f,%.0f) ", pair[j].p, pair[j].w);
        }
        
        // Handle spacing for proper formatting
        int remaining = 38 - 7 - (b[i+1]) * 8;
        if (remaining < 0) remaining = 0;
        for (int k = 0; k < remaining; k++) {
            printf(" ");
        }
        printf("|");
    }
    printf("\n|------------------------------------------");

float max_profit = 0;
float max_weight = 0;
int max_idx = 0;

for (int i = 0; i <= h; i++) {
    if (pair[i].w <= m && (pair[i].p > max_profit || 
       (pair[i].p == max_profit && pair[i].w > max_weight))) {
        max_profit = pair[i].p;
        max_weight = pair[i].w;
        max_idx = i;
    }
}
    printf("\n| Maximum profit: %.0f, Weight: %.0f |", max_profit, max_weight);
    float remaining_weight = pair[max_idx].w;
    float remaining_profit = pair[max_idx].p;
    

    for (int i = n; i >= 1; i--) {
      
        int j;
        for (j = 0; j <= max_idx; j++) {
            if (pair[j].w == remaining_weight - w[i] && 
                pair[j].p == remaining_profit - p[i]) {
                x[i] = 1;  
                remaining_weight -= w[i];
                remaining_profit -= p[i];
                break;
            }
        }
    }
    
    printf("Selected items: ");
    int any_selected = 0;
    for (int i = 1; i <= n; i++) {
        if (x[i] == 1) {
            printf("%d ", i);
            any_selected = 1;
        }
    }
    if (!any_selected) {
        printf("None");
    }
    printf("\n");
    
    return max_profit;
}
void displayMenu() {
    printf("\n***** KNAPSACK PROBLEM  *****\n");
    printf("1. Enter new problem instance\n");
    printf("2. Solve using DP-Knapsack algorithm\n");
    printf("3. Display solution\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
}

void printItems(float p[], float w[], int n) {
    printf("\nItem Details:\n");
    printf("Item\tProfit\tWeight\n");
    for (int i = 1; i <= n; i++) {
        printf("%d\t%.2f\t%.2f\n", i, p[i], w[i]);
    }
}

int main() {
        printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    int n = 0;                      
    int capacity = 0;               
    float profits[MAX_ITEMS+1];     
    float weights[MAX_ITEMS+1];     
    int solution[MAX_ITEMS+1] = {0}; 
    PW pairs[MAX_CAPACITY + 1];     
    float optimal_value = 0;
    int choice;
    int solved = 0;
    
   
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("\nEnter the number of items: ");
                scanf("%d", &n);
                
                if (n <= 0 || n > MAX_ITEMS) {
                    printf("Invalid number of items. Please enter a value between 1 and %d.\n", MAX_ITEMS);
                    break;
                }
                
                printf("\nEnter the capacity of the knapsack: ");
                scanf("%d", &capacity);
                
                if (capacity <= 0 || capacity > MAX_CAPACITY) {
                    printf("Invalid capacity. Please enter a value between 1 and %d.\n", MAX_CAPACITY);
                    break;
                }
                
                printf("\nEnter the profit and weight for each item:\n");
                for (int i = 1; i <= n; i++) {
                    printf("Item %d profit: ", i);
                    scanf("%f", &profits[i]);
                    
                    printf("Item %d weight: ", i);
                    scanf("%f", &weights[i]);
                    
                    if (profits[i] < 0 || weights[i] <= 0) {
                        printf("Invalid profit or weight. Profit should be non-negative and weight should be positive.\n");
                        i--;
                    }
                }
                
                printItems(profits, weights, n);
                solved = 0;
                printf("\nProblem instance entered successfully.\n");
                break;
                
            case 2:
                if (n <= 0) {
                    printf("\nPlease enter a problem instance first (option 1).\n");
                    break;
                }
                
                printf("\nSolving the knapsack problem.\n");
                start_timer();
                optimal_value = dpknap(profits, weights, n, capacity, pairs, solution);
                double time_taken = end_timer(start_timer());
                printf("\nExecution time: %.2f ms\n", time_taken);
                
                solved = 1;
                printf("\nProblem solved! The optimal value is %.2f\n", optimal_value);
                break;
                
            case 3:
                if (!solved) {
                    printf("\nPlease solve the problem first (option 2).\n");
                    break;
                }
                
                printf("\n----- KNAPSACK SOLUTION -----\n");
                printf("Optimal value: %.2f\n", optimal_value);
                printf("Selected items: ");
                int any_selected = 0;
                for (int i = 1; i <= n; i++) {
                    if (solution[i] == 1) {
                        printf("%d ", i);
                        any_selected = 1;
                    }
                }
                if (!any_selected) {
                    printf("None");
                }
                printf("\n");
                
                printf("\nSelected items details:\n");
                printf("Item\tProfit\tWeight\n");
                float total_weight = 0;
                for (int i = 1; i <= n; i++) {
                    if (solution[i] == 1) {
                        printf("%d\t%.2f\t%.2f\n", i, profits[i], weights[i]);
                        total_weight += weights[i];
                    }
                }
                printf("\nTotal profit: %.2f\n", optimal_value);
                printf("Total weight: %.2f / %d\n", total_weight, capacity);
                break;
                
            case 4:
                printf("\nExiting ...\n");
                return 0;
                
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
    
    return 0;
}































































































































































//hello guys