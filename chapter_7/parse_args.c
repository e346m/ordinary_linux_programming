#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  int opt;
  while((opt = getopt(argc, argv, "af:tx")) != -1) {
    switch(opt) {
      case 'a' :
        printf("a\n");
        break;
      case 'f' :
        printf("f: %s\n", optarg);
        break;
      case 't' :
        printf("t\n");
        break;
      case 'x' :
        printf("x\n");
        break;
      case '?' :
        printf("?\n");
        break;
    }
  }
}
