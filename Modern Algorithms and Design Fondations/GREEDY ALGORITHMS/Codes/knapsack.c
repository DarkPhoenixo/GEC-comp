#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
int sort[MAX];  
void sortProfit(int n, float profit[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        sort[i] = i; }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (profit[sort[j]] < profit[sort[j + 1]]) {
                int temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
  }}}}

void sortWeight(int n, float weight[]) {
    int i, j;
    for (i = 0; i < n; i++) {
        sort[i] = i; 
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (weight[sort[j]] > weight[sort[j + 1]]) {
                int temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
}}}}

void sortRatio(int n, float profit[], float weight[]) {
    int i, j;
    float pw[MAX];

    for (i = 0; i < n; i++) {
        sort[i] = i;
        pw[i] = profit[i] / weight[i]; 
    }

    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (pw[sort[j]] < pw[sort[j + 1]]) {
                int temp = sort[j];
                sort[j] = sort[j + 1];
                sort[j + 1] = temp;
}}}}
void maxProfit(int n, int m, float profit[], float weight[]) {
    float objx[MAX] = {0}; 
    float total = 0.0;
    int max = m, i;

    sortProfit(n, profit);

    for (i = 0; i < n && weight[sort[i]] <= max; i++) {
        total += profit[sort[i]];
        objx[sort[i]] = 1.0;
        max -= weight[sort[i]];
    }

    if (max > 0 && i < n) {
        objx[sort[i]] = (float)max / weight[sort[i]];
        total += profit[sort[i]] * objx[sort[i]];
    }


    printf("\nMAXIMUM PROFIT STRATEGY\n");
    for (i = 1; i <=n; i++) {
  printf ("\tx%d", i);
 }
    printf("\t   WiXi\t\tPiXi\n");
    for (i = 0; i < n; i++) {
        printf("\t%.2f", objx[i]);
    }
    printf("\t   %d\t\t%.2f\n", m, total);
}
void minWeight(int n, int m, float profit[], float weight[]) {
    float objx[MAX] = {0};
    float total = 0.0;
    int max = m, i;

    sortWeight(n, weight); 

    for (i = 0; i < n && weight[sort[i]] <= max; i++) {
        total += profit[sort[i]];
        objx[sort[i]] = 1.0;
        max -= weight[sort[i]];
    }

    if (max > 0 && i < n) {
        objx[sort[i]] = (float)max / weight[sort[i]];
        total += profit[sort[i]] * objx[sort[i]];
    }

    printf("\nMINIMUM WEIGHT STRATEGY\n");
         for (i = 1; i <=n; i++) {
  printf ("\tx%d", i);
 }
    printf("\t   WiXi\t\tPiXi\n");
    for (i = 0; i < n; i++) {
        printf("\t%.2f", objx[i]);
    }
    printf("\t   %d\t\t%.2f\n", m, total);
}

void maxRatio(int n, int m, float profit[], float weight[]) {
    float objx[MAX] = {0};
    float total = 0.0;
    int max = m, i;

    sortRatio(n, profit, weight); 

    for (i = 0; i < n && weight[sort[i]] <= max; i++) {
        total += profit[sort[i]];
        objx[sort[i]] = 1.0;
        max -= weight[sort[i]];
    }

    if (max > 0 && i < n) {
        objx[sort[i]] = (float)max / weight[sort[i]];
        total += profit[sort[i]] * objx[sort[i]];
    }
    printf("\nMAXIMUM PROFIT-TO-WEIGHT RATIO STRATEGY\n");
        for (i = 1; i <=n; i++) {
  printf ("\tx%d", i);
 }
    printf("\t   WiXi\t\tPiXi\n");
    for (i = 0; i < n; i++) {
        printf("\t%.2f", objx[i]);
    }
    printf("\t   %d\t\t%.2f\n", m, total);
}

void solve_multiple_strategies(int n, float weight[], float profit[], int m) {
    maxProfit(n, m, profit, weight);
    minWeight(n, m, profit, weight);
    maxRatio(n, m, profit, weight);
}

int main() {

    printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");




    int i, n, m;
    printf("Enter number of elements (n): ");
    scanf("%d", &n);

    float *profit = (float *)malloc(n * sizeof(float));
    float *weight = (float *)malloc(n * sizeof(float));
    if (profit == NULL || weight == NULL) {
        printf("Memory allocation failed\n");
        return 1;
    }

    printf("Enter weights (w1, w2, ...): ");
    for (i = 0; i < n; i++) {
        scanf("%f", &weight[i]);
    }

    printf("Enter value of m (capacity): ");
    scanf("%d", &m);

    printf("Enter profits (p1, p2, ...): ");
    for (i = 0; i < n; i++) {
        scanf("%f", &profit[i]);
    }
   
    clock_t start = clock();
    solve_multiple_strategies(n, weight, profit, m);
    clock_t end = clock();
  
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("\nTime taken: %.6f seconds\n", time_taken);
    return 0;
}
