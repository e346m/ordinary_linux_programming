#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "wrong arguments");
    exit(1);
  }
  FILE *f = fopen(argv[1], "r");
  if(!f) {
    perror(argv[1]);
    exit(1);
  }
  if(rename(argv[1], argv[2]) < 0) {
    perror(argv[1]);
    exit(1);
  }
  fclose(f);
  exit(0);
}
