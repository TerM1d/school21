#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
    int b;
    int e;
    int n;
    int s;
    int t;
    int v;
    int T;
    int E;
} flags;

int flag_v(int cur) {
    if ((cur >= 0 && cur < 9) || (cur > 10 && cur < 32)) {
        printf("^");
        cur += 64;
    }
    return cur;
}

int open_file(char *argv[], flags flag) {
    FILE *fp;
    int ret = 0;
    fp = fopen(argv[optind], "r");
    if (fp != NULL) {
        int str_count = 1;
        int empty_count = 0;
        int end_sym = '\n';
        while (1) {
            int cur = fgetc(fp);
            if (cur == EOF) {
                break;
            }
            if (flag.s && cur == '\n' && end_sym == '\n') {
                empty_count++;
                if (empty_count > 1) {
                    continue;
                }
            } else {
                empty_count = 0;
            }
            if (end_sym == '\n' && ((flag.b && cur != '\n') || flag.n)) {
                printf("%6d\t", str_count++);
            }
            if (flag.t) {
                if ((cur >= 0 && cur <= 9) || (cur > 10 && cur < 32)) {
                    printf("^");
                    cur += 64;
                }
            }
            if (flag.T && cur == '\t') {
                printf("^");
                cur = 'I';
            }
            if (flag.e) {
                if (cur == 10)
                    printf("$");
                cur = flag_v(cur);
            }
            if (flag.E && cur == '\n') {
                printf("$");
            }
            if (flag.v) {
                cur = flag_v(cur);
            }
            printf("%c", cur);
            end_sym = cur;
        }
        fclose(fp);
    } else {
        ret = -1;
    }
    return ret;
}

int main(int argc, char *argv[]) {
    flags flag;
    flag.b = 0;
    flag.e = 0;
    flag.n = 0;
    flag.s = 0;
    flag.t = 0;
    flag.v = 0;
    flag.T = 0;
    flag.E = 0;
    int err = 1;
    int i = 1;
    int index = 0;
    int rez = 0;
    static struct option options[] = {
        {"number-nonblank", 0, 0, 'b'},
        {"number", 0, 0, 'n'},
        {"squeeze-blank", 0, 0, 's'},
        {0, 0, 0, 0},
    };
    while ((rez = getopt_long(argc, argv, "beEvnstT", options, &index)) != -1) {
        switch (rez) {
        case 'b':
            flag.b = 1;
            break;
        case 'e':
            flag.e = 1;
            break;
        case 'n':
            flag.n = 1;
            break;
        case 's':
            flag.s = 1;
            break;
        case 't':
            flag.t = 1;
            break;
        case 'v':
            flag.v = 1;
            break;
        case 'T':
            flag.T = 1;
            break;
        case 'E':
            flag.E = 1;
        default:
            break;
        }

        i++;
    }

    while (optind < argc) {
        err = open_file(argv, flag);
        optind++;
    }
    return err;
}
