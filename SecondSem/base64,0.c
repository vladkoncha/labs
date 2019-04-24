#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *in = fopen("in.txt", "r");
  FILE *out = fopen("out.txt", "w");
  char alphabet[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  unsigned char a[3] = {0};
  unsigned char x[4] = {0};
  int c = 0;
  int counter = 0;
  int lastChar = 0;

  while ((c = fgetc(in)) != EOF) { // add odd number
    counter = 1;
    a[0] = c;
    x[0] = a[0] & 252u;
    x[0] >>= 2u;

    if ((c = fgetc(in)) == EOF) {
      a[1] = 0;
      lastChar = 1;
    } else
      a[1] = c;
    counter++;
    x[1] = ((a[0] & 3u) << 4u) | (a[1] >> 4u);

    if (lastChar != 1) {
      if ((c = fgetc(in)) == EOF) {
        a[2] = 0;
        lastChar = 2;
      } else
        a[2] = c;
      counter += 2;
      x[2] = ((a[1] & 15u) << 2u) | (a[2] >> 6u);
      x[3] = a[2] & 63u;
    }

    if (lastChar == 2)
      counter--;
    for (int i = 0; i < counter; i++) {
      fprintf(out, "%c", alphabet[x[i]]);
      x[i] = 0;
    }
  }

  fclose(in);
  fclose(out);
  return 0;
}
