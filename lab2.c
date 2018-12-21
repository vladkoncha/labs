#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define maxline 1000

int asc[256]; //ascii

void table(unsigned char find[20])
{
	int leng = strlen(find);
	for (int i = 0; i <= 255; i++)
		asc[i] = leng;

	for (int i = 0; i < leng - 1; i++)
	{
		asc[find[i]] = leng - i - 1;
	}
}
void search(unsigned char str[maxline], unsigned  char find[20])
{
	int lengstr = strlen(str);
	int lengfind = strlen(find);

	int i = lengfind - 1;
	int j = i;
	int k = i;
	while (i <= lengstr - 1)
	{
		j = lengfind - 1;
		k = i;
		printf("%d ", k + 1);
		while ((j > 0) && (str[k]) == (find[j]))
		{
			k--;
			j--;
			printf("%d ", k + 1);
		}
		i += asc[str[i]];
	}
}

int main()
{
	unsigned char str[maxline] = { 0 };
	unsigned char find[20];
	char input[128];
	gets(find);

	while (fgets(input, sizeof(input), stdin)) {
		if ((strlen(str) + strlen(input)) > 999)
			break;
		strcat(str, input);
		if (input[0] == '\n') 
			break;
	}

	if (str[0] && str[strlen(str) - 1] == '\n') // if string is not empty and final char is \n
		str[strlen(str) - 1] = 0; // erase final \n
	table(find);
	search(str, find);
	return 0;

}
