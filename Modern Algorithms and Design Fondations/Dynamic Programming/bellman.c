#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

#define N 100
#define INF 99999

void printPath(int parent[], int j);


void displayIterationDistances(int n, int dist[N][N]) {
    printf("\nDistance table for each iteration (k):\n");
    
    
    printf("%5s", "k");
    for (int i = 1; i <= n; i++) {
        printf("%4d", i);
    }
    printf("\n");
    
    for (int i = 0; i <= n; i++) printf("----");
    printf("\n");
    
    
    for (int k = 0; k <= n; k++) {
        printf("%4d |", k);
        for (int j = 1; j <= n; j++) {
            if (dist[k][j] == INF)
                printf("  INF ");
            else
                printf("%3d ", dist[k][j]);
        }
        printf("\n");
    }
}


void displayFinalDistances(int n, int dist[N], int parent[N], int source) {
    printf("\nFinal shortest distances from source vertex %d:\n", source);
    printf("Vertex\tDistance\tPath\n");
    
    for (int i = 1; i <= n; i++) {
        if (i != source) {
            printf("%d\t", i);
            
            if (dist[i] == INF)
                printf("∞\t\tUnreachable\n");
            else {
                printf("%d\t\t%d", dist[i], source);
                printPath(parent, i);
                printf("\n");
            }
        }
    }
}


void printPath(int parent[], int j) {
    if (parent[j] == -1)
        return;
        
    printPath(parent, parent[j]);
    printf(" -> %d", j);
}


void initializeGraph(int n, int graph[][N]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else
                graph[i][j] = INF;
        }
    }
}


void displayGraph(int n, int graph[][N]) {
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 1; i <= n; i++)
        printf("%4d", i);
    printf("\n");
    
    for (int i = 1; i <= n; i++) {
        printf("%2d ", i);
        for (int j = 1; j <= n; j++) {
            if (graph[i][j] == INF)
                printf(" INF");
            else
                printf("%4d", graph[i][j]);
        }
        printf("\n");
    }
}


void inputGraph(int n, int graph[][N]) {
    printf("\nEnter the cost matrix (%d for infinity):\n", INF);
    
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                graph[i][j] = 0;  
                continue;
            }
            printf("cost[%d][%d]: ", i, j);
            scanf("%d", &graph[i][j]);
            if (graph[i][j] == INF) {
                printf("  (infinity)\n");
            }
        }
    }
}


void runBellmanFord(int n, int graph[][N], int source) {
    int dist[N][N]; 
    int finalDist[N]; 
    int parent[N]; 
    clock_t start, end;
    double cpu_time_used;
    bool has_negative_cycle = false;
    
  
    for (int i = 1; i <= n; i++)
        parent[i] = -1;
    
    start = clock();
    

    for (int i = 1; i <= n; i++) {
        if (i == source) {
            dist[0][i] = 0;
        } else {
            dist[0][i] = graph[source][i];
            if (graph[source][i] != INF)
                parent[i] = source;
        }
    }
    
  
    for (int k = 1; k <= n; k++) {
       
        for (int i = 1; i <= n; i++)
            dist[k][i] = dist[k-1][i];
        
        // Relax edges
        for (int v = 1; v <= n; v++) {
            if (v != source) {
                for (int u = 1; u <= n; u++) {
                    if (graph[u][v] != INF && dist[k-1][u] != INF &&
                        dist[k-1][u] + graph[u][v] < dist[k][v]) {
                        dist[k][v] = dist[k-1][u] + graph[u][v];
                        parent[v] = u;
                    }
                }
            }
        }
    }
    

    for (int i = 1; i <= n; i++)
        finalDist[i] = dist[n][i];
    

    for (int u = 1; u <= n; u++) {
        for (int v = 1; v <= n; v++) {
            if (graph[u][v] != INF && dist[n][u] != INF && 
                dist[n][u] + graph[u][v] < dist[n][v]) {
                has_negative_cycle = true;
                break;
            }
        }
        if (has_negative_cycle) break;
    }
    
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("\nExecution time: %.6f seconds\n", cpu_time_used);
    

    displayIterationDistances(n, dist);
    
  
    if (has_negative_cycle) {
        printf("\nWARNING: Graph contains negative weight cycle!\n");
    } else {
      
        displayFinalDistances(n, finalDist, parent, source);
    }
}

int main() {
        printf("*****************************************************\n");
    printf(" Roll number: 23B-CO-010\n");
    printf(" PR Number - 202311390\n");
    printf("*****************************************************\n\n");
    int choice, n, source;
    int graph[N][N];
    bool graphCreated = false;
    
    while (1) {
        printf("\n===== Bellman Ford Algorithm Menu =====\n");
        printf("1. Create Graph\n");
        printf("2. Run Bellman-Ford Algorithm\n");
        printf("3. Display Graph\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter number of vertices (max %d): ", N-1);
                scanf("%d", &n);
                
                if (n <= 0 || n >= N) {
                    printf("Invalid number of vertices!\n");
                    break;
                }
                
                initializeGraph(n, graph);
                inputGraph(n, graph);
                graphCreated = true;
                break;
                
            case 2:
                if (!graphCreated) {
                    printf("Please create a graph first!\n");
                    break;
                }
                
                printf("Enter source vertex (1 to %d): ", n);
                scanf("%d", &source);
                
                if (source < 1 || source > n) {
                    printf("Invalid source vertex!\n");
                    break;
                }
                
                runBellmanFord(n, graph, source);
                break;
                
            case 3:
                if (!graphCreated) {
                    printf("Please create a graph first!\n");
                    break;
                }
                
                displayGraph(n, graph);
                break;
                
            case 4:
                printf("Exiting program...\n");
                return 0;
                
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    
    return 0;
}
