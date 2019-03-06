#include <stdio.h>
#include <stdlib.h>

struct Edge{
    int start, end, weight;
};

struct Graph{
    int N, M;
    struct Edge* edge;
};

struct Graph* CreateGraph(int N, int M){
    struct Graph* graph = malloc(sizeof(*graph));
    graph->N = N;
    graph->M = M;

    graph->edge = malloc(M*sizeof(graph->edge));

    return graph;
}

struct subset{
    int parent;
    int rank;
};

int Find(struct subset subsets[], int i){
    if (subsets[i].parent != i)
        subsets[i].parent = Find(subsets, subsets[i].parent);
    return  subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y){
    int xroot = Find(subsets, x);
    int yroot = Find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank)
        subsets[xroot].parent = yroot;
    else if (subsets[xroot].rank > subsets[yroot].rank)
        subsets[yroot].parent = xroot;
    else{
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

int MyComp(const void* a, const void* b){
    struct Edge* a1 = (struct Edge*)a;
    struct Edge* b1 = (struct Edge*)b;
    return a1->weight > b1->weight;
}

void KruskalMST(struct Graph* graph){
    int N = graph->N;
    struct Edge result[N];
    int e = 0;
    int i = 0;

    qsort(graph->edge, (size_t) graph->M, sizeof(graph->edge[0]), MyComp);

    struct subset* subsets = (struct subset*)malloc(N*sizeof(struct subset));

    for (int n = 0; n < N; ++n ){
        subsets[n].parent = n;
        subsets[n].rank = 0;
    }

    while (e < (N - 1)){
        struct Edge next_edge = graph->edge[i++];
        int x = Find(subsets, next_edge.start);
        int y = Find(subsets, next_edge.end);

        if (x != y){
            result[e++] = next_edge;
            Union(subsets, x, y);
        }
    }

    for (i = 0; i < e; ++i)
        printf("%d %d %d\n", result[i].start, result[i].end, result[i].weight);

}

int main() {

    int N = 0;
    scanf_s("%d", &N);
    if ((N < 0) || (N > 5000))
    {
        printf_s("bad number of vertices");
        exit(0);
    }

    int M = -1;
    scanf_s("%d", &M);
    if (M == -1)
    {
        printf_s("bad number of lines");
        exit(0);
    }


    int validNumOfEdges = N * (N + 1) / 2;
    if ((M < 0) || (M > validNumOfEdges))
    {
        printf_s("bad number of edges");
        exit(0);
    }

    struct Graph* graph = CreateGraph(N, M);

    int edgeStart = 0;
    int edgeEnd = 0;
    int edgeWeight = 0;
    for (int i = 0; i < M; i++)
    {
        edgeStart = edgeEnd = edgeWeight = 0;
        scanf_s("%d %d %d", &edgeStart, &edgeEnd, &edgeWeight);
        if ((edgeEnd == 0) || (edgeStart == 0))
        {
            printf_s("bad number of lines");
            exit(0);
        }
        if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > N))
        {
            printf_s("bad vertex");
            exit(0);
        }
        graph->edge[i].start = edgeStart;
        graph->edge[i].end = edgeEnd;
        graph->edge[i].weight = edgeWeight;
    }

    KruskalMST(graph);


    return 0;
}
