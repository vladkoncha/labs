#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int count_hash(unsigned char *pat, int end)
{
    int hash = 0;
    int k = 1;
    for (int i = 0; i < end; i++)
    {
        hash += (pat[i] % 3) * k;
        k *= 3;
    }
    return hash;
}

int step(int i)
{
    int st = 1;
    while (i != 0){
        st *= 3;
        i--;
    }
    return st;
}

int main()
{
    unsigned char pattern[18] = { 0 };
    unsigned char str[18] = { 0 };
    unsigned char letter;
    fgets(pattern, 18, stdin);

    int patlen = (int)strlen(pattern) - 1;
    fgets (str, patlen + 1, stdin);

    int maxstep = step(patlen - 1);

    int hash_pat = count_hash(pattern, patlen);
    printf("%d ", hash_pat);
    int hash_str = count_hash(str, patlen);

    for (int i = 0; feof(stdin) == 0; ++    i)
    {
        if (hash_str == hash_pat)
        {
            for (int j = 0; j < patlen; j++)
            {
                printf("%d ", j + i + 1);
                if (pattern[j] != str[(i + j) % patlen])
                    break;
            }
        }
        letter = fgetc(stdin);
        hash_str = (hash_str - (str[i % patlen] % 3))/3 + ((letter % 3) * maxstep);
        str[i % patlen] = letter;
    }

    return 0;
}
