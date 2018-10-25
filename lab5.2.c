#include <stdio.h>
#include <stdlib.h>

void sift(int *a, int l, int r)
{
    int max;
    _Bool done=0;
    while ((l * 2 <= r) && (!done))
    {
        if (l * 2 == r)
            max = l * 2;
        else if (a[l * 2] < a[l * 2 + 1])
            max = l * 2;
        else
            max = l * 2 + 1;
        if (a[l] > a[max])
        {
            int temp = a[l];
            a[l] = a[max];
            a[max] = temp;
            l = max;
        }
        else
            done = 1;
    }
}

void heap(int *a, int N)
{
    // Формируем нижний ряд пирамиды
    for (int i = (N / 2) - 1; i >= 0; i--)
        sift(a, i, N - 1);
    for (int i = N - 1; i >= 1; i--)
    {
        int temp = a[0]; // убираем первый элемент (который является наибольшим) в конец
        a[0] = a[i];    // и просеиваем массив уже без него
        a[i] = temp;
        sift(a, 0, i - 1);
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
    heap(a, N);
    for (int i = N-1; i >= 0; i--)
        printf("%d ", a[i]);
    free(a);
    return 0;
}
