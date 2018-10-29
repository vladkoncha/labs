#include <stdio.h>
#include <stdlib.h>

void swap (int *a, int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void heap (int *a, int N, int border)
{
    _Bool found = 0;
    for (int i = N/2 - 1; i>=0; i--)
    {
        found = 0;
        if ((a[i] > a[i * 2 + 1]) && (i * 2 + 1 < border))
        {
            swap(a, i, i * 2 + 1);
            found = 1;
            i++;
        }
        if ((a[i] > a[i * 2 + 2]) && (found != 1) && (i * 2 + 2 < border))
        {
            swap(a, i, i * 2 + 2);
            i++;
        }
    }
}

void sort (int *a, int N)
{
    for (int i = N - 1; i >= 1; i--)
    {
            swap(a, 0, i);
            heap(a, i , i);
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
    heap(a, N, N);
    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);
    printf("\n");
    sort(a, N);
    for (int i = N-1; i >= 0; i--)
        printf("%d ", a[i]);
    free(a);
    return 0;
}
