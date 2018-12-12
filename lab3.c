#include <stdio.h>
#include <string.h>

int count_hash(char *pat, int begin, int end)
{
    int hash = 0;
    int k = 1;
    for (int i = begin; i < end; i++)
    {
        hash += (pat[i]%3) * k;
        k *= 3;
    }
    return hash;
}

int next_hash(char *str, int last, int hash, int step)
{
    int k = 1;
    for (int j = 0; j < step; j++)
    {
       k *= 3;
    }
    int hash_str = (hash - (str[last - step - 1]%3))/3 + str[last]%3 * k;
    return hash_str;
}

int main()
{
    char pattern[17] = {0};
    char str[100] = {0};
    gets(pattern);
    gets(str);
    int patlen = (int) strlen(pattern);

    int hash_pat = count_hash(pattern, 0, patlen);
    printf("%d\n", hash_pat);

    int hash_str = 0;
    for (int i = 0; i < (int) strlen(str) - patlen + 1; i++)
    {
        if (hash_str == 0)
            hash_str = count_hash(str, i, i + patlen);
        else
            hash_str = next_hash(str, i + patlen - 1, hash_str, patlen - 1);
        if (hash_str == hash_pat)
        {
            int k = 0;
            int j = i;
            while ((pattern[k] == str[j]) && (k < strlen(pattern)))
            {
                printf("%d ", j + 1);
                k++;
                j++;
            }
        }
    }




    return 0;
}
