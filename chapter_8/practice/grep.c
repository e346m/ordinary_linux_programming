#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <regex.h>
#define _GNU_SOURCE
#include <getopt.h>

int icase = 0;
int invert = 0;
static void do_grep(regex_t *pat, FILE *src);
static void printe(int e, regex_t *pat);
static struct option longopts[] = {
  {"ignore-case", no_argument, NULL, 'i'},
  {"invert-match", no_argument, NULL, 'v'},
  {"help", no_argument, NULL, 'h'},
  {0, 0, 0, 0}
};

int main(int argc, char *argv[]) {
  int opt;
  while((opt = getopt_long(argc, argv, "ivh", longopts, NULL)) != -1) {
    switch (opt) {
      case 'i' :
        icase = 1;
        break;
      case 'v' :
        invert = 1;
        break;
      case 'h' :
        fprintf(stdout, "Usage %s [-i|-v pattern][FILE ...]\n", argv[0]);
        exit(0);
      case '?' :
        fprintf(stderr, "Usage %s [-i|-v pattern][FILE ...]\n", argv[0]);
        exit(1);
    }
  }

  int err;
  regex_t pat;
  int re_mode = REG_EXTENDED | REG_NOSUB | REG_NEWLINE;
  if(icase) re_mode |= REG_ICASE;
  err = regcomp(&pat, argv[optind], re_mode);
  printe(err, &pat);

  int i;
  if(argc == optind + 1) {
    do_grep(&pat, stdin);
  } else {
    for (i = optind + 1; i < argc; i++) {
      FILE *f;
      f = fopen(argv[i], "r");
      if(!f) {
        perror(argv[i]);
        exit(1);
      }
      do_grep(&pat, f);
      fclose(f);
    }
  }
  regfree(&pat);
  exit(0);
}

static void do_grep(regex_t *pat, FILE *src) {
  char buf[4096];
  int matched;
  while(fgets(buf, sizeof buf, src)) {
    matched = (regexec(pat, buf, 0, NULL, 0) == 0);
    if(invert) {
      matched = !matched;
    }
    if(matched) {
      fputs(buf, stdout);
    }
  }
}

static void printe(int err, regex_t *pat) {
  if(err != 0) {
    char buf[1024];
    regerror(err, pat, buf, sizeof buf);
    puts(buf);
    exit(1);
  }
}
