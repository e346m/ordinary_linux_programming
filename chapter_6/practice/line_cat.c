#include <stdio.h>
#include <stdlib.h>

static void put(const char c);

int main(int argc, char *argv[]) {
  int i;
  for(i = 1; i < argc; i++) {
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
          put('\\');
          put('t');
          break;
        case '\n' :
          put('$');
          put('\\');
          put('n');
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
