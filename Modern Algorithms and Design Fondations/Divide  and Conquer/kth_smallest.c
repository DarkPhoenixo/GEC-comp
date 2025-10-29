#include <stdio.h>
#include <time.h>
#define MAX 20
char arr[MAX];

void display_array(int n) {
  if (n == 0) {
    printf("Array is empty. Please enter the array first.\n");
    return;
  }
  printf("Array elements are: ");
  for (int i = 0; i < n; i++) {
    printf("|%c ", arr[i]);
  }
  printf("|\n");
}


int partition(int low, int high) {
    clock_t start, end;
    double cpu_time_used;
    start = clock();
  int i = low + 1, j = high;
  char pivot = arr[low];
  while (i <= j) {
    while (i <= high && arr[i] <= pivot) i++;
    while (arr[j] > pivot) j--;
    if (i < j) {
      char temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  arr[low] = arr[j];
  arr[j] = pivot;
 

  return j;
}

void select(int k, int n) {
  if (k <= 0 || k > n) {
    printf("Invalid value of k. Please enter a value between 1 and %d.\n", n);
    return;
  }
  int l = 0, h = n - 1;
  int j;
  while (l <= h) {
    j = partition(l,h);
     printf ("\n ");
    display_array(n);
    printf (" j = %d and pivot = %c\n", j, arr[j]);
    printf ("\n ");
    if (j == k - 1) {
      printf ("\n ");
      display_array(n);
      printf (" j = %d and pivot = %c\n", j, arr[j]);
      printf ("\n \n"); 
      printf("%dth smallest element is '%c'\n", k, arr[j]);
      return;
    } else if (j < k - 1) {
      printf ("\n ");
      display_array(n);
      printf (" j = %d and pivot = %c\n", j, arr[j]);
      printf ("\n ");
      l = j + 1;
    } else {
        printf ("\n ");
      display_array(n);
        printf (" j = %d and pivot = %c\n", j, arr[j]);
      printf ("\n ");
      h = j - 1;
    }
  }


}


int main() {

 printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");


  int choice;
  int n = 0, k;
   clock_t start, end;
    double cpu_time_used;

  do {
    printf("\n\n--------------- Menu --------\n");
    printf("1. Enter the elements of the array\n");
    printf("2. Find kth smallest element in the list\n");
    printf("3. Display the array\n");
    printf("4. Exit\n");
    printf("Choose your option: ");
    scanf("%d", &choice);

    switch (choice) {
      case 1:
        printf("Enter the number of elements in the array (max %d): ", MAX);
        scanf("%d", &n);
        if (n <= 0 || n > MAX) {
          printf("Invalid number of elements. Please enter a value between 1 and %d.\n", MAX);
          n = 0;
          break;
        }
        printf("Enter the elements of the array (as characters):\n");
        for (int i = 0; i < n; i++) {
          while ((arr[i] = getchar()) == '\n');
        }
        break;
      case 2:   
        if (n == 0) { 
          printf("Array is empty. Please enter the array first.\n");
          break;
        }
        printf("Enter the value of k: ");
        scanf("%d", &k);
        start = clock();
        select(k, n);
         end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("\nTime taken by select function : %f seconds\n", cpu_time_used);
        break;
      case 3:
        display_array(n);
        break;
      case 4:
        printf("Exiting the program.\n");
        break;
      default:
        printf("Invalid choice. Please choose a valid option.\n");
        break;
    }
  } while (choice != 4);

  return 0;
}










































































































































































































































































































































































































































































































//hello































































































































































































































































































































































































