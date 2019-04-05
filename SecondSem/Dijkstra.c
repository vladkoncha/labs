#define _CRT_SECURE_NO_WARNINGS
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define CHECKED 1
typedef struct vector vector;

struct array {
	int vertex;
	long long weight;
};

struct vector {
	int mem;
	struct array *array;
	int size;

	int(*begin)(vector);

	int(*end)(vector);

	void(*pushBack)(vector *, int, long long);

	void(*remov)(vector *);
};

void pushBack(vector *vector, int value, long long edgeWeight) {
	if (vector->size >= vector->mem) {
		vector->array =
			realloc(vector->array, sizeof(struct array) * vector->size * 2);
		vector->mem *= 2;
	}
	vector->array[vector->size].vertex = value;
	vector->array[vector->size].weight = edgeWeight;
	vector->size++;
}

int begin(vector vector) { return vector.array[0].vertex; }

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
	vector buff = {
		1, malloc(sizeof(struct array)), 0, &begin, &end, &pushBack, &remov };
	return buff;
}

void FreeGraph(struct vector *graph, int N) {
	for (int i = 0; i < N; ++i)
		free(graph[i].array);
	free(graph);
}

int overflowCounter = 0;
void Dijkstra(vector *graph, vector *marker, int N, int S, int F) {
	for (int i = 0; i < graph[S].size; i++) {
		if (graph[S].array[i].weight < marker->array[graph[S].array[i].vertex].weight)
			marker->array[graph[S].array[i].vertex].weight = graph[S].array[i].weight;
	}
	marker->array[S].vertex = CHECKED;
	int checked = 0;
	long long *vertexWeight = NULL;
	for (int currentVertex = 0; currentVertex < N; currentVertex++) {
		if (currentVertex == S)
			continue;
		for (int adjVertex = 0; adjVertex < graph[currentVertex].size; adjVertex++) {
			if (currentVertex == graph[currentVertex].array[adjVertex].vertex)
				continue;
			checked = (marker->array[graph[currentVertex].array[adjVertex].vertex].vertex == CHECKED);
			vertexWeight = &marker->array[graph[currentVertex].array[adjVertex].vertex].weight;
			if (currentVertex == F) {
				if (((graph[currentVertex].array[adjVertex].weight + marker->array[currentVertex].weight) > INT_MAX)
					|| (graph[currentVertex].array[adjVertex].weight > INT_MAX)
					|| (marker->array[currentVertex].weight > INT_MAX))
					overflowCounter++;
			}
			if ((!checked) && (graph[currentVertex].array[adjVertex].weight + marker->array[currentVertex].weight < *vertexWeight)) {
				*vertexWeight = graph[currentVertex].array[adjVertex].weight + marker->array[currentVertex].weight;
			}
		}
		if (marker->array[currentVertex].weight != UINT_MAX)
			marker->array[currentVertex].vertex = CHECKED;
	}
}

void Way(vector *graph, vector marker, int S, int currentVertex) {
	for (int i = 0; marker.array[currentVertex].weight != 0; i++) {
		if ((marker.array[currentVertex].weight - graph[currentVertex].array[i].weight)
			== marker.array[graph[currentVertex].array[i].vertex].weight) {
			printf("%d ", currentVertex + 1);
			Way(graph, marker, S, graph[currentVertex].array[i].vertex);
			return;
		}
	}
	printf("%d", S + 1);
}

int main() {
	int N = 0;
	scanf("%d", &N);
	if ((N < 0) || (N > 5000)) {
		printf("bad number of vertices");
		exit(0);
	}

	int S = -1;
	int F = -1;
	scanf("%d %d", &S, &F);
	if ((S == -1) || (F == -1)) {
		printf("bad number of lines");
		exit(0);
	}
	if ((S < 1) || (S > N) || (F < 1) || (F > N)) {
		printf("bad vertex");
		exit(0);
	}

	int M = -1;
	scanf("%d", &M);
	if (M == -1) {
		printf("bad number of lines");
		exit(0);
	}

	int validNumOfEdges = N * (N - 1) / 2;
	if ((M < 0) || (M > validNumOfEdges)) {
		printf("bad number of edges");
		exit(0);
	}

	vector *graph;
	graph = malloc(sizeof(vector) * N);
	for (int i = 0; i < N; ++i)
		graph[i] = NewVector();

	int edgeStart = 0;
	int edgeEnd = 0;
	long long edgeWeight = 0;
	for (int i = 0; i < M; i++) {
		edgeStart = edgeEnd = 0;
		edgeWeight = 0;
		scanf("%d %d %lld", &edgeStart, &edgeEnd, &edgeWeight);
		if ((edgeEnd == 0) || (edgeStart == 0) || (edgeWeight == 0)) {
			printf("bad number of lines");
			FreeGraph(graph, N);
			exit(0);
		}
		if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > N)) {
			printf("bad vertex");
			FreeGraph(graph, N);
			exit(0);
		}
		if ((edgeWeight > INT_MAX) || (edgeWeight < 0)) {
			printf("bad length");
			FreeGraph(graph, N);
			exit(0);
		}
		graph[edgeStart - 1].pushBack(&graph[edgeStart - 1], edgeEnd - 1, edgeWeight);
		graph[edgeEnd - 1].pushBack(&graph[edgeEnd - 1], edgeStart - 1, edgeWeight);
	}

	vector marker;
	marker = NewVector();
	for (int i = 0; i < N; i++) {
		marker.pushBack(&marker, 0, UINT_MAX);
	}
	marker.array[S - 1].weight = 0;

	Dijkstra(graph, &marker, N, S - 1, F - 1);

	for (int i = 0; i < N; i++)
		if (marker.array[i].weight == UINT_MAX)
			printf("oo ");
		else if (marker.array[i].weight > INT_MAX)
			printf("INT_MAX+ ");
		else
			printf("%lld ", marker.array[i].weight);

	printf("\n");

	if (marker.array[F - 1].weight == UINT_MAX)
		printf("no path");
	else if ((marker.array[F - 1].weight > INT_MAX) && (overflowCounter >= 2))
		printf("overflow");
	else
		Way(graph, marker, S - 1, F - 1);

	FreeGraph(graph, N);
	free(marker.array);
	return 0;
}
