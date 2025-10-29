#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>

#define MAXV 100
#define MAXS 20
#define MAXE 1000

typedef struct {
    int from;
    int to;
    int cost;
} Edge;

void print_forward_calculations(Edge edges[], int edge_count, int k, int n, int fcost[], int d[]) {
    printf("\nForward Approach - Detailed Calculations:\n");
    // Create an array to store stage of each vertex
    int vertex_stage[MAXV];
    
    // Initialize vertex stages
    for (int i = 1; i <= n; i++) {
        if (i == 1) vertex_stage[i] = 1;
        else if (i == n) vertex_stage[i] = k;
        else {
            // Determine stage based on your vertex distribution
            for (int stage = 2; stage < k; stage++) {
                if (i >= 2 && i <= 5) vertex_stage[i] = 2;
                else if (i >= 6 && i <= 9) vertex_stage[i] = 3;
                else if (i >= 10 && i <= 13) vertex_stage[i] = 4;
                else vertex_stage[i] = -1; // Unknown stage
            }
        }
    }
    
    // Process vertices in reverse order (from stage k-1 to 1)
    for (int stage = k-1; stage >= 1; stage--) {
        printf("\n--- STAGE %d ---\n", stage);
        
        // Process all vertices in this stage
        for (int j = 1; j < n; j++) {
            if (vertex_stage[j] == stage) {
                printf("Vertex %d:\n", j);
                printf("fcost(%d,%d) = min{", stage, j);
                
                int first = 1;
                for (int e = 0; e < edge_count; e++) {
                    if (edges[e].from == j) {
                        if (!first) printf(", ");
                        printf("c(%d,%d)+fcost(%d,%d)=%d+%d=%d", 
                              j, edges[e].to, stage+1, edges[e].to, edges[e].cost, fcost[edges[e].to], 
                              edges[e].cost + fcost[edges[e].to]);
                        first = 0;
                    }
                }
                printf("} = %d\n", fcost[j]);
                printf("d(%d,%d) = %d\n\n", stage, j, d[j]);
            }
        }
    }
}

void print_backward_calculations(Edge edges[], int edge_count, int k, int n, int bcost[], int d[]) {
    printf("\nBackward Approach - Detailed Calculations:\n");
    // Create an array to store stage of each vertex
    int vertex_stage[MAXV];
    
    // Initialize vertex stages
    for (int i = 1; i <= n; i++) {
        if (i == 1) vertex_stage[i] = 1;
        else if (i == n) vertex_stage[i] = k;
        else {
            // Determine stage based on your vertex distribution
            for (int stage = 2; stage < k; stage++) {
                if (i >= 2 && i <= 5) vertex_stage[i] = 2;
                else if (i >= 6 && i <= 9) vertex_stage[i] = 3;
                else if (i >= 10 && i <= 13) vertex_stage[i] = 4;
                else vertex_stage[i] = -1; // Unknown stage
            }
        }
    }
    
    // Process vertices in forward order (from stage 2 to k)
    for (int stage = 2; stage <= k; stage++) {
        printf("\n--- STAGE %d ---\n", stage);
        
        // Process all vertices in this stage
        for (int j = 2; j <= n; j++) {
            if (vertex_stage[j] == stage) {
                printf("Vertex %d:\n", j);
                printf("bcost(%d,%d) = min{", stage, j);
                
                int first = 1;
                for (int e = 0; e < edge_count; e++) {
                    if (edges[e].to == j) {
                        if (!first) printf(", ");
                        printf("bcost(%d,%d)+c(%d,%d)=%d+%d=%d", 
                              stage-1, edges[e].from, edges[e].from, j, 
                              bcost[edges[e].from], edges[e].cost, 
                              bcost[edges[e].from] + edges[e].cost);
                        first = 0;
                    }
                }
                printf("} = %d\n", bcost[j]);
                printf("d(%d,%d) = %d\n\n", stage, j, d[j]);
            }
        }
    }
}


void forward(Edge edges[], int edge_count, int k, int n, int p[], int show_steps) {
    clock_t start = clock();
    int fcost[MAXV], d[MAXV];
    fcost[n] = 0;
    d[n] = -1;
    
    for (int j = 1; j < n; j++) fcost[j] = INT_MAX;
    
    for (int j = n-1; j >= 1; j--) {
        for (int e = 0; e < edge_count; e++) {
            if (edges[e].from == j && edges[e].cost + fcost[edges[e].to] < fcost[j]) {
                fcost[j] = edges[e].cost + fcost[edges[e].to];
                d[j] = edges[e].to;
            }
        }
    }
    
    if (show_steps) print_forward_calculations(edges, edge_count, k, n, fcost, d);
    
    p[1] = 1;
    p[k] = n;
    for (int j = 2; j <= k-1; j++) p[j] = d[p[j-1]];
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nForward Approach Results:\n");
    printf("Minimum cost: %d\n", fcost[1]);
    printf("Shortest path: ");
    for (int i = 1; i <= k; i++) printf("%d ", p[i]);
    printf("\nPath details:\n");
    for (int i = 1; i < k; i++) {
        int edge_cost = 0;
        for (int e = 0; e < edge_count; e++) {
            if (edges[e].from == p[i] && edges[e].to == p[i+1]) {
                edge_cost = edges[e].cost;
                break;
            }
        }
        printf("Stage %d to %d: %d->%d (cost: %d)\n", 
              i, i+1, p[i], p[i+1], edge_cost);
    }
    printf("Execution time: %f seconds\n", time_taken);
}

void backward(Edge edges[], int edge_count, int k, int n, int p[], int show_steps) {
    clock_t start = clock();
    int bcost[MAXV], d[MAXV];
    bcost[1] = 0;
    d[1] = -1;
    
    for (int j = 2; j <= n; j++) bcost[j] = INT_MAX;
    
    for (int j = 2; j <= n; j++) {
        for (int e = 0; e < edge_count; e++) {
            if (edges[e].to == j && bcost[edges[e].from] + edges[e].cost < bcost[j]) {
                bcost[j] = bcost[edges[e].from] + edges[e].cost;
                d[j] = edges[e].from;
            }
        }
    }
    
    if (show_steps) print_backward_calculations(edges, edge_count, k, n, bcost, d);
    
    p[1] = 1;
    p[k] = n;
    for (int j = k-1; j >= 2; j--) p[j] = d[p[j+1]];
    
    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    
    printf("\nBackward Approach Results:\n");
    printf("Minimum cost: %d\n", bcost[n]);
    printf("Shortest path: ");
    for (int i = k; i >= 1; i--) printf("%d ", p[i]);
    printf("\nPath details:\n");
    for (int i = k-1; i >= 1; i--) {
        int edge_cost = 0;
        for (int e = 0; e < edge_count; e++) {
            if (edges[e].from == p[i] && edges[e].to == p[i+1]) {
                edge_cost = edges[e].cost;
                break;
            }
        }
        printf("Stage %d to %d: %d->%d (cost: %d)\n", 
              i, i+1, p[i], p[i+1], edge_cost);
    }
    printf("Execution time: %f seconds\n", time_taken);
}

void show_edges(Edge edges[], int edge_count) {
    printf("\nEdge List:\n");
    printf("From To Cost\n");
    for (int i = 0; i < edge_count; i++) {
        printf("%4d %4d %4d\n", edges[i].from, edges[i].to, edges[i].cost);
    }
}

int main() {
        printf ("*****************************************************");
    printf ("\n Roll number: 23B-CO-010\n");
    printf (" PR Number - 202311390\n");
    printf("*****************************************************\n\n\n");
    int choice, k, n, p[MAXS], show_steps;
    Edge edges[MAXE];
    int edge_count = 0;
    
    printf("Multistage Graph Path Finder\n");
    
    while (1) {
        printf("\nMenu:\n");
        printf("1. Input Graph\n");
        printf("2. Run Forward Approach\n");
        printf("3. Run Backward Approach\n");
        printf("4. Show Edges\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                printf("Number of stages (k): ");
                scanf("%d", &k);
                printf("Number of vertices (n): ");
                scanf("%d", &n);
                
                printf("Enter edges (from to cost), -1 -1 -1 to finish:\n");
                edge_count = 0;
                while (1) {
                    printf("Edge %d: ", edge_count+1);
                    scanf("%d %d %d", &edges[edge_count].from, &edges[edge_count].to, &edges[edge_count].cost);
                    
                    if (edges[edge_count].from == -1 && edges[edge_count].to == -1 && edges[edge_count].cost == -1) {
                        break;
                    }
                    
                    edge_count++;
                    if (edge_count >= MAXE) {
                        printf("Maximum edges reached!\n");
                        break;
                    }
                }
                break;
            }
                
            case 2:
                if (edge_count == 0) printf("Please input graph first!\n");
                else {
                    printf("Show detailed calculations? (1=Yes, 0=No): ");
                    scanf("%d", &show_steps);
                    forward(edges, edge_count, k, n, p, show_steps);
                }
                break;
                
            case 3:
                if (edge_count == 0) printf("Please input graph first!\n");
                else {
                    printf("Show detailed calculations? (1=Yes, 0=No): ");
                    scanf("%d", &show_steps);
                    backward(edges, edge_count, k, n, p, show_steps);
                }
                break;
                
            case 4:
                if (edge_count == 0) printf("Please input graph first!\n");
                else show_edges(edges, edge_count);
                break;
                
            case 5:
                printf("Exiting...\n");
                exit(0);
                
            default:
                printf("Invalid choice!\n");
        }
    }
    
    return 0;
}