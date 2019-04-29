#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define EQUALS -2

//add getopt, -f, -i and help

void BaseSymbolCheck(int c, const unsigned char *alphadec) {
  if (alphadec[c] == 66) {
    printf("Not base64 symbol\n");
    exit(0);
  }
}

char SpacesSkip(FILE *in, const unsigned char *alphadec) {
  int c = 0;
  while ((c = fgetc(in)) != EOF) {
    if (alphadec[c] != 64) {
      BaseSymbolCheck(c, alphadec);
      return c;
    }
  }
  return EOF;
}

int GetC(FILE *in, const unsigned char *alphadec) {
  int c = 0;
  if ((c = fgetc(in)) == '=')
    return -2;
  else {
    BaseSymbolCheck(c, alphadec);
    if (alphadec[c] == 64)
      if ((c = SpacesSkip(in, alphadec)) == EOF)
        return EOF;
  }
  return c;
}

void decode(FILE *in, FILE *out) {
  const unsigned char alphadec[] = {
      // WHITESPACE - 64, EQUALS - 65, INVALID - 66;
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 64, 66, 66, 64, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 64, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 62, 66, 66, 66, 63, 52, 53, 54, 55, 56, 57,
      58, 59, 60, 61, 66, 66, 66, 65, 66, 66, 66, 0,  1,  2,  3,  4,  5,  6,
      7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24,
      25, 66, 66, 66, 66, 66, 66, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36,
      37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66, 66,
      66, 66, 66, 66};

  unsigned char input[4] = {0};
  unsigned char output[3] = {0};
  int c = 0;
  int counter = 0;

  while ((c = GetC(in, alphadec)) != EOF) {
    counter = 0;
    input[0] = alphadec[c];

    if ((c = GetC(in, alphadec)) != EQUALS) {
      if (c == EOF)
        break;
      counter++;
      input[1] = alphadec[c];
      output[0] = (input[0] << 2u) | (input[1] >> 4u);
    }

    if ((c = GetC(in, alphadec)) != EQUALS) {
      if (c == EOF)
        break;
      counter++;
      input[2] = alphadec[c];
      output[1] = (input[1] << 4u) | (input[2] >> 2u);
    }

    if ((c = GetC(in, alphadec)) != EQUALS) {
      if (c == EOF)
        break;
      counter++;
      input[3] = alphadec[c];
      output[2] = (input[2] << 6u) | input[3];
    }

    for (int i = 0; i < counter; i++) {
      fprintf(out, "%c", output[i]);
      output[i] = 0;
    }
  }
}

void encode(FILE *in, FILE *out, const char *alphabet) {
  unsigned char input[3] = {0};
  unsigned char output[4] = {0};
  int c = 0;
  int counter = 0;
  int lastChar = 0;

  while ((c = fgetc(in)) != EOF) { // add odd number
    counter = 1;
    input[0] = c;
    output[0] = input[0] & 252u;
    output[0] >>= 2u;

    if ((c = fgetc(in)) == EOF) {
      input[1] = 0;
      lastChar = 1;
    } else
      input[1] = c;
    counter++;
    output[1] = ((input[0] & 3u) << 4u) | (input[1] >> 4u);

    if (lastChar != 1) {
      if ((c = fgetc(in)) == EOF) {
        input[2] = 0;
        lastChar = 2;
      } else
        input[2] = c;
      counter += 2;
      output[2] = ((input[1] & 15u) << 2u) | (input[2] >> 6u);
      output[3] = input[2] & 63u;
    }

    if (lastChar == 2)
      counter--;
    for (int i = 0; i < counter; i++) {
      fprintf(out, "%c", alphabet[output[i]]);
      output[i] = 0;
    }
  }
  if (lastChar != 0)
    for (int i = 0; i < (3 - lastChar); i++)
      fprintf(out, "=");
}

int main(int argc, char *argv[]) {
  FILE *in = fopen(argv[2], "rb");
  if (in == NULL) {
    printf("File doesn't exist\n");
    exit(0);
  }
  FILE *out = fopen(argv[3], "wb");
  char alphabet[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  if (!strcmp(argv[1], "-e"))
    encode(in, out, alphabet);
  else if (!strcmp(argv[1], "-d"))
    decode(in, out);
  else
    printf("wtf you want?\n");

  fclose(in);
  fclose(out);
  return 0;
}
