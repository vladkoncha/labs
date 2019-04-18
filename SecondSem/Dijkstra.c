#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef short bool;

void Dijkstra(int **graph, long long *marker, bool *check, int N) {
  long long minWeight = 0;
  long long minVertex = 0;
  do {
    minVertex = LLONG_MAX;
    minWeight = LLONG_MAX;
    for (int i = 0; i < N; i++) {
      if (!check[i] && (marker[i] < minWeight)) {
        minWeight = marker[i];
        minVertex = i;
      }
    }

    if (minVertex != LLONG_MAX) {
      for (int i = 0; i < N; i++) {
        if (graph[minVertex][i] > 0) {
          if ((minWeight + graph[minVertex][i]) < marker[i]) {
            marker[i] = minWeight + graph[minVertex][i];
          }
        }
      }
      check[minVertex] = 1;
    }
  } while (minVertex < LLONG_MAX);
}

bool VertPrint(long long *marker, int N, int F) {
  int overflowCounter = 0;
  for (int i = 0; i < N; i++) {
    if (marker[i] != LLONG_MAX) {
      if (marker[i] >= INT_MAX) {
        overflowCounter++;
      }
      if (marker[i] > INT_MAX) {
        printf("INT_MAX+ ");
      } else printf("%lld ", marker[i]);
    } else printf("oo ");
  }
  printf("\n");
  long long weight = marker[F - 1];
  if (weight == LLONG_MAX) {
    printf("no path");
    return 0;
  } else if (weight > INT_MAX && overflowCounter > 2) {
    printf("overflow");
    return 0;
  }
  return 1;
}

void Way(int **graph, const long long *marker, int F, long long weight, int N) {
  printf("%d ", F + 1);
  while (weight > 0) {
    for (int i = 0; i < N; i++) {
      if (graph[F][i] != 0) {
        if (weight - graph[F][i] == marker[i]) {
          weight = weight - graph[F][i];
          F = i;
          printf("%d ", i + 1);
        }
      }
    }
  }
}

void FreeGraph(int **graph, int N) {
  for (int i = 0; i < N; i++) {
    free(graph[i]);
  }
  free(graph);
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

  int **graph = (int **) calloc(N, sizeof(int *));
  for (int i = 0; i < N; i++) {
    graph[i] = calloc(N, sizeof(int));
  }

  int edgeStart = 0;
  int edgeEnd = 0;
  int edgeWeight = 0;
  for (int i = 0; i < M; i++) {
    edgeStart = edgeEnd = 0;
    edgeWeight = 0;
    scanf("%d %d %d", &edgeStart, &edgeEnd, &edgeWeight);
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
    graph[edgeStart - 1][edgeEnd - 1] = edgeWeight;
    graph[edgeEnd - 1][edgeStart - 1] = edgeWeight;
  }

  long long *marker = malloc(N * (sizeof(long long)));
  bool *check = malloc(N * (sizeof(bool)));

  for (int i = 0; i < N; i++) {
    marker[i] = LLONG_MAX;
    check[i] = 0;
  }
  marker[S - 1] = 0;

  Dijkstra(graph, marker, check, N);

  if (VertPrint(marker, N, F))
    Way(graph, marker, F - 1, marker[F - 1], N);

  FreeGraph(graph, N);
  free(marker);
  free(check);
  return 0;
}
