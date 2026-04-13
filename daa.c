#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF INT_MAX

void dijkstra(int graph[MAX][MAX], int n, int src, const char *resultFile);
void bellmanFord(int graph[MAX][MAX], int n, int src, const char *resultFile);
void floydWarshall(int graph[MAX][MAX], int n, const char *resultFile);
void loadGraphFromFile(int graph[MAX][MAX], int *n, const char *filename);
void saveGraphToFile(int graph[MAX][MAX], int n, const char *filename);
void generateRandomGraph(int graph[MAX][MAX], int n, double density, int maxWeight);
void performanceComparison(int graph[MAX][MAX], int n, int src, const char *resultFile);
void visualizeGraph(int graph[MAX][MAX], int n);
void visualizePerformance(double dijkstraTime, double bellmanTime, double floydTime);

int main() {
    int n, choice, src;
    int graph[MAX][MAX];
    char filename[100], resultFile[100];

    printf("=== Shortest Distance Computation ===\n");
    printf("1. Load graph from file\n2. Generate random graph\nChoose option: ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter the filename to load graph data: ");
        scanf("%s", filename);
        loadGraphFromFile(graph, &n, filename);
    } else if (choice == 2) {
        double density;
        int maxWeight;
        printf("Enter number of vertices (max %d): ", MAX);
        scanf("%d", &n);
        printf("Enter graph density (0.0 to 1.0): ");
        scanf("%lf", &density);
        printf("Enter max edge weight (positive integer): ");
        scanf("%d", &maxWeight);

        generateRandomGraph(graph, n, density, maxWeight);
        saveGraphToFile(graph, n, "generated_graph.txt");
        printf("Generated graph saved to 'generated_graph.txt'\n");
    } else {
        printf("Invalid option. Exiting.\n");
        return 1;
    }

    printf("Enter the filename to save results: ");
    scanf("%s", resultFile);

    while (1) {
        printf("\n--- Shortest Path Algorithms ---\n");
        printf("1. Dijkstra\n2. Bellman-Ford\n3. Floyd-Warshall\n4. Performance Comparison (all 3)\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        if (choice == 1 || choice == 2) {
            printf("Enter the source vertex (0 to %d): ", n - 1);
            scanf("%d", &src);
            if (src < 0 || src >= n) {
                printf("Invalid source vertex.\n");
                continue;
            }
        }

        switch (choice) {
            case 1:
                dijkstra(graph, n, src, resultFile);
                break;
            case 2:
                bellmanFord(graph, n, src, resultFile);
                break;
            case 3:
                floydWarshall(graph, n, resultFile);
                break;
            case 4:
                printf("Enter the source vertex for single-source algorithms (0 to %d): ", n - 1);
                scanf("%d", &src);
                if (src < 0 || src >= n) {
                    printf("Invalid source vertex.\n");
                    continue;
                }
                performanceComparison(graph, n, src, resultFile);
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    visualizeGraph(graph, n);

    printf("Enter the filename to save results: ");
    scanf("%s", resultFile);

    while (1) {
        printf("\n--- Shortest Path Algorithms ---\n");
        printf("1. Dijkstra\n2. Bellman-Ford\n3. Floyd-Warshall\n4. Performance Comparison (all 3)\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 5) {
            printf("Exiting...\n");
            break;
        }

        if (choice == 1 || choice == 2 || choice == 4) {
            printf("Enter the source vertex (0 to %d): ", n - 1);
            scanf("%d", &src);
            if (src < 0 || src >= n) {
                printf("Invalid source vertex.\n");
                continue;
            }
        }

        switch (choice) {
            case 1:
                dijkstra(graph, n, src, resultFile);
                break;
            case 2:
                bellmanFord(graph, n, src, resultFile);
                break;
            case 3:
                floydWarshall(graph, n, resultFile);
                break;
            case 4:
                performanceComparison(graph, n, src, resultFile);
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
// Load graph from file
void loadGraphFromFile(int graph[MAX][MAX], int *n, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", n);
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            fscanf(file, "%d", &graph[i][j]);

    fclose(file);
}

// Save graph to file
void saveGraphToFile(int graph[MAX][MAX], int n, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open %s for writing\n", filename);
        exit(1);
    }

    fprintf(file, "%d\n", n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fprintf(file, "%d ", graph[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

// Generate random graph
void generateRandomGraph(int graph[MAX][MAX], int n, double density, int maxWeight) {
    srand(time(NULL));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (i == j)
                graph[i][j] = 0;
            else {
                double r = (double)rand() / RAND_MAX;
                if (r < density)
                    graph[i][j] = 1 + rand() % maxWeight;
                else
                    graph[i][j] = INF; // No edge
            }
        }
}


// Visualize Graph
void visualizeGraph(int graph[MAX][MAX], int n) {
    printf("\nGraph Visualization:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF)
                printf(" INF ");
            else
                printf(" %4d ", graph[i][j]);
        }
        printf("\n");
    }
}

// Visualize Performance Comparison
void visualizePerformance(double dijkstraTime, double bellmanTime, double floydTime) {
    printf("\nPerformance Comparison (Execution Time):\n");
    printf("Dijkstra       : "); for (int i = 0; i < dijkstraTime * 100; i++) printf("#"); printf(" %.6fs\n", dijkstraTime);
    printf("Bellman-Ford    : "); for (int i = 0; i < bellmanTime * 100; i++) printf("#"); printf(" %.6fs\n", bellmanTime);
    printf("Floyd-Warshall  : "); for (int i = 0; i < floydTime * 100; i++) printf("#"); printf(" %.6fs\n", floydTime);
}

// Dijkstra Algorithm
void dijkstra(int graph[MAX][MAX], int n, int src, const char *resultFile) {
    int dist[MAX], visited[MAX] = {0};
    FILE *file = fopen(resultFile, "a");
    clock_t start = clock();

    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++) {
        int min = INF, u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && dist[j] < min)
                min = dist[j], u = j;

        if (u == -1) break; // Remaining vertices unreachable

        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }

    clock_t end = clock();

    fprintf(file, "\nDijkstra's Algorithm (Source: %d)\n", src);
    for (int i = 0; i < n; i++) {
        if(dist[i] == INF)
            fprintf(file, "%d -> %d : INF\n", src, i);
        else
            fprintf(file, "%d -> %d : %d\n", src, i, dist[i]);
    }
    fprintf(file, "Execution Time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    fclose(file);
}

// Bellman-Ford Algorithm
void bellmanFord(int graph[MAX][MAX], int n, int src, const char *resultFile) {
    int dist[MAX];
    FILE *file = fopen(resultFile, "a");
    clock_t start = clock();

    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[src] = 0;

    for (int i = 0; i < n - 1; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v])
                    dist[v] = dist[u] + graph[u][v];

    // Check for negative weight cycle
    for (int u = 0; u < n; u++)
        for (int v = 0; v < n; v++)
            if (graph[u][v] != INF && dist[u] != INF && dist[u] + graph[u][v] < dist[v]) {
                fprintf(file, "\nGraph contains negative weight cycle\n");
                fclose(file);
                return;
            }

    clock_t end = clock();

    fprintf(file, "\nBellman-Ford Algorithm (Source: %d)\n", src);
    for (int i = 0; i < n; i++) {
        if(dist[i] == INF)
            fprintf(file, "%d -> %d : INF\n", src, i);
        else
            fprintf(file, "%d -> %d : %d\n", src, i, dist[i]);
    }
    fprintf(file, "Execution Time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    fclose(file);
}

// Floyd-Warshall Algorithm
void floydWarshall(int graph[MAX][MAX], int n, const char *resultFile) {
    int dist[MAX][MAX];
    clock_t start = clock();

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dist[i][j] = graph[i][j];

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];

    clock_t end = clock();

    FILE *file = fopen(resultFile, "a");
    fprintf(file, "\nFloyd-Warshall Algorithm (All-Pairs)\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                fprintf(file, "INF ");
            else
                fprintf(file, "%d ", dist[i][j]);
        }
        fprintf(file, "\n");
    }

    fprintf(file, "\nExecution Time: %.6f seconds\n\n", (double)(end - start) / CLOCKS_PER_SEC);
    fclose(file);
}


void performanceComparison(int graph[MAX][MAX], int n, int src, const char *resultFile) {
    clock_t start, end;
    double timeDijkstra, timeBellman, timeFloyd;

    int distDijkstra[MAX], distBellman[MAX], distFloyd[MAX][MAX];

    // Dijkstra timing
    start = clock();
    int visited[MAX] = {0};
    for (int i = 0; i < n; i++) distDijkstra[i] = INF;
    distDijkstra[src] = 0;
    for (int i = 0; i < n - 1; i++) {
        int min = INF, u = -1;
        for (int j = 0; j < n; j++)
            if (!visited[j] && distDijkstra[j] < min)
                min = distDijkstra[j], u = j;
        if (u == -1) break;
        visited[u] = 1;
        for (int v = 0; v < n; v++)
            if (!visited[v] && graph[u][v] != INF && distDijkstra[u] != INF && distDijkstra[u] + graph[u][v] < distDijkstra[v])
                distDijkstra[v] = distDijkstra[u] + graph[u][v];
    }
    end = clock();
    timeDijkstra = (double)(end - start) / CLOCKS_PER_SEC;

    // Bellman-Ford timing
    start = clock();
    for (int i = 0; i < n; i++) distBellman[i] = INF;
    distBellman[src] = 0;
    for (int i = 0; i < n - 1; i++)
        for (int u = 0; u < n; u++)
            for (int v = 0; v < n; v++)
                if (graph[u][v] != INF && distBellman[u] != INF && distBellman[u] + graph[u][v] < distBellman[v])
                    distBellman[v] = distBellman[u] + graph[u][v];
    // No negative cycle check here for speed
    end = clock();
    timeBellman = (double)(end - start) / CLOCKS_PER_SEC;

    // Floyd-Warshall timing
    start = clock();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            distFloyd[i][j] = graph[i][j];
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (distFloyd[i][k] != INF && distFloyd[k][j] != INF && distFloyd[i][k] + distFloyd[k][j] < distFloyd[i][j])
                    distFloyd[i][j] = distFloyd[i][k] + distFloyd[k][j];
    end = clock();
    timeFloyd = (double)(end - start) / CLOCKS_PER_SEC;

    FILE *file = fopen(resultFile, "a");
    fprintf(file, "\nPerformance Comparison (Source vertex: %d)\n", src);

    fprintf(file, "Algorithm         Execution Time (seconds)\n");
    fprintf(file, "-----------------------------------------\n");
    fprintf(file, "Dijkstra          %.6f\n", timeDijkstra);
    fprintf(file, "Bellman-Ford      %.6f\n", timeBellman);
    fprintf(file, "Floyd-Warshall    %.6f\n\n", timeFloyd);

    fclose(file);

    printf("Performance comparison completed. Check '%s' for details.\n", resultFile);
}