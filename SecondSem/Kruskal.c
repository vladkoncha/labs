#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define NA_VIHOD 1

struct graph {
	int start;
	int end;
	unsigned int weight;
	int out;
};

int cmp(const void *a, const void *b) {
	struct graph *graphA = (struct graph*) a;
	struct graph *graphB = (struct graph*) b;
	return (int)(graphA->weight - graphB->weight);
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

	if ((N == 0) && (M == 0)) {
		printf("no spanning tree");
		return 0;
	}

	int validNumOfEdges = N * (N - 1) / 2;
	if ((M < 0) || (M > validNumOfEdges)) {
		printf("bad number of edges");
		exit(0);
	}

	struct graph *graph = NULL;
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
			free(graph);
			exit(0);
		}
		if ((edgeStart < 1) || (edgeStart > N) || (edgeEnd < 1) || (edgeEnd > N)) {
			printf("bad vertex");
			free(graph);
			exit(0);
		}
		if (edgeWeight > INT_MAX){
			printf("bad length");
			free(graph);
			exit(0);
		}
		graph[i].start = --edgeStart;
		graph[i].end = --edgeEnd;
		graph[i].weight = edgeWeight;
	}
	qsort(graph, (size_t)M, sizeof(struct graph), cmp);

	int *color = (int*)malloc(N * sizeof(int));
	for (int i = 0; i < N; i++)
		color[i] = i;

	int currentColor = 0;
	for (int currentEdge = 0; currentEdge < M; currentEdge++) {
		if (color[graph[currentEdge].start] != color[graph[currentEdge].end]) {
			currentColor = color[graph[currentEdge].end];
			for (int numOfVertex = 0; numOfVertex < N; numOfVertex++) {
				if (color[numOfVertex] == currentColor)
					color[numOfVertex] = color[graph[currentEdge].start];
			}
			graph[currentEdge].out = NA_VIHOD;
		}
	}

	for (int i = 1; i < N; i++)
		if (color[i - 1] != color[i]) {
			printf("no spanning tree");
			return 0;
		}

	for (int i = 0; i < M; i++)
		if (graph[i].out == NA_VIHOD)
			printf("%d %d\n", ((graph[i].start < graph[i].end) ? ++graph[i].start : ++graph[i].end), ((graph[i].start > graph[i].end) ? ++graph[i].start : ++graph[i].end));

	free(color);
	free(graph);
	return 0;
}
