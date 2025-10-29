#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 100
#define INF 99999
int parent[MAX], e = 0;
struct Edge {
    int o, d, weight;
};

void adjust(struct Edge cost[], int i, int n) {
    int j = 2 * i;
    struct Edge item = cost[i];
    while (j <= n) {
        if (j < n && (cost[j].weight > cost[j + 1].weight ||
                      (cost[j].weight == cost[j + 1].weight && cost[j].o > cost[j + 1].o))) {
            j = j + 1;
        }
        if (item.weight <= cost[j].weight) {
            break;
        }
        cost[j / 2] = cost[j];
        j = 2 * j;
    }
    cost[j / 2] = item;
}
void heapify(struct Edge cost[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        adjust(cost, i, n);
    }
}
int delMin(struct Edge cost[], int *n, struct Edge *x) {
    if (*n == 0) {
        printf("\nHeap Empty\n");
        return 0;
    }
    *x = cost[1];
    cost[1] = cost[*n];
    (*n)--;
    adjust(cost, 1, *n);
    return 1;
}

int find(int i) {
    if (parent[i] < 0) {
        return i;
    }
    return parent[i] = find(parent[i]); 
}

void Union(int i, int j) {
    parent[i] = j;
}

void kruskal(struct Edge cost[MAX], int n, int e) {
    int i, mincost = 0, z;
    struct Edge x;
    int mst[MAX][2]; 
    heapify(cost, e);
    for (i = 1; i <= n; i++) {
        parent[i] = -1; 
    }

    i = 0;
    while (i < n - 1 && e > 0) {
        if (delMin(cost, &e, &x)) {
            int j = find(x.o);
            int k = find(x.d);

            if (j != k) {
                mst[i][0] = x.o;
                mst[i][1] = x.d;
                mincost += x.weight;
                Union(j, k);
                i++;
                printf("\nEdge %d: (%d - %d) Cost: %d\n", i, x.o, x.d, x.weight);

                printf("Parent Array: [ ");
                for (z = 1; z <= n; z++) {
                    printf("%d ", parent[z]);
                }
                printf("]\nMinimum Cost: %d\n", mincost);
            }
        }
    }

    if (i != n - 1) {
        printf("\nNo Spanning Tree Possible\n");
    } else {
        printf("\nEdges in Minimum Spanning Tree:\n");
        for (i = 0; i < n - 1; i++) {
            printf("%d - %d\n", mst[i][0], mst[i][1]);
        }
        printf("Total Minimum Cost: %d\n", mincost);
    }
}

int main() {
       
    printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

 
    int n, i, ori, des, we;
    struct Edge cost[MAX];
    clock_t start, end;
    double time_taken;

    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);

    for (i = 1; i <= n * (n - 1) / 2; i++) {
        printf("Enter edge %d (-1, -1 to quit): ", i);
        scanf("%d%d", &ori, &des);
        if (ori == -1 && des == -1) {
            break;
        }
        if (ori > n || des > n || ori < 1 || des < 1) {
            printf("\nInvalid Input! Try Again.\n");
            i--;
        } else {
            printf("Enter cost of edge: ");
            scanf("%d", &we);
            cost[i].o = ori;
            cost[i].d = des;
            cost[i].weight = we;
            e++;
        }
    }
    start = clock();
    kruskal(cost, n, e);
    end = clock();
    time_taken = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nTime Taken: %.6f seconds\n", time_taken);
    return 0;
}
