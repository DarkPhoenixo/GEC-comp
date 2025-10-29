#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 15
#define MAX_LEN 100
char a[MAX][MAX_LEN];

void merge(int min, int max) {
    int mid = (min + max) / 2;
    int i = min;
    int j = mid + 1;
    int k = 0;
    char temp[MAX][MAX_LEN];

    while (i <= mid && j <= max) {
        if (strcmp(a[i], a[j]) < 0) {
            strcpy(temp[k], a[i]);
            k++;
            i++;
        } else {
            strcpy(temp[k], a[j]);
            k++;
            j++;
        }
    }

    while (i <= mid) {
        strcpy(temp[k], a[i]);
        k++;
        i++;
    }

    while (j <= max) {
        strcpy(temp[k], a[j]);
        k++;
        j++;
    }

    for (i = min, k = 0; i <= max; i++, k++) {
        strcpy(a[i], temp[k]);
    }
}

void mergesort(int min, int max) {


    int mid;
    if (min < max) {
        mid = (min + max) / 2;
        mergesort(min, mid);
        mergesort(mid + 1, max);
        merge(min, max);
    }


}

int binary_search(char key[], int low, int high) {
   

    int mid;
    while (low <= high) {
        mid = (low + high) / 2;
        int cmp = strcmp(key, a[mid]);
        if (cmp == 0) {
            return mid;
        }
        if (cmp < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    return -1;
}

void display_elements(int n) {
    if (n == 0) {
    printf("Array is empty. Please enter the array first.\n");
    return;
  }
    printf("The elements of the array are: ");
    for (int i = 0; i < n; i++) {
      
        printf("| %10s ", a[i]);
    }
    printf("|\n");
}

int main() {

      printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

    int i, n=0, result, choice;
    char key[MAX_LEN];
     clock_t start, end;
     double cpu_time_used;

    do {
        printf("\nMenu:\n");
        printf("1. Enter elements of the array\n");
        printf("2. Display elements of the array\n");
        printf("3. Search for an element\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of elements in the array: ");
                scanf("%d", &n);
                for (i = 0; i < n; i++) {
                    printf("Enter element %d: ", i + 1);
                    scanf("%s", a[i]);
                }
                mergesort(0, n - 1);
                break;
            case 2:
            if (n == 0) {
          printf("Array is empty. Please enter the array first.\n");
         break ;
  }
                display_elements(n);
                break;
            case 3:
            
             
                printf("Enter the element to be searched: ");
                scanf("%s", key);
                start = clock();
                result = binary_search(key, 0, n - 1);
                end = clock();
                if (result == -1) {
                    printf("Element not found\n");
                } else {
                    printf("Element found at index %d\n", result);
                }
                 
                 cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
                 printf("Time taken by Binary Search: %f seconds\n", cpu_time_used);

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
