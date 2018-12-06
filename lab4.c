#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void swap(char *P, int i, int j)
{
	char temp = P[i];
	P[i] = P[j];
	P[j] = temp;
}

void sort(char *P, int i)
{
	int k = 0;
	int j = (int)strlen(P) - 1;
	while (i < j)
	{
		swap(P, i, j - k);
		k++;
		i++;
	}
}


void permutations(char *P)
{
	int st = (int)(strlen(P) - 1);
	int min = 0;
	for (int i = st; i >= 1; i--)
	{
		if (P[i]>P[i - 1])
		{
			min = i;
			for (int j = i; j <= st; j++)
			{
				if ((P[j] < P[min]) && (P[j]>P[i - 1]))
					min = j;
			}
			swap(P, i - 1, min);
			sort(P, i);

			int k = 0;
			while (P[k] != '\0')
			{
				printf("%c", P[k]);
				k++;
			}
			printf("\n");
			return;
		}

	}
}


int main()
{
	char P[11] = { '\0' };
	int Check[10] = { '\0' };
	int N;
	gets(P);
	scanf("%d", &N);
	for (int j = 0; j < (int)strlen(P); j++)
	{
		if ((P[j] < '0') || (P[j] > '9') || (Check[(int)(P[j]-'0')] != '\0'))
		{
			printf("bad input");
			exit(0);
		}
		else Check[(int)(P[j] - '0')] = 1;
	}


	for (int i = 0; i < N; i++)
	{
		permutations(P);
	}

	return 0;
}
