#include <stdio.h>
#include <stdlib.h>


void swap(int *a, int i, int j)
{
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}


void heap(int *a, int i, int N)
{
    while (i < N)
    {
        int big_index = i;
        int childl = 2 * i + 1;
        int childr = childl + 1;

        if ((childl < N) && (a[childl] > a[big_index]))
            big_index = childl;

        if ((childr < N) && (a[childr] > a[big_index]))
            big_index = childr;

        if (big_index == i) return;

        swap (a, i, big_index);
        i = big_index;
    }
}

void build_heap (int *a, int N)
{
    int index = N/2 - 1;
    while (index >= 0)
    {
        heap(a, index, N);
        index-- ;
    }
}


void sort(int *a, int N)
{
    build_heap(a, N);
    int end = N - 1;

    while(end >= 0)
    {
        swap(a, 0, end);
        heap(a, 0, end);
        end -= 1;
    }
}


int main() {
    int *a;
    int N;
    scanf("%d", &N);
    a = (int*)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++)
        scanf("%d", &a[i]);

    sort(a, N);

    for (int i = 0; i < N; i++)
        printf("%d ", a[i]);

    free(a);
    return 0;
}