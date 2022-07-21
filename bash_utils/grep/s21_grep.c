#include "s21_grep.h"

int main(int argc, char *argv[]) {
    struct flags options;
    int ret = 0;
    char pattern[buffer] = {0};
    memset(&options, 0, sizeof(options));
    ret = check_flags(argc, argv, &options, pattern);
    if ((argc >= 3) && (ret != 1)) {
        grep_main(&options, argc, argv, pattern);
    }
    return ret;
}

int check_flags(int argc, char *argv[], struct flags *options, char *pattern) {
    int i = 0, ret = 0;
    while ((i = getopt(argc, argv, "e:ivclnhsf:o")) != -1) {
        if (i == 'e') {
        options->is_e = 1;
        snprintf(pattern, buffer, "%s", optarg);
        } else if (i == 'i') {
        options->is_i = 1;
        } else if (i == 'v') {
        options->is_v = 1;
        } else if (i == 'c') {
        options->is_c = 1;
        } else if (i == 'l') {
        options->is_l = 1;
        } else if (i == 'n') {
        options->is_n = 1;
        } else if (i == 'h') {
        options->is_h = 1;
        } else if (i == 's') {
        options->is_s = 1;
        } else if (i == 'f') {
        options->is_f = 1;
        snprintf(pattern, buffer, "%s", optarg);
        } else if (i == 'o') {
        options->is_o = 1;
        } else {
        ret = 1;
        }
    }
    return ret;
}

void grep_main(struct flags *options, int argc, char **argv, char *temp) {
  char patt[buffer] = {0};
  int cols = 0;

  if (!options->is_f && !options->is_e) snprintf(patt, buffer, "%s", argv[optind++]);
  if (options->is_f) cols = save_patt_file(patt, temp);
  if (!options->is_f && options->is_e) snprintf(patt, buffer, "%s", temp);

  if (cols != -1) {
    int file_c = (argc - optind > 1) ? 1 : 0;

    for (int i = optind; i < argc; i++) {
      if (file_c && !options->is_h && !options->is_l) printf("%s:", argv[i]);
      grep_file(options, patt, argv[i]);
    }
  }
}

int save_patt_file(char *pattern, char *temp) {
  FILE *fp;
  fp = fopen(temp, "r");
  int i = 0;

  if (fp == NULL) {
    i = -1;
  } else {
    int ch;
    while ((ch = fgetc(fp)) != EOF) {
      if (ch == 13 || ch == 10) pattern[i++] = '|';
      if (ch != 13 && ch != 10) pattern[i++] = ch;
    }

    if (pattern[i - 1] == '|') pattern[i - 1] = '\0';
    fclose(fp);
  }
  return (i == -1) ? -1 : (i + 1);
}

void grep_file(struct flags *options, char *pattern, char *file) {
  int cflags = (options->is_i) ? REG_ICASE | REG_EXTENDED : REG_EXTENDED;
  regex_t reg;
  FILE *fp;
  fp = fopen(file, "r");

  if (fp == NULL) {
  } else {
    regcomp(&reg, pattern, cflags);
    filework(options, fp, reg, file);
    regfree(&reg);
    fclose(fp);
  }
}

void filework(struct flags *options, FILE *fp, regex_t reg, char *file) {
  char text[buffer] = {0};
  regmatch_t pmatch[1];
  int line_matches = 0, nline = 1;

  while (fgets(text, buffer - 1, fp) != NULL) {
    int status = regexec(&reg, text, 1, pmatch, 0);
    int match = 0;

    if (status == 0 && !options->is_v) match = 1;
    if (status == REG_NOMATCH && options->is_v) match = 1;
    if (match && !options->is_l && !options->is_c && options->is_n) printf("%d:", nline);
    if (match && !options->is_l && !options->is_c && !options->is_o) printf("%s", text);

    if (options->is_o && match) {
      for (int i = pmatch[0].rm_so; i < pmatch[0].rm_eo; i++) {
        printf("%c", text[i]);
      }
      printf("\n");
    }
    line_matches += match;
    nline++;
  }

  if (options->is_l && line_matches > 0) printf("%s\n", file);
  if (options->is_c && !options->is_l) printf("%d\n", line_matches);
}
