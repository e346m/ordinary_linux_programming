#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

static void traverse(const char* path);

int main(int argc, char *argv[]) {
  if (argc < 2) {
    fprintf(stderr, "%s: no arguments\n", argv[0]);
    exit(1);
  }

  int i;
  for(i = 1; i < argc; i++) {
    traverse(argv[i]);
  }
  exit(0);
}

static void traverse(const char* path) {
  DIR *d;
  d = opendir(path);
  if(!d) {
    perror(path);
    exit(1);
  }

  struct dirent* ent;
  while (ent = readdir(d)) {
    if ('.' == ent->d_name[0]) continue;
    if (ent->d_type == DT_DIR) {
      traverse(ent->d_name);
    } else {
      printf("%s\n", ent->d_name);
    }
  }
}
