#include <stdio.h>
#include <stdlib.h>




void swap(int *a, int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void heap(int *a, int N )
{
    for (int i = N / 2 - 1; i >= 0; i--)
    {
        if ((a[i] > a[i * 2 + 1]) && (i * 2 + 1 < N))
            if  ((a[i] > a[i * 2 + 2]) && (i * 2 + 2 < N))
                swap(a, i, i * 2 + 2);
            else
                swap(a, i, i * 2 + 1);
        else
            if ((a[i] > a[i * 2 + 2]) && (i * 2 + 2 < N))
            swap(a, i, i * 2 + 2);
    }
}

void sort(int *a, int N)
{
    heap(a, N);
    for (int i = N - 1; i >= 1; i--)
    {
        swap(a, 0, i);
        heap(a, i);
    }
}

int main()
{
    int *a;
    int N;
    scanf("%d", &N);
    a = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);
    sort(a, N);
    for (int i = N - 1; i >= 0; i--)
        printf("%d ", a[i]);
    free(a);
    return 0;
}
