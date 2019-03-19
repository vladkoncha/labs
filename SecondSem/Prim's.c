#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NA_VIHOD 1
typedef short bool;

struct graph {
    int start;
    int end;
    unsigned int weight;
    int out;
};

struct graph *FindMin(struct graph *closestVertex, struct graph *graph, const int *check, int M){
    unsigned int minWeight = INT_MAX;
    closestVertex = NULL;
    bool endChecked = 0;
    bool startChecked = 0;
    for (int i = 0; i < M; i++){
        endChecked = (check[graph[i].end] == 1);
        startChecked = (check[graph[i].start] == 1);
        if (((startChecked && !endChecked) || (endChecked && !startChecked)) && (graph[i].weight <= minWeight) && (graph[i].weight != 0)){
            minWeight = graph[i].weight;
            closestVertex = &graph[i];
        }
    }
    if (closestVertex != NULL)
        closestVertex->out = 1;
    return closestVertex;
}

int Prim(struct graph *graph, int N, int M){
    int numOfVertices = 1;
    struct graph *closestVertex = NULL;
    struct graph *ptr;
    int *check = (int*)malloc((N + 1) * sizeof(int));
    for (int i = 0; i < N + 1; i++)
        check[i] = 0;
    check[graph[0].start] = 1;
    while ((ptr = FindMin(closestVertex, graph, check, M))){
        ptr->weight = 0;
        check[ptr->start] = 1;
        check[ptr->end] = 1;
        numOfVertices++;
    }
    free(check);
    return numOfVertices;
}

int main() {
    int N = 0;
    scanf("%d", &N);
    if ((N < 0) || (N > 5000)) {
        printf("bad number of vertices");
        exit(0);
    }

    int M = -1;
    scanf("%d", &M);
    if (M == -1) {
        printf("bad number of lines");
        exit(0);
    }

    if (((N == 0)||(N > 1))&&(M == 0)) {
        printf("no spanning tree");
        return 0;
    }

    int validNumOfEdges = N * (N - 1) / 2;
    if ((M < 0) || (M > validNumOfEdges)) {
        printf("bad number of edges");
        exit(0);
    }

    struct graph *graph;
    graph = (struct graph*)malloc(M * sizeof(struct graph));

    int edgeStart = 0;
    int edgeEnd = 0;
    unsigned int edgeWeight = 0;
    for (int i = 0; i < M; i++) {
        edgeStart = edgeEnd = 0;
        edgeWeight = 0;
        scanf("%d %d %u", &edgeStart, &edgeEnd, &edgeWeight);
        if ((edgeEnd == 0) || (edgeStart == 0) || (edgeWeight == 0)) {
            printf("bad number of lines");
            exit(0);
        }
        if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > N)) {
            printf("bad vertex");
            exit(0);
        }
        if ((edgeWeight > INT_MAX) || (edgeWeight < 0)) {
            printf("bad length");
            exit(0);
        }
        graph[i].start = edgeStart;
        graph[i].end = edgeEnd;
        graph[i].weight = edgeWeight;
    }

    if (M != 0)
        if (Prim(graph, N, M) != N){
            printf ("no spanning tree");
            exit(0);
        }

    for (int i = 0; i < M; i++)
        if (graph[i].out == NA_VIHOD)
            printf("%d %d\n", ((graph[i].start < graph[i].end) ? graph[i].start : graph[i].end), ((graph[i].start > graph[i].end) ? graph[i].start : graph[i].end));

    free(graph);
    return 0;
}
