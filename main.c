#include <stdio.h>
void quicksort(int a[200000],int first,int last){
    int i, j, mid, temp;
    
    if(first<last)
    {
        mid=(first+last)/2; // опорный элемент
        i=first;
        j=last;
        
        while(i<j)
        {
            while((a[i]<=a[mid]) && (i<last))
                i++;
            while(a[j]>a[mid])
                j--;
            if(i<j)
            {
                temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
        
        temp=a[mid];
        a[mid]=a[j];
        a[j]=temp;
        quicksort(a,first,j-1);
        quicksort(a,j+1,last);
        
    }
}

int main(){
    int i, count, a[200000];
    
    scanf("%d",&count); // ввод количества элементов
    
    for(i=0;i<count;i++)
        scanf("%d",&a[i]); // ввод элементов
    
    quicksort(a,0,count-1);
    
    for(i=0;i<count;i++)
        printf("%d ",a[i]); // вывод элементов
    
    return 0;
}