#include <stdlib.h>
#include <stdio.h>

typedef struct vector vector;

struct array {
    int vertex;
    unsigned int weight;
};

struct vector {
    int mem;
    struct array *array;
    int size;

    int (*begin)(vector);

    int (*end)(vector);

    void (*push_back)(vector *, int, unsigned int);

    void (*remov)(vector *);
};

void push_back(vector *vector, int edgeEnd, unsigned int edgeWeight) {
    if (vector->size >= vector->mem) {
        vector->array = realloc(vector->array, sizeof(struct array) * vector->size * 2);
        vector->mem *= 2;
    }
    vector->array[vector->size].vertex = edgeEnd;
    vector->array[vector->size++].weight = edgeWeight;
}

int begin(vector vector) {
    return vector.array[0].vertex;
}

int end(vector vector) {
    if (vector.size > 0)
        return vector.array[vector.size - 1].vertex;
    return 0;
}

void remov(vector *vector) {
    if (vector->size > 0) {
        vector->array[--vector->size].vertex = 0;
        vector->array[vector->size].weight = 0;
    }
}

struct vector NewVector() {
    vector buff = {1, malloc(sizeof(struct array)), 0, &begin, &end, &push_back, &remov};
    return buff;
}

void FreeGraph(struct vector *graph, int N) {
    for (int i = 0; i < N; ++i)
        free(graph[i].array);
    free(graph);
}

int main() {
    FILE *in = fopen("in.txt", "r");
    FILE *out = fopen("out.txt", "w");
    int N = 0;
    fscanf(in, "%d", &N);
    if ((N < 0) || (N > 5000)) {
        fprintf(out, "bad number of vertices");
        fclose(in);
        fclose(out);
        exit(0);
    }

    int M = -1;
    fscanf(in, "%d", &M);
    if (M == -1) {
        fprintf(out, "bad number of lines");
        fclose(in);
        fclose(out);
        exit(0);
    }

    if (((N == 0) || (N > 1)) && (M == 0)) {
        fprintf(out, "no spanning tree");
        fclose(in);
        fclose(out);
        return 0;
    }

    int validNumOfEdges = N * (N - 1) / 2;
    if ((M < 0) || (M > validNumOfEdges)) {
        fprintf(out, "bad number of edges");
        fclose(in);
        fclose(out);
        exit(0);
    }

    vector *graph;
    graph = malloc(sizeof(vector) * N);
    for (int i = 0; i < N; ++i)
        graph[i] = NewVector();

    int edgeStart = 0;
    int edgeEnd = 0;
    unsigned int edgeWeight = 0;
    for (int i = 0; i < M; i++) {
        edgeStart = edgeEnd = 0;
        edgeWeight = 0;
        fscanf(in, "%d %d %u", &edgeStart, &edgeEnd, &edgeWeight);
        if ((edgeEnd == 0) || (edgeStart == 0) || (edgeWeight == 0)) {
            fprintf(out, "bad number of lines");
            fclose(in);
            fclose(out);
            FreeGraph(graph, N);
            exit(0);
        }
        if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > N)) {
            fprintf(out, "bad vertex");
            fclose(in);
            fclose(out);
            FreeGraph(graph, N);
            exit(0);
        }
        if ((edgeWeight > INT_MAX) || (edgeWeight < 0)) {
            fprintf(out, "bad length");
            fclose(in);
            fclose(out);
            FreeGraph(graph, N);
            exit(0);
        }
        graph[edgeStart - 1].push_back(&graph[edgeStart - 1], edgeEnd - 1, edgeWeight);
    }

    fclose(in);
    fclose(out);
    FreeGraph(graph, N);
    return 0;
}
