#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "no arguments");
    exit(1);
  }

  FILE *f = fopen(argv[1], "r");
  if(!f) {
    perror(argv[1]);
    exit(1);
  }

  if(unlink(argv[1]) < 0) {
    perror(argv[1]);
    exit(0);
  }
  fclose(f);
  exit(0);
}
