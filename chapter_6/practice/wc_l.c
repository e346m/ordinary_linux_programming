#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
  int total = 0;
  for (int i = 1; i < argc; i++) {
    FILE *f;
    int c;
    int count = 0;

    f = fopen(argv[i], "r");
    if(!f) {
      perror(argv[i]);
      exit(1);
    }
    while((c = fgetc(f)) != EOF) {
      if (c == '\n') {
        count++;
      }
    }
  printf("file: %s, count: %d\n", argv[i], count);
  total += count;
  }
  printf("total: %d\n", total);
  exit(0);
}
