#include <stdio.h>

long findSize(char file[])
{
    // opening the file in read mode
    FILE* fp = fopen(file, "r");

    // checking if the file exist or not
    if (fp == NULL) {
        printf("File Not Found!\n");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);

    // calculating the size of the file
    long res = ftell(fp);
    // closing the file
    fclose(fp);

    return res;
}

// Driver code
int main()
{
    char ch, str[1000];
    int k=0;
    char file[] = { "/Users/admin/CLionProjects/workwithfiles/a.html" };
    long res = findSize(file);
    FILE* fp = fopen(file, "r");
    while (getc(fp) != EOF) k++;
    //fgets(str, (k/2), fp);
    //for (int i=0; i<(k/2); i++)
        printf ("%d", k);


    if (res != -1)
        printf("Size of the file is %ld bytes \n", res);
    return 0;
}
