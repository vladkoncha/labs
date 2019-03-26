#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
typedef short bool;

struct graph {
	int start;
	int end;
	unsigned int weight;
};

int cmp(const void *a, const void *b) {
	struct graph *graphA = (struct graph*) a;
	struct graph *graphB = (struct graph*) b;
	return (int)(graphA->weight - graphB->weight);
}

struct graph *FindMin(struct graph *closestVertex, struct graph *graph, const int *check, int M) {
	unsigned int minWeight = INT_MAX;
	closestVertex = NULL;
	bool endChecked = 0;
	bool startChecked = 0;
	for (int i = 0; i < M; i++) {
		endChecked = (check[graph[i].end] == 1);
		startChecked = (check[graph[i].start] == 1);
		if (((startChecked && !endChecked) || (endChecked && !startChecked)) && (graph[i].weight <= minWeight) && (graph[i].weight != 0)) {
			closestVertex = &graph[i];
			break;
		}
	}
	return closestVertex;
}

int Prim(struct graph *graph, int N, int M, FILE *out) {
	int numOfVertices = 1;
	struct graph *closestVertex = NULL;
	struct graph *ptr;
	int *check = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i < N + 1; i++)
		check[i] = 0;
	check[graph[0].start] = 1;
	while ((ptr = FindMin(closestVertex, graph, check, M))) {
		fprintf(out, "%d %d\n", ptr->start, ptr->end);
		ptr->weight = 0;
		check[ptr->start] = 1;
		check[ptr->end] = 1;
		numOfVertices++;
	}
	free(check);
	return numOfVertices;
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

	struct graph *graph = NULL;
	graph = (struct graph*)malloc(M * sizeof(struct graph));

	for (int i = 0; i < M; i++) {
		if (fscanf(in, "%d %d %u", &graph[i].start, &graph[i].end, &graph[i].weight) != EOF) {}
		else {
			fprintf(out, "bad number of lines");
			fclose(in);
			fclose(out);
			free(graph);
			exit(0);
		}
		if ((graph[i].start < 1) || (graph[i].start > N) || (graph[i].end < 1) || (graph[i].end > N)) {
			fprintf(out, "bad vertex");
			fclose(in);
			fclose(out);
			free(graph);
			exit(0);
		}
		if ((graph[i].weight > INT_MAX) || (graph[i].weight < 0)) {
			fprintf(out, "bad length");
			fclose(in);
			fclose(out);
			free(graph);
			exit(0);
		}
	}

	qsort(graph, (size_t)M, sizeof(struct graph), cmp);

	if (M != 0)
		if (Prim(graph, N, M, out) != N) {
			fclose(out);
			out = fopen("out.txt", "w");
			fprintf(out, "no spanning tree");
		}

	fclose(in);
	fclose(out);
	if (graph)
		free(graph);
	return 0;
}
