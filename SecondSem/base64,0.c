#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *in = fopen("in.txt", "r");
  FILE *out = fopen("out.txt", "w");
  char alphabet[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  unsigned char a[] = "123456";
  unsigned char x[4] = { 0 };

  for (unsigned int j = 0; j < 6; j += 3) { //add odd number

    x[0] = a[j + 0] & 252u;
    x[0] >>= 2u;

    x[1] = ((a[j + 0] & 3u) << 4u) | (a[j + 1] >> 4u);

    x[2] = ((a[j + 1] & 15u) << 2u) | (a[j + 2] >> 6u);

    x[3] = a[j + 2] & 63u;

    for (int i = 0; i < 4; i++) {
      fprintf(out, "%c", alphabet[x[i]]);
      x[i] = 0;
    }
  }


  fclose(in);
  fclose(out);
  return 0;
}
