#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef short bool;

struct graph{
    int start, end, weight;
};

struct spanningTree{
    int start, end;
};

int cmp(const void *a, const void *b){
    const struct graph *graphA = a;
    const struct graph *graphB = b;
    return (graphA->weight > graphB->weight) - (graphA->weight < graphB->weight);
}

void Unification(int* setOfEdges, int start, int end, struct spanningTree *spanningTree, int edge){
    setOfEdges[end] = setOfEdges[start];
    for (int i = edge; i > 0; i--){
        if (spanningTree[i].start == end){
            Unification(setOfEdges, end, spanningTree[i].end, spanningTree, edge);
        }
    }
}

int* Kruskal(struct graph* graph, struct spanningTree* spanningTree, int* ans, int N, int M){
    int* setOfEdges = (int*)malloc(sizeof(int) * (N + 1));
    for (int i = 0; i < N + 1; i++)
        setOfEdges[i] = 0;
    int numOfGraph = 0, newEdge = 0, nodes = 0, numOfUnion = 0;
    while(numOfGraph < M){

        bool loop = (setOfEdges[graph[numOfGraph].start] == setOfEdges[graph[numOfGraph].end]);
        bool newStart = (setOfEdges[graph[numOfGraph].start] == 0);
        bool newEnd = (setOfEdges[graph[numOfGraph].end] == 0);
        bool degenerate = (graph[numOfGraph].start == graph[numOfGraph].end);
        if (!loop ||((newStart && newEnd && !degenerate))){
            spanningTree[newEdge].start = graph[numOfGraph].start;
            spanningTree[newEdge].end = graph[numOfGraph].end;

            if (!newStart && !newEnd){
                Unification(setOfEdges, graph[numOfGraph].start, graph[numOfGraph].end, spanningTree, newEdge);
            }

            else if (!newStart){
                setOfEdges[graph[numOfGraph].end] = setOfEdges[graph[numOfGraph].start];
                nodes++;
            }
            else if (!newEnd){
                setOfEdges[graph[numOfGraph].start] = setOfEdges[graph[numOfGraph].end];
                nodes++;
            }
            else {
                numOfUnion++;
                setOfEdges[graph[numOfGraph].end] = numOfUnion;
                setOfEdges[graph[numOfGraph].start] = numOfUnion;
                nodes += 2;
            }
            numOfGraph++;
            newEdge++;
        }
        else
            numOfGraph++;
    }
    free(setOfEdges);
    ans[0] = nodes;
    ans[1] = newEdge;
    return &ans[0];
}

int main(){
    int N = 0;
    scanf("%d", &N);
    if ((N < 0) || (N > 5000))
    {
        printf("bad number of vertices");
        exit(0);
    }

    int M = -1;
    scanf("%d", &M);
    if (M == -1)
    {
        printf("bad number of lines");
        exit(0);
    }

    int validNumOfEdges = N * (N - 1) / 2;
    if ((M < 0) || (M > validNumOfEdges))
    {
        printf("bad number of edges");
        exit(0);
    }

    struct graph *graph;
    graph = (struct graph*)malloc(M*sizeof(graph));
    int edgeStart = 0;
    int edgeEnd = 0;
    int edgeWeight = 0;
    for (int i = 0; i < M; i++)
    {
        edgeStart = edgeEnd = edgeWeight = 0;
        scanf("%d %d %d", &edgeStart, &edgeEnd, &edgeWeight);
        if ((edgeEnd == 0) || (edgeStart == 0) || (edgeWeight == 0))
        {
            printf("bad number of lines");
            exit(0);
        }
        if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > N) || (edgeWeight > INT_MAX))
        {
            printf("bad vertex");
            exit(0);
        }
        graph[i].start = edgeStart;
        graph[i].end = edgeEnd;
        graph[i].weight = edgeWeight;
    }
    qsort(graph, (size_t) M, sizeof(struct graph), cmp);

    struct spanningTree *spanningTree;
    spanningTree = (struct spanningTree*)malloc((N-1) * sizeof(spanningTree));

    int ans[2] = {0};
    int *p = Kruskal(graph, spanningTree, &ans[0], N, M);
    if (p[0] != N)
        printf ("no spanning tree");
    else{
        for (int i = 0; i < p[1]; i++){
            printf("%d ",spanningTree[i].start);
            printf("%d\n",spanningTree[i].end);
        }
    }

    free(graph);
    free(spanningTree);

    return 0;
}
