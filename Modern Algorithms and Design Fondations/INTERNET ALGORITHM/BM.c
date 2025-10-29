#include <stdio.h>
#include <string.h>
#define MAX 100
#include <time.h>

char p[MAX];
char t[MAX];
int cmp[MAX] = {0};
int comparison_count = 0; 
int store;
int lastocc_table[256]; 

int lastoccurrence(char a) {
    int m = strlen(p);
    for (int i = m - 1; i >= 0; i--) {
        if (p[i] == a) {
            return i;
        }
    }
    return -1;
}


void build_lastocc_table() {
    int m = strlen(p);
    for (int i = 0; i < 256; i++) lastocc_table[i] = -1;
    for (int i = 0; i < m; i++) lastocc_table[(unsigned char)p[i]] = i;
}


void print_lastocc_table() {
    int m = strlen(p);
    printf("\nLast Occurrence :\n");
    printf("Char: ");
    for (int i = 0; i < m; i++) printf("%4c", p[i]);
    printf("\nIdx : ");
    for (int i = 0; i < m; i++) printf("%4d", lastocc_table[(unsigned char)p[i]]);
    printf("\n\n");
}

void display_comparison(int i, int j) {
    printf("Comparing t[%d] = '%c' with p[%d] = '%c' : ", i, t[i], j, p[j]);
    if (t[i] == p[j]) {
        printf("Equal\n");
    } else {
        printf("Not Equal\n");
    }
}

long long current_time_us()
{
    clock_t now = clock();
    return (long long)((double)now * 1000000.0 / CLOCKS_PER_SEC);
}

int min(int a, int b) {
    return (a <= b) ? a : b;
}

void print_text() {
    int n = strlen(t);

    printf("Pattern: %s\n", p);
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("%4d", i); 
    }
    printf("\n");
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("----"); 
    }
    printf("\n");
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("|%3c", t[i]);  
    }
    printf("|\n");
    
    printf("    ");  
    for (int i = 0; i < n; i++) {
        printf("----"); 
    }
    printf("\n");
}

void print_pattern(int i, int j, int lastocc) {
    int m = strlen(p);
    int n = strlen(t);
    
    printf("\n");
    for (int k = 0; k < (i - j + 1); k++) {
        printf("    ");  
    }
    
    for (int idx = 0; idx < m; idx++) {
        printf("|%3c", p[idx]);  
    }
    printf("| i = %d lastocc = %d  ", i, lastocc);
    display_comparison(i, j);

    for (int k = 0; k < (i - j + 1); k++) {
        printf("    ");  
    }
    for (int idx = 0; idx < m; idx++) {
        printf("|%3d", cmp[idx]); 
    }
    printf("| j = %d\n", j);

    // Print last occurrence table for this step
    printf("Last Occurrence Table: ");
    for (int idx = 0; idx < m; idx++) {
        printf("%c:%d ", p[idx], lastocc_table[(unsigned char)p[idx]]);
    }
    printf("\n");

    printf("\n\n"); // 1-2 blank lines for clarity
}

void print_comparison_table() {
    int m = strlen(p);
    printf("\nTotal Comparisons Table:\n");
    printf("Char: ");
    for (int i = 0; i < m; i++) printf("%4c", p[i]);
    printf("\nCmp : ");
    for (int i = 0; i < m; i++) printf("%4d", cmp[i]);
    printf("\n");
}

int BM() {
    print_text();
    int m = strlen(p);
    int n = strlen(t);
    int i = m - 1;
    int j = m - 1;
    int flag = 1;

    do {
        comparison_count++; 
        if (p[j] == t[i]) {
            cmp[j]++;
            if (j == 0) {
                return i;
            } else {
                i--;
                j--;
            }
        } else {
            cmp[j]++;
            int lastocc = lastoccurrence(t[i]);
            store = n - i - (m - j);
            print_pattern(i, j, lastocc);
            i = i + m - min(j, lastocc + 1);
            j = m - 1;
        }
    } while (i <= n - 1);
    return -1;
}
int main() {
    int choice;
    long long start_time, end_time;
    do {
        printf("\nBoyer-Moore Pattern Matching Algorithm\n");
        printf("1. Enter new text and pattern\n");
        printf("2. Search pattern\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
        
            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);
            choice = -1; 
        }
        getchar(); 
        switch(choice) {
            case 1:
                printf("Enter the text: ");
                fgets(t, MAX, stdin);
                t[strcspn(t, "\n")] = 0;

                printf("Enter the pattern to search: ");
                fgets(p, MAX, stdin);
                p[strcspn(p, "\n")] = 0; 
                break;
            case 2:
                if (strlen(t) == 0 || strlen(p) == 0) {
                    printf("Please enter text and pattern first!\n");
                    break;
                }
                comparison_count = 0;
                memset(cmp, 0, sizeof(cmp)); 
                build_lastocc_table();
                printf("\nText: %s\n", t);
                printf("Pattern: %s\n", p);
                print_lastocc_table();
                start_time = current_time_us();
                int i = BM();
                print_pattern(i, 0, 0);
                end_time = current_time_us();
                printf("Time taken: %lld μs\n", end_time - start_time);
                if (i != -1) {
                    printf("\nPattern found at index: %d\n", i);
                } else {
                    printf("\nPattern not found in the text\n");
                }
                printf("Number of comparisons made: %d\n", comparison_count);
                print_comparison_table();
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
