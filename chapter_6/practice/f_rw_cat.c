#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define BUFFER_SIZE 2048 * 5

int main(int argc, char *argv[]) {
  int i;
  for(i = 1; i < argc; i++) {
    FILE *f;
    f = fopen(argv[i], "r");
    if(!f) {
      perror(argv[i]);
      exit(1);
    }

    unsigned char buf[BUFFER_SIZE];
    size_t n;
    size_t size = 1;
    size_t nmemb = sizeof buf;
    for(;;) {
      n = fread(buf, size, nmemb, f);
      if(ferror(f)) exit(1);
      if(fwrite(buf, size, n, stdout) < n) exit(1);
      if(!ferror(f) && n < nmemb) break;
    }
    if(fclose(f) != 0) exit(1);
  }
}
