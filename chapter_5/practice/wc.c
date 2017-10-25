#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int read_line(const char *path);
static void die(const char *s);

int main(int argc, char *argv[]) {
  int i;
  int total = 0;
  if(argc < 2) {
    fprintf(stderr, "%s: filename not given\n", argv[0]);
    exit(1);
  }
  for (i = 1; i < argc; i++) {
    total += read_line(argv[i]);
  }
  printf("total lines: %d", total);
  exit(0);
}

#define BUFFER_SIZE 2048
// TODO sometimes extra \n is found in buffer...
static int read_line(const char *path) {
  int fd;
  unsigned char buf[BUFFER_SIZE];
  int count = 0;
  int n;

  fd = open(path, O_RDONLY);
  if (fd < 0) die(path);
  for(;;) {
    n = read(fd, buf, sizeof buf);
    if(n < 0) die(path);
    if (n == 0) break;
    for (int i = 0; i < BUFFER_SIZE; i++) {
      if (buf[i] == '\n') {
        count++;
      }
    }
  }

  if(close(fd) < 0) die(path);
  return count;
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
