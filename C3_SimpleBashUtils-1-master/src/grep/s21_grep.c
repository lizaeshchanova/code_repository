#include "s21_grep.h"

int parsing(int argc, char *argv[], Flags *flags) {
  int opt;
  while ((opt = getopt_long(argc, argv, "e:ivclno", NULL, 0)) != (-1)) {
    switch (opt) {
      case 'e': {
        flags->e = 1;
        strcat(flags->ar_reg, optarg);
        strcat(flags->ar_reg, "|");
      } break;
      case 'i':
        flags->i = 1;
        break;
      case 'v':
        flags->v = 1;
        break;
      case 'c':
        flags->c = 1;
        break;
      case 'l':
        flags->l = 1;
        break;
      case 'n':
        flags->n = 1;
        break;
      case 'o':
        flags->o = 1;
        break;
    }
  }
  if (!flags->e) {
    if (argc > optind) strcat(flags->ar_reg, argv[optind]);
    optind++;
  }
  if (flags->e) flags->ar_reg[strlen(flags->ar_reg) - 1] = '\0';
  if (argc - optind > 1) flags->cnt_files = 1;
  return optind;
}

void blockCL(Flags *flags, char *name, int cntIdent) {
  if (flags->c && flags->l && flags->cnt_files)
    printf("%s:%d\n", name, cntIdent);
  if (flags->c && flags->l && !flags->cnt_files && cntIdent > 0)
    printf("1\n%s\n", name);
}
void blockO(Flags *flags, regex_t reg, regmatch_t infoMatch) {
  if (flags->o && !flags->c && !flags->l) {
    char *ptr = flags->arr_o;
    if (flags->v) {
      printf("%s", flags->ar_str);
    } else {
      while ((regexec(&reg, ptr, 1, &infoMatch, 0) == 0)) {
        printf("%.*s\n", (int)(infoMatch.rm_eo - infoMatch.rm_so),
               ptr + infoMatch.rm_so);
        ptr += infoMatch.rm_eo;
      }
    }
  }
}

void print_grep(char *name, Flags *flags) {
  FILE *file;
  regmatch_t infoMatch;
  regex_t reg;
  file = fopen(name, "r");

  if (regcomp(&reg, flags->ar_reg, (flags->i) ? REG_ICASE : REG_EXTENDED) ==
      0) {
    if (file != NULL) {
      int cntIdent = 0, numStr = 0;
      while (fgets(flags->ar_str, sizeof(flags->ar_str), file) != NULL) {
        numStr++;
        if (flags->o) strcpy(flags->arr_o, flags->ar_str);

        int match = regexec(&reg, flags->ar_str, 1, &infoMatch, 0);
        if ((!match && !flags->v) || (match && flags->v)) {
          if (flags->l && cntIdent == 0 && !flags->c) printf("%s\n", name);

          cntIdent++;

          if (flags->cnt_files && !flags->l && !flags->c) printf("%s:", name);

          if (flags->c) continue;

          if (!flags->l && !flags->c && flags->n) {
            if (flags->o)
              printf("%d:", numStr);
            else
              printf("%d:%s", numStr, flags->ar_str);
          }

          if (!flags->l && !flags->c && !flags->n && !flags->o)
            printf("%s", flags->ar_str);
          blockO(flags, reg, infoMatch);
        }
      }
      if (flags->c && !flags->l && !flags->cnt_files) printf("%d\n", cntIdent);

      blockCL(flags, name, cntIdent);
      if (flags->c && flags->cnt_files && !flags->l)
        printf("%s:%d\n", name, cntIdent);
      fclose(file);
    } else
      fprintf(stderr, "s21_grep: %s: No such file or directory\n", name);
  }
  regfree(&reg);
}

int main(int argc, char *argv[]) {
  Flags flags = {0};

  for (int opt = parsing(argc, argv, &flags); opt < argc; opt++) {
    print_grep(argv[opt], &flags);
  }
  return 0;
}