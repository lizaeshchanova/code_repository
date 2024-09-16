#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
  int o;
  char ar_str[4096];
  char ar_reg[4096];
  char arr_o[4096];
  int cnt_files;
} Flags;

int parsing(int argc, char *argv[], Flags *flags);
void blockCL(Flags *flags, char *name, int cntIdent);
void blockO(Flags *flags, regex_t reg, regmatch_t infoMatch);
void print_grep(char *name, Flags *flags);