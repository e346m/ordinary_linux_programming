#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <getopt.h>

static void put(const char c);
static struct option longopts[] = {
  {"visible-tab", no_argument, NULL, 't'},
  {"visible-lf", no_argument, NULL, 'n'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
  int t = 0;
  int n = 0;
  int opt;
  while((opt = getopt_long(argc, argv, "tn", longopts, NULL)) != -1) {
    switch(opt) {
      case 't' :
        t = 1;
        break;
      case 'n' :
        n = 1;
        break;
      case 'h' :
        fprintf(stdout, "Usage: %s [-v|-n][FILE ...]\n", argv[0]);
        exit(0);
      case '?' :
        fprintf(stderr, "Usage: %s [-v|-n][FILE ...]\n", argv[0]);
        exit(1);
    }
  }

  int i;
  for(i = optind; i < argc; i++) {
    FILE *f;
    int c;


    f = fopen(argv[i], "r");
    if (!f) {
      perror(argv[i]);
      exit(1);
    }

    while((c = fgetc(f)) != EOF) {
      switch(c) {
        case '\t' :
          if (t == 1) {
            put('\\');
            put('t');
          } else {
            put(c);
          }
          break;
        case '\n' :
          if (n == 1) {
            put('\\');
            put('n');
          } else {
            put(c);
          }
          break;
        default :
          put(c);
      }
    }
  }
  exit(0);
}

static void put(const char c) {
  if(putchar(c) < 0) exit(1);
}
