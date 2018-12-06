﻿#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>


void sort(int a[200000], int l, int r)
{
	int i = l, j = r, w;
	int x = (l + r) / 2;
	do
	{
		while (a[i]<a[x]) i++;
		while (a[x]<a[j]) j--;
		if (i <= j)
		{
			w = a[i];
			a[i] = a[j];
			a[j] = w;
			i++;
			j--;
		}
	} while (i<j);

	if (l<j) sort(a, l, j);
	if (i<r) sort(a, i, r);

	
}

int main()
{
	int N = 0;
	int l = 0;
	scanf("%d", &N);
	int r = N;
	int a[200000];
	for (int i = 0; i<N; i++)
		scanf("%d", &a[i]);

	sort(a, 0, N-1);

	for (int i = 0; i<N; i++)
		printf("%d ", a[i]);

	return 0;
}