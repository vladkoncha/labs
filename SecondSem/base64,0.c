#include <stdio.h>
#include <stdlib.h>

int main() {
  FILE *in = fopen("in.txt", "r");
  FILE *out = fopen("out.txt", "w");
  char alphabet[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  unsigned char a[3] = { 0 };
  unsigned char x[4] = { 0 };
  int counter = 0;

  while (!feof(in)){ //add odd number
    counter = 1;
    a[0] = fgetc(in);
    x[0] = a[0] & 252u;
    x[0] >>= 2u;

    if (!feof(in)) {
      counter++;
      a[1] = fgetc(in);
      x[1] = ((a[0] & 3u) << 4u) | (a[1] >> 4u);

      if (!feof(in)) {
        counter += 2;
        a[2] = fgetc(in);
        x[2] = ((a[1] & 15u) << 2u) | (a[2] >> 6u);
        x[3] = a[2] & 63u;
      }
    }

    for (int i = 0; i < counter; i++) {
      fprintf(out, "%c", alphabet[x[i]]);
      x[i] = 0;
    }
  }


  fclose(in);
  fclose(out);
  return 0;
}
