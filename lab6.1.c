#include <stdio.h>


void sort(char a[], int N, int l, int r)
{
    int i=l, j=r, w;
    int x=(l+r)/2;
    do
    {
        while(a[i]<x) i++;
        while(x<a[j]) j--;
        if (i<=j)
        {
            w=a[i];
            a[i]=a[j];
            a[j]=w;
            i++;
            j--;
        }
    } while(i<j);
    
    if (l<j) sort(a, N, l, j);
    if (i<r) sort(a, N, i, r);
    
    for (i=0; i<=N; i++)
        printf("%d ",a[i]);
   
}

int main()
{
    int N=0;
    int l=0;
    scanf("%d",&N);
    int r=N;
    char a[N];
    scanf("%s",&a[N]);
    sort(a, N, l, r);
        
    return 0;
}
