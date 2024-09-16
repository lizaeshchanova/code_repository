#include "s21_cat.h"

bool parsing(Flags* flags, char* option) {
  int out = 1;

  if (strcmp(option, "-b") == 0 || strcmp(option, "--number-nonblank") == 0)
    flags->b = 1;
  else if (strcmp(option, "-s") == 0 || strcmp(option, "--squeeze-blank") == 0)
    flags->s = 1;
  else if (strcmp(option, "-n") == 0 || strcmp(option, "--number") == 0) {
    flags->n = flags->b ? 0 : 1;
  } else if (strcmp(option, "-e") == 0) {
    flags->e = 1;
    flags->v = 1;
  } else if (strcmp(option, "-E") == 0) {
    flags->e = 1;
  } else if (strcmp(option, "-t") == 0) {
    flags->t = 1;
    flags->v = 1;
  } else if (strcmp(option, "-T") == 0) {
    flags->t = 1;
  } else if (strcmp(option, "-v") == 0) {
    flags->v = 1;
  } else
    out = 0;

  return out;
}

void print_cat(FILE* file, Flags* flags) {
  int prevSym = '\n';
  bool empty_line = 0;
  int cnt = 0;

  int ch = file ? fgetc(file) : getchar();

  while (ch != EOF) {
    if (!(flags->s && prevSym == '\n' && ch == '\n' && empty_line)) {
      empty_line = (prevSym == '\n' && ch == '\n');

      if (((flags->n && !flags->b) || (flags->b && ch != '\n')) &&
          prevSym == '\n') {
        cnt++;
        printf("%6d\t", cnt);
      }
      if (flags->e && ch == '\n') printf("$");

      if (flags->t && ch == '\t') {
        printf("^");
        ch = '\t' + 64;
      }
      if (flags->v) {
        if (ch > 127 && ch < 160) printf("M-^");
        if ((ch < 32 && ch != '\n' && ch != '\t') || ch == 127) printf("^");
        if ((ch < 32 || (ch > 126 && ch < 160)) && ch != '\n' && ch != '\t')
          ch = ch > 126 ? ch - 128 + 64 : ch + 64;
      }
      fputc(ch, stdout);
    }
    prevSym = ch;
    ch = file ? fgetc(file) : getchar();
  }
}

int main(int argc, char* argv[]) {
  Flags flags = {false, false, false, false, false, false};
  bool not_ok = false;
  FILE* file = NULL;
  for (int i = 1; i < argc; i++) {
    char* argument = argv[i];
    if (argument[0] == '-') {
      if (!parsing(&flags, argument)) {
        fprintf(stderr, "s21_cat: invalid option '%s'\n", argument);
        not_ok = true;
      }
    } else {
      file = fopen(argument, "r");
      if (file == NULL) {
        fprintf(stderr, "s21_cat: %s: No such file or directory\n", argument);
        not_ok = true;
      }
    }
  }
  if (not_ok == false) print_cat(file, &flags);
  return 0;
}