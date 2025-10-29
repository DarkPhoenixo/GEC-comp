#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX 10
int n=0;

typedef struct {
    int id;
    char name[50];
    float price;
} Item;

Item a[MAX];

void merge(int min, int max) {
    int mid = (min + max) / 2;
    int i = min;
    int j = mid + 1;
    int k = min;
    Item temp[MAX];

    while (i <= mid && j <= max) {
        if (a[i].id < a[j].id) {
            temp[k] = a[i];
            k++;
            i++;
        } else {
            temp[k] = a[j];
            k++;
            j++;
        }
    }

    while (i <= mid) {
        temp[k++] = a[i++] ;
    }

    while (j <= max) {
        temp[k] = a[j];
        k++;
        j++;
    }

    for (i = min, k = min; i <= max; i++, k++) {
        a[i] = temp[k];
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

void displayItems() {
    int i;
    printf("\nItems:\n");
    for (i = 0; i < n; i++) {
        printf("Item %d\n", i + 1);
        printf("ID: %d\n", a[i].id);
        printf("Name: %s\n", a[i].name);
        printf("Price: %.2f\n", a[i].price);
        printf("\n");
    }
}

int main() {

      printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

     clock_t start, end;
    double cpu_time_used;
    
    int choice;
    int i;

    do {
        printf("\nMenu:\n");
        printf("1. Enter items\n");
        printf("2. Sort items by ID\n");
        printf("3. Display items\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of items (up to %d): ", MAX);
                  scanf("%d", &n);
                if (n > MAX) {
                     printf("You can only enter up to %d items.\n", MAX);
                      break;
                   }
                    printf("Enter the elements of the array:\n");
                     for (i = 0; i < n; i++) {
                          printf("Item %d\n", i + 1);
                           printf("ID: ");
                           scanf("%d", &a[i].id);
                    printf("Name: ");
                     scanf("%s", a[i].name);
                    printf("Price(in Rs.): ");
                    scanf("%f", &a[i].price);
                                   
          }
                break;
            case 2:
            start = clock();
                mergesort(0, n-1);
                printf("Items sorted by ID.\n");
                 end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by Merge Sort: %f seconds\n", cpu_time_used);
                break;
            case 3:
                displayItems();
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