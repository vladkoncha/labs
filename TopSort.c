#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#define MAX_VERTEX 1001
#define HAVE_CONNECTION 1

typedef short boolean;

enum colours {WHITE = 0, GREY, BLACK};

struct SortedGraph
{
    int elem[MAX_VERTEX];
    int top;
};

void Init(struct SortedGraph* stk)
{
    stk->top = 0;
}

void Push(struct SortedGraph* stk, int vertex)
{
    if (stk->top < MAX_VERTEX)
    {
        stk->elem[stk->top] = vertex+1;
        stk->top++;
    } else
        printf("Стек полон\n%d", stk->top);
}

int Pop(struct SortedGraph *stk)
{
    int topVertex = 0;
    if ((stk->top) > 0)
    {
        stk->top--;
        topVertex = stk->elem[stk->top];
        return topVertex;
    }
    else return -1;
}

void Sort(struct SortedGraph* stk, int** adjMatrix, boolean* checked, int currentVertex, int N)
{
    if (checked[currentVertex] == BLACK)
        return;
    if (checked[currentVertex] == GREY)
    {
        printf_s("impossible to sort");
        exit(0);
    }
    if (checked[currentVertex] == WHITE)
    {
        checked[currentVertex] = GREY;
        for (int adjVertex = 0; adjVertex < N; adjVertex++)
        {
            if (adjMatrix[currentVertex][adjVertex] == HAVE_CONNECTION)
                Sort(stk, adjMatrix, checked, adjVertex, N);
        }
        checked[currentVertex] = BLACK;
        Push(stk, currentVertex);
    }
}


int main()
{
    int N = 0;
    scanf_s("%d", &N);
    if ((N < 0) || (N > 1000)) {
        printf_s("bad number of vertices");
        exit(0);
    }

    int M = 0;
    scanf_s("%d", &M);
    if (M == 0)
    {
        printf_s("bad number of lines");
        exit(0);
    }


    int validNumOfEdges = N*(N-1)/2;
    if ((M < 0) || (M > validNumOfEdges)) {
        printf_s("bad number of edges");
        exit(0);
    }

    int **adjMatrix;
    adjMatrix = (int **)malloc(N*sizeof(int*));
    for(int i = 0; i < N; i++)
    {
        adjMatrix[i] = (int *)malloc(N*sizeof(int));
    }

    int edgeStart = 0;
    int edgeEnd = 0;
    for(int i = 0; i < M; i++)
    {
        edgeStart = edgeEnd = 0;
        scanf_s("%d %d", &edgeStart, &edgeEnd);
        if ((edgeEnd == 0) || (edgeStart == 0))
        {
            printf_s("bad number of lines");
            exit(0);
        }
        if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > 1000))
        {
            printf_s("bad vertex");
            exit(0);
        }
        adjMatrix[edgeStart - 1][edgeEnd - 1] = HAVE_CONNECTION;
    }

    boolean *checked;
    checked = (boolean *)malloc((sizeof(boolean))*N);
    for (int i = 0; i<N; i++)
        checked[i] = WHITE;

    struct SortedGraph *stk;
    stk = (struct SortedGraph*)malloc(sizeof(struct SortedGraph));
    Init(stk);
    for (int k = 0; k<N; k++)
        Sort(stk, adjMatrix, checked, k, N);

    for (int i = 0; i < N; i++)
        printf_s("%d ", Pop(stk));

    for(int i = 0; i < N; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);

    return 0;
}
