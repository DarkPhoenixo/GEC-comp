#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#define MAX 100
#define INF 99999
int dist[MAX], parent[MAX];
bool s[MAX];

int minDist(int n) {
    int min = INF, index = -1, i;
    for (i = 1; i <= n; i++) {
        if (!s[i] && dist[i] < min) {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

void printPath(int j) {
    if (parent[j] == -1) {
        printf("%d ", j);
        return;
    }
    printPath(parent[j]);
    printf("-> %d ", j);
}

void shortestPath(int n, int cost[MAX][MAX], int v) {
    int i, j, w;
    for (i = 1; i <= n; i++) {
        s[i] = false;
        dist[i] = cost[v][i];
        parent[i] = (cost[v][i] != INF && v != i) ? v : -1;
    }
    s[v] = true;
    dist[v] = 0;

    printf("\n\nIteration 1\tv = %d\n", v);
    for (j = 1; j <= n; j++) {
        if (s[j] == true) printf("s[%d] = ", j);
    }
    printf("TRUE\n");
    for (j = 1; j <= n; j++) {
        if (s[j] == false) printf("s[%d] = ", j);
    }
    printf("FALSE\nDist Array: [ ");
    for (j = 1; j <= n; j++) {
        if (dist[j] == INF) printf("INF ");
        else printf("%d ", dist[j]);
    }
    printf("]\n");

    for (i = 2; i <= n; i++) {
        int u = minDist(n);
        if (u == -1) break;
        s[u] = true;

        printf("\n\nIteration %d\tu = %d\n", i, u);
        for (j = 1; j <= n; j++) {
            if (s[j] == true) printf("s[%d] = ", j);
        }
        printf("TRUE\n");
        for (j = 1; j <= n; j++) {
            if (s[j] == false) printf("s[%d] = ", j);
        }
        printf("FALSE\nDist Array: [ ");

        for (w = 1; w <= n; w++) {
            if (!s[w] && cost[u][w] && dist[u] != INF && dist[w] > dist[u] + cost[u][w]) {
                dist[w] = dist[u] + cost[u][w];
                parent[w] = u;
            }
        }

        for (j = 1; j <= n; j++) {
            if (dist[j] == INF) printf("INF ");
            else printf("%d ", dist[j]);
        }
        printf("]\n");
    }k
}

int main() {
       
    printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");

 
    int n, maxE, i, j, o, d, w, start;
    int cost[MAX][MAX];

    printf("\nEnter the number of vertices: ");
    scanf("%d", &n);
    maxE = n * (n - 1);

    for (i = 1; i <= n; i++) {
        for (j = 1; j <= n; j++) {
            cost[i][j] = INF;
        }
    }

    for (i = 1; i <= maxE; i++) {
        printf("Enter edge %d (-1, -1 to quit): ", i);
        scanf("%d%d", &o, &d);
        if (o == -1 && d == -1) {
            break;
        }
        if (o > n || d > n || o < 0 || d < 0) {
            printf("\nInvalid Input");
            i--;
        } else {
            printf("Enter weight of edge: ");
            scanf("%d", &w);
            cost[o][d] = w;
        }
    }

    printf("\nEnter the starting vertex: ");
    scanf("%d", &start);
    clock_t start_time = clock();
    shortestPath(n, cost, start);
    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

    printf("\n\n%-10s %-12s %-16s %-30s\n", "Source", "Destination", "Path Length", "Path");
    printf("--------------------------------------------------------------\n");
    for (i = 1; i <= n; i++) {
        if (i != start) {
            printf("%-10d %-12d ", start, i);
            if (dist[i] == INF) {
                printf("%-16s %-30s\n", "INF", "No path");
            } else {
                printf("%-16d ", dist[i]);
                printPath(i);
                printf("\n");
       }}}
    printf("\nTime taken: %.6f seconds\n", time_taken);
    return 0;
}
