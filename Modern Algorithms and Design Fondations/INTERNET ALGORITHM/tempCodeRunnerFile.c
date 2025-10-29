#include <stdio.h>
#include <string.h>
#define MAX 100
#include <time.h>
char p[MAX];
char t[MAX];
int cmp[MAX] = {0};
int comparison_count = 0;
int f[MAX];
int store;

// 1. Compare reason function
void compare_reason(char a, char b, int i, int j) {
    printf("Comparing t[%d] = '%c' and p[%d] = '%c': ", i, a, j, b);
    if (a == b)
        printf("EQUAL\n");
    else
        printf("NOT EQUAL\n");
}

// 2. Display failure function at each step
void display_failure_step(int m, int upto) {
    printf("Failure function after step %d: [", upto);
    for (int k = 0; k <= upto; k++) {
        printf("%d", f[k]);
        if (k < upto) printf(", ");
    }
    printf("]\n");
}

long long current_time_us(){
    return (long long)(clock() * 1000000LL / CLOCKS_PER_SEC);
}

void failureFunction(int m){
    f[0] = 0;
    int i = 1, j = 0;
    printf("\nFailure Function (f[]): ");
    while (i < m) {
        // Show comparison reason
        compare_reason(p[i], p[j], i, j);
        if (p[i] == p[j]) {
            f[i] = j + 1;
            display_failure_step(m, i); // Show failure function at this step
            i++;
            j++;
        }
        else if (j > 0) {
            j = f[j - 1];
        }
        else {
            f[i] = 0;
            display_failure_step(m, i); // Show failure function at this step
            i++;
        }
    }
    // Final failure function display
    printf("\nFinal Failure Function:\n");
    for (int k = 0; k < m; k++)
        printf("%2c ", p[k]);
    printf("\n");
    for (int k = 0; k < m; k++)
        printf("---");
    printf("-\n|");
    for (int k = 0; k < m; k++)
        printf("%d |", f[k]);
    printf("\n");
    for (int k = 0; k < m; k++)
        printf("---");
    printf("-\n");
    printf("\n");
}

void print_pattern(int i, int j){
    int m = strlen(p);
    int n = strlen(t);
    printf("\n");
    for (int k = 0; k < (i - j + 1); k++)    {
        printf("    ");
    }
    for (int idx = 0; idx < m; idx++)    {
        printf("|%3c", p[idx]);
    }
    printf("| i = %d\n", i);
    for (int k = 0; k < (i - j + 1); k++)    {
        printf("    ");
    }
    for (int idx = 0; idx < m; idx++)    {
        printf("|%3d", cmp[idx]);
    }
    printf("| j = %d\n", j);
}

void print_text(){
    int n = strlen(t);
    printf("Pattern: %s\n", p);
    printf("    ");
    for (int i = 0; i < n; i++)    {
        printf("%4d", i);
    }
    printf("\n");
    printf("    ");
    for (int i = 0; i < n; i++)    {
        printf("----");
    }
    printf("\n");
    printf("    ");
    for (int i = 0; i < n; i++)    {
        printf("|%3c", t[i]);
    }
    printf("|\n");
    printf("    ");
    for (int i = 0; i < n; i++)    {
        printf("----");
    }
    printf("\n");
}

int KMP(){
    int m = strlen(p);
    int n = strlen(t);
    failureFunction(m);
    print_text( );
    int i = 0, j = 0;
    while (i < n){
        comparison_count++;
        compare_reason(t[i], p[j], i, j); // Show comparison reason
        if (t[i] == p[j])       {
            cmp[j]++;
            if (j == m - 1)
            {
                return i - m + 1;
            }
            i++;
            j++;
        }
        else if (j > 0)   {
            store = i;
            cmp[j]++;
            print_pattern( i, j);
            j = f[j - 1];
        }
        else        {
            cmp[j]++;
            print_pattern( i, j);
            i++;
        }
    }
    return -1;
}

int main(){
    int choice;
    long long start_time, end_time;
    do    {
        printf("\nKnuth-Morris-Pratt Pattern Matching Algorithm\n");
        printf("1. Enter new text and pattern\n");
        printf("2. Search pattern\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        switch (choice)        {
        case 1:
            printf("Enter the text: ");
            fgets(t, MAX, stdin);
            t[strcspn(t, "\n")] = 0;

            printf("Enter the pattern to search: ");
            fgets(p, MAX, stdin);
            p[strcspn(p, "\n")] = 0;
            break;
        case 2:
            if (strlen(t) == 0 || strlen(p) == 0)
            {
                printf("Please enter text and pattern first!\n");
                break;
            }
            comparison_count = 0;
            memset(cmp, 0, sizeof(cmp));
            printf("\nText: %s\n", t);
            printf("Pattern: %s\n", p);
            start_time = current_time_us();
            int i = KMP();
            print_pattern( i, 0);
            end_time = current_time_us();
            printf("Time taken: %lld μs\n", end_time - start_time);
            if (i != -1)            {
                printf("\nPattern found at index: %d\n", i);
            }
            else            {
                printf("\nPattern not found in the text\n");
            }
            printf("Number of comparisons made: %d\n", comparison_count);
            break;
        case 3:
            printf("Exiting program...\n");
            break;
        default:
            printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
    return 0;
}
