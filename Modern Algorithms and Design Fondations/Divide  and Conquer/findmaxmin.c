#include <stdio.h>
#include <time.h>
#define MAX 20
int a[MAX];

void Min_max(int low, int high, int *min, int *max) {
 
    int mid, min1, max1;
    if (low == high) {
        *min = *max = a[low];
        printf("i = %d, j = %d, min = %d, max = %d.\n", low, high, *min, *max);
    } else if (low == high - 1) {
        if (a[low] < a[high]) {
            *min = a[low];
            *max = a[high];
            printf("i = %d, j = %d, min = %d, max = %d.\n", low, high, *min, *max);
        } else {
            *min = a[high];
            *max = a[low];
            printf("i = %d, j = %d, min = %d, max = %d.\n", low, high, *min, *max);
        }
    } else {
        mid = (low + high) / 2;
        Min_max(low, mid, min, max);
        Min_max(mid + 1, high, &min1, &max1);
        if (min1 < *min) {
            *min = min1;
        }
        if (max1 > *max) {
            *max = max1;
        }
        printf("i = %d, j = %d, min = %d, max = %d.\n", low, high, *min, *max);
    }

   
}

void displayArray(int n) {
    if (n == 0) {
        printf("Array is empty.\n");
    } else {
        printf("Array elements: ");
        for (int i = 0; i < n; i++) {
            printf("|%d ", a[i]);
        }
        printf("|\n");
    }
}

int main() {
    printf("*****************************************************");
    printf("\n Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

    int choice, i, n = 0, min, max;
       clock_t start, end;
    double cpu_time_used;
    

    while (1) {
        printf("\nMenu:\n");
        printf("1. Enter array elements\n");
        printf("2. Find min and max\n");
        printf("3. Display array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements in the array: ");
                scanf("%d", &n);

                if (n > MAX) {
                    printf("Number of elements exceeds the maximum allowed (%d). Please try again.\n", MAX);
                    n = 0;
                } else {
                    printf("Enter the elements of the array: ");
                    for (i = 0; i < n; i++) {
                        scanf("%d", &a[i]);
                    }
                }
                break;

            case 2:  start = clock();
                if (n == 0) {
                    printf("Array is empty. Please enter array elements first.\n");
                } else {
                    Min_max(0, n - 1, &min, &max);
                    printf("Minimum element: %d\n", min);
                    printf("Maximum element: %d\n", max);
                     end = clock();
                  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                 printf("Time taken by Min_max: %f seconds\n", cpu_time_used);
                }
                break;

            case 3:
                displayArray(n);
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}
