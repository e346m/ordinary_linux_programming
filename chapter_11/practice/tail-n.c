#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
  {"number", required_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

static void do_tail(FILE* stream, int nlines);

int main(int argc, char* argv[]) {
  int opt;
  int nlines = DEFAULT_N_LINES;
  while ((opt = getopt_long(argc, argv, "n:h", longopts, NULL)) != -1) {
    switch (opt) {
      case 'n':
        nlines = atol(optarg);
        break;
      case 'h':
        fprintf(stdout, "Usage: %s [-n Number][FILE ...]\n", argv[0]);
        exit(0);
      case '?':
        fprintf(stderr, "Usage: %s [-n Number][FILE ...]\n", argv[0]);
        exit(1);
    }
  }

  if(optind == argc) {
    do_tail(stdin, nlines);
  } else {
    int i;
    for( i = optind; i < argc; i ++) {
      FILE *f = fopen(argv[i], "r");
      if(!f) {
        perror(argv[i]);
        exit(1);
      }
      printf("%s\n", argv[i]);
      do_tail(f, nlines);
      printf("------------------------\n");
      fclose(f);
    }
  }
}

static void do_tail(FILE* stream, int nlines) {
  int c;
  int count = 0;
  while((c = fgetc(stream)) != EOF) {
    if (c == '\n') {
      count++;
    }
  }
  rewind(stream);
  while((c = fgetc(stream)) != EOF) {
    if (c == '\n') {
      count--;
      if (count == nlines) continue;
    }
    if (count <= nlines) {
      if(putchar(c) < 0) exit(1);
    }
  }
}

