#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s [FILE ...]\n", argv[0]);
    exit(1);
  }
  FILE *f;
  f = fopen(argv[1], "r");


  int c;
  int count = 0;
  while((c = fgetc(f)) != EOF) {
    if(c == '\n') {
      count++;
    }
  }
  rewind(f);
  while((c = fgetc(f)) != EOF) {
    if(c == '\n') {
      count--;
      if (count == 5) continue;
    }
    if (count == 6) {

    }
    if (count <= 5) {
      if (putchar(c) < 0) exit(1);
    }
  }
  fclose(f);
  exit(0);
}
