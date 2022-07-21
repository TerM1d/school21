#ifndef _SRC_GREP_S21_GREP_H_
#define _SRC_GREP_S21_GREP_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>
#include <getopt.h>
#define buffer 999999

struct flags {
    int is_e;
    int is_i;
    int is_v;
    int is_c;
    int is_l;
    int is_n;
    int is_h;
    int is_s;
    int is_f;
    int is_o;
};

int check_flags(int argc, char *argv[], struct flags *options, char *pattern);
void filework(struct flags *options, FILE *fp, regex_t reg, char *file);
void grep_file(struct flags *options, char *pattern, char *file);
int save_patt_file(char *pattern, char *temp);
void grep_main(struct flags *options, int argc, char **argv, char *temp);

#endif // _SRC_GREP_S21_GREP_H_