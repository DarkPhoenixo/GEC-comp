#include <stdio.h>
#include <limits.h>
#include <time.h>
#define MAX 10
#define INF INT_MAX
int k = 1, l;
void displayNear(int* near, int n, int cost[MAX][MAX]) {
    printf("\nnear: ");
    for (int i = 1; i <= n; i++) {
        printf("[%02d] ", i);
    }
    printf("\n       ");
    for (int i = 1; i <= n; i++) {
        printf("%2d   ", near[i]);
    }
    printf("\ncost:  ");
    for (int i = 1; i <= n; i++) {
        if (cost[i][near[i]] == INF) {
            printf("inf  ");
            continue;
        }
        if (near[i] == 0) {
            printf("--   ");
            continue;
        }
        printf("%2d   ", cost[i][near[i]]);
    }
    printf("\n");
}

void showmst(int n, int t[][2]) {
    printf("\nThe edges of the Minimum Spanning Tree (MST) are:\n");
    for (int i = 0; i < n - 1; i++) {
        printf("%d - %d\n", t[i][0], t[i][1]);
    }
}

void showcost(int cost[MAX][MAX], int n) {
    printf("\nThe cost adjacency matrix is:\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (cost[i][j] == INF) {
                printf("0 ");
            } else {
                printf("%d ", cost[i][j]);
            }
        }
        printf("\n");
    }
}

int prims(int t[][2], int size, int cost[MAX][MAX], int near[MAX]) {
    int mincost = cost[k][l];
    t[0][0] = k;
    t[0][1] = l;

    for (int i = 1; i <= size; i++) {
        if (cost[i][l] < cost[i][k]) {
            near[i] = l;
        } else {
            near[i] = k;
        }
    }
    near[k] = 0;
    near[l] = 0;

    displayNear(near, size, cost);

    for (int j = 1; j < size - 1; j++) {
        int min = INF;
        int nextVertex = -1;
        for (int i = 1; i <= size; i++) {
            if (near[i] != 0 && cost[i][near[i]] < min) {
                min = cost[i][near[i]];
                nextVertex = i;
            }
        }
        t[j][0] = nextVertex;
        t[j][1] = near[nextVertex];
        mincost += cost[nextVertex][near[nextVertex]];
        near[nextVertex] = 0;

        for (int i = 1; i <= size; i++) {
            if (near[i] != 0 && cost[i][near[i]] > cost[i][nextVertex]) {
                near[i] = nextVertex;
            }
        }
        displayNear(near, size, cost);
    }

    showcost(cost, size);
    showmst(size, t);
    return mincost;
}

int main() {
    
    printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

    int n;
    int cost[MAX][MAX];
    int t[MAX][2];
    int near[MAX];

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    printf("Enter the cost adjacency matrix (use 0 for no edge):\n");
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            cost[i][j] = (i == j) ? 0 : INF;
        }
    }
    printf("Enter the edges and their costs (enter -1 -1 to stop):\n");
    while (1) {
        int u, v, w;
        scanf("%d %d", &u, &v);
        if (u == -1 && v == -1) {
            break;
        }
        printf("Enter the cost of (%d, %d): ", u, v);
        scanf("%d", &w);
        cost[u][v] = w;
        cost[v][u] = w;
    }

    clock_t start = clock();

    int min = INF;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (cost[i][j] < min) {
                min = cost[i][j];
                k = i;
                l = j;
            }
        }
    }

    int mincost = prims(t, n, cost, near);

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nThe minimum cost is: %d\n", mincost);
    printf("Time taken: %.6f seconds\n", time_taken);
    return 0;
}

