#include <stdio.h>
#define MAX 15
#include <time.h>
int a[MAX];
int n;

void displayArray() {
    int i;
    for (i = 0; i < n; i++) {
        printf("|%d ", a[i]);
    }
    printf("|\n");
}

void partition(int low, int high, int *pp) {
   
  
    int i, j,  pivot, temp;
    pivot = a[low];
    i = low;
    j = high + 1;
    printf(" i = %d , j = %d ,pivot = %d .  \n ", i, j, pivot);
    displayArray();
    while (1) {

        do {
            i++;
        } while (i <= high && a[i] <= pivot);
        do {
            j--;
        } while (a[j] > pivot);
        if (i >= j) {
            break;
        }
        printf("\n");

        temp = a[i];
        a[i] = a[j];
        a[j] = temp;
        printf(" i = %d , j = %d ,pivot = %d . ( i , j interchanged )\n  ", i, j, pivot);
        printf("\n");
        displayArray();
    }
    temp = a[low];
    a[low] = a[j];
    a[j] = temp;
    *pp = j;
    printf("\n i = %d , j = %d ,pivot = %d . (pivot exchanged ) \n ", i, j, pivot);
    displayArray();
}

void quicksort(int low, int high) {
   
    int p;
    if (low < high) {
        partition(low, high, &p);
        quicksort(low, p - 1);
        quicksort(p + 1, high);
    }
   
}

int main() {

          printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

    int choice, i;
     clock_t start, end;
    double cpu_time_used;
    do {
        printf("Menu:\n");
        printf("1. Enter array elements\n");
        printf("2. Sort array using Quicksort\n");
        printf("3. Display sorted array\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements in the array: ");
                scanf("%d", &n);
                printf("Enter the elements of the array: ");
                for (i = 0; i < n; i++) {
                    scanf("%d", &a[i]);
                }
                break;
            case 2:
            
    start = clock();
                quicksort(0, n - 1);
                printf("Array sorted using Quicksort.\n");
                 end = clock();
               cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
               printf("Time taken by quicksort: %f seconds\n", cpu_time_used);
                break;
            case 3:
                printf("Sorted array: ");
                displayArray();
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 4);
    return 0;
}
