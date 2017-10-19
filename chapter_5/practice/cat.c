#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int do_cat(int fd);
static void die(const char *s);

int main(int argc, char *argv[]) {
  int i;
  if(argc < 2) {
    if (do_cat(STDIN_FILENO) < 0) {
      exit(1);
    }
  } else {
    for (i = 1; i < argc; i++) {
      int fd;
      fd = open(argv[1], O_RDONLY);
      if (do_cat(fd) < 0) {
        die(argv[1]);
      }
    }
  }
  exit(0);
}

#define BUFFER_SIZE 2048

static int do_cat(int fd) {
  unsigned char buf[BUFFER_SIZE];
  int n;

  if (fd < 0) return fd;
  do {
    n = read(fd, buf, sizeof buf);
    if (n < 0) return -1;
    if (write(STDOUT_FILENO, buf, n) < 0) return -1;
  } while(0 == n);

  if (close(fd) < 0) return -1;
  return 1;
}

static void die(const char *s) {
  perror(s);
  exit(1);
}
