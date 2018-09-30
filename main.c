#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define maxline 1000

int asc [255]; //ascii

void table (char find[20])
{
    int leng = strlen(find);
    for (int i=0; i<=255; i++)
    asc[i]=leng;
    
    for (int i=0; i<leng-1; i++)
    {
            asc[find[i]]=leng-i-1;
    }
}
void search (char str[maxline], char find[20])
{
    int lengstr = strlen(str);
    int lengfind = strlen(find);
    if (lengfind > lengstr)
        printf("Bad input");
    int i=lengfind-1;
    int j=i;
    int k=i;
    while (i <= lengstr-1)
    {
        j=lengfind-1;
        k=i;
        printf ("%d ", k+1);
        while ((j>0) && (str[k])==(find[j]))
        {
            k--;
            j--;
            printf ("%d ", k+1);
        }
        i+=asc[str[i]];
    }
}

int main()
{
    char str[maxline]={0};
    char find[20];
    char input[200];
    gets(find);
    while (fgets(input,sizeof(input),stdin))
    {
        strcat(str, input);
        if ((input[0] == '\n') || (input[0] == '\r' && input[1]=='\n'))
            break;
    }
    if (str[0])
        str[strlen(str)-1]=0;
    
    table(find);
    search(str, find);
    return 0;
    
}
