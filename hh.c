#include <stdio.h>

int main() {
  FILE *in = fopen("in.txt", "rb");
  int k = 0;
  int c = 0;
  while ((k = fgetc(in)) != EOF) {
    c++;
  }
  printf("%d", c);

  fclose(in);
  return 0;
}