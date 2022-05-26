#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

// #if !defined(ck_assert_ptr_null)
// #define ck_assert_ptr_null(X) ck_assert_ptr_eq(X, NULL)
// #define ck_assert_ptr_nonnull(X) ck_assert_ptr_ne(X, NULL)
// #endif
// #if !defined(ck_assert_mem_eq)
// #define ck_assert_mem_eq(X, Y, L) ck_assert_uint_eq(memcmp(X, Y, L), 0)
// #endif

START_TEST(trimTest) {
    char* a = "*** Much -Ado About*** Nothing*- -***";
    char* b = "poppy***pop***";
    char* c = "poppy***pop";
    char* d = "***poppy***pop";
    char* tr_ch = "*- ";
    char* expa = "Much -Ado About*** Nothing";
    char* expbcd = "poppy***pop";

    char* res = (char*)s21_trim(a, tr_ch);
    ck_assert_str_eq(res, expa);
    free(res);
    res = (char*)s21_trim(b, tr_ch);
    ck_assert_str_eq(res, expbcd);
    free(res);
    res = (char*)s21_trim(c, tr_ch);
    ck_assert_str_eq(res, expbcd);
    free(res);
    res = (char*)s21_trim(d, tr_ch);
    ck_assert_str_eq(res, expbcd);
    free(res);
    res = (char*)s21_trim("", "abc");
    ck_assert_str_eq(res, "");
    free(res);
    res = (char*)s21_trim("abc", "");
    ck_assert_str_eq(res, "abc");
    free(res);

    res = (char*)s21_trim(s21_NULL, tr_ch);
    ck_assert_ptr_null(res);
    res = (char*)s21_trim(a, s21_NULL);
    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(insertTest) {
    char* a = "hellys";
    char* b = "o gu";
    char* exp = "hello guys";

    char* res = (char*)s21_insert(a, b, 4);
    ck_assert_str_eq(res, exp);
    free(res);

    res = (char*)s21_insert(a, b, 9);
    ck_assert_ptr_null(res);
    res = (char*)s21_insert(a, b, -1);
    ck_assert_ptr_null(res);
    res = (char*)s21_insert(s21_NULL, b, 4);
    ck_assert_ptr_null(res);
    res = (char*)s21_insert(a, s21_NULL, 4);
    ck_assert_ptr_null(res);
}
END_TEST

START_TEST(toupperTest) {
    char* str = "hello, guys HELLO, GUYS";
    char* str1 = "ёлки-иголки, привет, ребята ЁЛКИ-ИГОЛКИ, ПРИВЕТ, РЕБЯТА";
    char str2[] = "goodbye, guys GOODBYE, GUYS";
    char str3[3];
    str3[0] = 'H';
    str3[1] = 'i';
    str3[2] = '\0';
    char* str5 = NULL;

    char* res = (char*)s21_to_upper(str);
    ck_assert_str_eq(res, "HELLO, GUYS HELLO, GUYS");
    free(res);
    res = (char*)s21_to_upper(str1);
    ck_assert_str_eq(res, "ЁЛКИ-ИГОЛКИ, ПРИВЕТ, РЕБЯТА ЁЛКИ-ИГОЛКИ, ПРИВЕТ, РЕБЯТА");
    free(res);
    res = (char*)s21_to_upper(str2);
    ck_assert_str_eq(res, "GOODBYE, GUYS GOODBYE, GUYS");
    free(res);
    res = (char*)s21_to_upper(str3);
    ck_assert_str_eq(res, "HI");
    free(res);

    ck_assert_ptr_null(s21_to_upper(str5));
}
END_TEST

START_TEST(tolowerTest) {
    char* str = "hello, guys HELLO, GUYS";
    char* str1 = "ёлки-иголки, привет, ребята ЁЛКИ-ИГОЛКИ, ПРИВЕТ, РЕБЯТА";
    char str2[] = "goodbye, guys GOODBYE, GUYS";
    char str3[3];
    str3[0] = 'H';
    str3[1] = 'i';
    str3[2] = '\0';
    char* str5 = NULL;

    char* res = (char*)s21_to_lower(str);
    ck_assert_str_eq(res, "hello, guys hello, guys");
    free(res);
    res = (char*)s21_to_lower(str1);
    ck_assert_str_eq(res, "ёлки-иголки, привет, ребята ёлки-иголки, привет, ребята");
    free(res);
    res = (char*)s21_to_lower(str2);
    ck_assert_str_eq(res, "goodbye, guys goodbye, guys");
    free(res);
    res = (char*)s21_to_lower(str3);
    ck_assert_str_eq(res, "hi");
    free(res);

    ck_assert_ptr_null(s21_to_lower(str5));
}
END_TEST

START_TEST(strlenTest) {
    ck_assert_uint_eq(s21_strlen("abcd"), strlen("abcd"));
    ck_assert_uint_eq(s21_strlen(""), strlen(""));
    ck_assert_uint_eq(s21_strlen("hello!"), strlen("hello!"));
    ck_assert_uint_eq(s21_strlen("hello! \n hi!"), strlen("hello! \n hi!"));
    ck_assert_uint_eq(s21_strlen("hello! \0 hi!"), strlen("hello! "));
}
END_TEST

START_TEST(strchrTest) {
    char str[6] = "abcdbc";
    char* empty_str = "";
    ck_assert_ptr_eq(s21_strchr(str, 'b'), strchr(str, 'b'));
    ck_assert_str_eq(s21_strchr(str, 'b'), "bcdbc");
    ck_assert_str_eq(strchr(str, 'b'), "bcdbc");
    ck_assert_ptr_eq(s21_strchr(str, 'e'), strchr(str, 'e'));
    ck_assert_ptr_eq(s21_strchr(empty_str, 'b'), strchr(empty_str, 'b'));
    ck_assert_ptr_eq(s21_strchr(str, 0), strchr(str, 0));
    ck_assert_ptr_null(s21_strchr(str, 'e'));
}
END_TEST

START_TEST(strcmpTest) {
    char s21_mem[10];
    char mem[10];

    memset(s21_mem, 'i', 10);
    memset(mem, 'i', 10);
    mem[9] = '\0';
    s21_mem[9] = '\0';

    ck_assert_int_eq(s21_strcmp(s21_mem, mem), strcmp(s21_mem, mem));

    mem[4] = 'y';
    ck_assert_int_eq(s21_strcmp(s21_mem, mem) < 0, strcmp(s21_mem, mem) < 0);

    mem[4] = 'a';
    ck_assert_int_eq(s21_strcmp(s21_mem, mem) > 0, strcmp(s21_mem, mem) > 0);
    ck_assert_int_eq(s21_strcmp(s21_mem, "") > 0, strcmp(s21_mem, "") > 0);
    ck_assert_int_eq(s21_strcmp("", mem) < 0, strcmp("", mem) < 0);
}
END_TEST

START_TEST(strncmpTest) {
    char s21_mem[10];
    char mem[10];

    memset(s21_mem, 'i', 10);
    memset(mem, 'i', 10);

    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 2), strncmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 10), strncmp(s21_mem, mem, 10));
    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 0), strncmp(s21_mem, mem, 0));

    mem[4] = 'y';

    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 2), strncmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_strncmp(s21_mem, mem, 10) < 0, strncmp(s21_mem, mem, 10) < 0);
    ck_assert_int_eq(s21_strncmp(s21_mem, "", 10) > 0, strncmp(s21_mem, "", 10) > 0);
    ck_assert_int_eq(s21_strncmp("", mem, 10) < 0, strncmp("", mem, 10) < 0);
}
END_TEST

START_TEST(strcatTest) {
    char str[10], s21_str[10];
    for (int i = 0; i < 10; i++) {
        str[i] = '\0';
        s21_str[i] = '\0';
    }
    ck_assert_str_eq(s21_strcat(s21_str, ""), strcat(str, ""));
    ck_assert_str_eq(s21_strcat(s21_str, "d"), strcat(str, "d"));
    ck_assert_str_eq(s21_strcat(s21_str, "v"), strcat(str, "v"));
    ck_assert_str_eq(s21_strcat(s21_str, "d"), strcat(str, "d"));
    ck_assert_str_eq(s21_strcat(s21_str, ""), strcat(str, ""));
    ck_assert_str_eq(s21_strcat(s21_str, "12"), strcat(str, "12"));
    ck_assert_str_eq(s21_strcat(s21_str, "1z"), strcat(str, "1z"));
}
END_TEST

START_TEST(strncatTest) {
    char str[10], s21_str[10];
    for (int i = 0; i < 10; i++) {
        str[i] = '\0';
        s21_str[i] = '\0';
    }
    ck_assert_str_eq(s21_strncat(s21_str, "", 0), strncat(str, "", 0));
    ck_assert_str_eq(s21_strncat(s21_str, "", 1), strncat(str, "", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "vv", 1), strncat(str, "vv", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "dvd", 1), strncat(str, "dvd", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "", 1), strncat(str, "", 1));
    ck_assert_str_eq(s21_strncat(s21_str, "1z", 3), strncat(str, "1z", 3));
}
END_TEST

START_TEST(memchrTest) {
    char str[6] = "abcdbc";
    char* empty_str = "";
    ck_assert_ptr_eq(s21_memchr(str, 'b', 3), memchr(str, 'b', 3));
    ck_assert_ptr_eq(s21_memchr(str, 'b', 1), memchr(str, 'b', 1));
    ck_assert_ptr_eq(s21_memchr(str, 'b', 0), memchr(str, 'b', 0));
    ck_assert_ptr_eq(s21_memchr(str, 'b', 6), memchr(str, 'b', 6));
    ck_assert_ptr_eq(s21_memchr(str, 'e', 6), memchr(str, 'e', 6));
    ck_assert_ptr_eq(s21_memchr(str, 'e', 3), memchr(str, 'e', 3));
    ck_assert_ptr_eq(s21_memchr(str, 'e', 0), memchr(str, 'e', 0));
    ck_assert_ptr_eq(s21_memchr(str, 500, 2), memchr(str, 500, 2));
    ck_assert_ptr_eq(s21_memchr(empty_str, 500, 1), memchr(empty_str, 500, 1));
    ck_assert_ptr_eq(s21_memchr(empty_str, 'b', 10), memchr(empty_str, 'b', 10));
    ck_assert_ptr_eq(s21_memchr(str, 0, 1), memchr(str, 0, 1));
    ck_assert_ptr_eq(s21_memchr(empty_str, 0, 10), memchr(empty_str, 0, 10));
}
END_TEST

START_TEST(memcmpTest) {
    void* s21_mem = malloc(10 * sizeof(char));
    void* mem = malloc(10 * sizeof(char));

    memset(s21_mem, 'i', 10);
    memset(mem, 'i', 10);

    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 2), memcmp(s21_mem, mem, 2));
    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 10), memcmp(s21_mem, mem, 10));
    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 0), memcmp(s21_mem, mem, 0));

    memset(s21_mem, 'y', 4);

    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 2) > 0, memcmp(s21_mem, mem, 2) > 0);
    ck_assert_int_eq(s21_memcmp(s21_mem, mem, 10) > 0, memcmp(s21_mem, mem, 10) > 0);
    ck_assert_int_eq(s21_memcmp(mem, s21_mem, 2) < 0, memcmp(mem, s21_mem, 2) < 0);
    ck_assert_int_eq(s21_memcmp(mem, s21_mem, 10) < 0, memcmp(mem, s21_mem, 10) < 0);
    ck_assert_int_eq(s21_memcmp(s21_mem, "", 10), memcmp(s21_mem, "", 10));
    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(memsetTest) {
    void* s21_mem = malloc(10 * sizeof(char));
    void* mem = malloc(10 * sizeof(char));
    s21_memset(s21_mem, 'y', 10);
    memset(mem, 'y', 10);
    ck_assert_mem_eq(s21_mem, mem, 10);

    s21_memset(s21_mem, '5', 4);
    memset(mem, '5', 4);
    ck_assert_mem_eq(s21_mem, mem, 4);

    s21_memset(s21_mem, '\0', 10);
    memset(mem, '\0', 10);
    ck_assert_mem_eq(s21_mem, mem, 10);

    free(mem);
    free(s21_mem);
}
END_TEST

START_TEST(memcpyTest) {
    void* s21_mem = malloc(10 * sizeof(char));
    void* mem = malloc(10 * sizeof(char));
    memset(s21_mem, '2', 10);
    memset(mem, '1', 10);
    memset(s21_mem, '2', 10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 10);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(memcpy_src_bigger_destTest) {
    void* s21_mem = malloc(5 * sizeof(char));
    void* mem = malloc(10 * sizeof(char));
    memset(s21_mem, '2', 5);
    memset(mem, '1', 10);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 5);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(memcpy_dest_bigger_srcTest) {
    void* s21_mem = malloc(10 * sizeof(char));
    void* mem = malloc(5 * sizeof(char));
    memset(s21_mem, '2', 10);
    memset(mem, '1', 5);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 10), mem, 5);
    ck_assert_mem_eq(s21_memcpy(s21_mem, mem, 8), mem, 5);
    free(s21_mem);
    free(mem);
}
END_TEST

START_TEST(memmoveTest) {
    void* src1 = malloc(10 * sizeof(char));
    void* dest1 = malloc(10 * sizeof(char));
    memset(src1, '2', 10);
    memset(dest1, '1', 10);
    ck_assert_mem_eq(s21_memmove(dest1, src1, 8), dest1, 8);
    free(src1);
    free(dest1);

    void* src2 = malloc(10 * sizeof(char));
    void* dest2 = src2 + 4;
    void* src3 = malloc(10 * sizeof(char));
    void* dest3 = src3 + 4;
    memset(src2, '2', 10);
    memset(src3, '2', 10);

    ck_assert_mem_eq(s21_memmove(dest2, src2, 6), dest2, 6);
    ck_assert_str_eq(s21_memmove(dest2, src2, 6), memmove(dest3, src3, 6));

    free(src2);
    free(src3);
}
END_TEST

START_TEST(strcpyTest) {
    char* s21_str = (char*)malloc(10 * sizeof(char));
    char* str = "1234567890";
    ck_assert_str_eq(s21_strcpy(s21_str, str), str);
    ck_assert_str_eq(s21_strcpy(s21_str, ""), s21_str);
    ck_assert_str_eq(s21_strcpy(s21_str, "123456789000"), "123456789000");
    free(s21_str);
}
END_TEST

START_TEST(strncpyTest) {
    char s21_str[] = "Sorry, my bad";
    char str[] = "Sorry, my bad";
    char s21_dest[] = "12345678901234567890";
    char dest[] = "12345678901234567890";
    char s21_2_dest[20] = "";

    ck_assert_str_eq(s21_strncpy(s21_dest, s21_str, 9), strncpy(dest, str, 9));
    ck_assert_str_eq(s21_strncpy(s21_dest, s21_str, 10), strncpy(dest, str, 10));
    ck_assert_str_eq(s21_strncpy(s21_dest, s21_str, 16), strncpy(dest, str, 16));
    ck_assert_str_eq(s21_strncpy(s21_2_dest, s21_str, 10), strncpy(s21_2_dest, str, 10));
}
END_TEST

START_TEST(strcspnTest) {
    ck_assert_uint_eq(s21_strcspn("aaaOOO", "O"), strcspn("aaaOOO", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOaa", "O"), strcspn("aaaOOOaa", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOoo", "Oo"), strcspn("aaaOOOo", "Oo"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOoo", "Ooo"), strcspn("aaaOOOo", "Ooo"));
    ck_assert_uint_eq(s21_strcspn("", "O"), strcspn("", "O"));
    ck_assert_uint_eq(s21_strcspn("aaaOOOaa", ""), strcspn("aaaOOOaa", ""));
}
END_TEST

START_TEST(strpbrkTest) {
    char* str1 = "aAaxxxx";
    ck_assert_ptr_eq(s21_strpbrk(str1, "ax"), strpbrk(str1, "ax"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "x"), strpbrk(str1, "x"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "xA"), strpbrk(str1, "xA"));
    ck_assert_ptr_eq(s21_strpbrk(str1, "z"), strpbrk(str1, "z"));
    ck_assert_ptr_eq(s21_strpbrk(str1, ""), strpbrk(str1, ""));
    ck_assert_ptr_eq(s21_strpbrk("", "ax"), strpbrk("", "ax"));
}
END_TEST

START_TEST(strerrorTest) {
#if defined(__linux__)
    for (int i = -3; i <= 135; i++) {
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
#elif defined(__APPLE__) || defined(__MACH__)
    for (int i = -3; i <= 108; i++) {
        ck_assert_str_eq(s21_strerror(i), strerror(i));
    }
#endif
}
END_TEST

START_TEST(strrchrTest) {
    char str[50] = "abcdbc";
    char* empty_str = "";
    ck_assert_ptr_eq(s21_strrchr(str, 'b'), strrchr(str, 'b'));
    ck_assert_str_eq(s21_strrchr(str, 'b'), "bc");
    ck_assert_ptr_eq(s21_strrchr(str, 'e'), strrchr(str, 'e'));
    ck_assert_ptr_eq(s21_strrchr(empty_str, 'b'), strrchr(empty_str, 'b'));
    ck_assert_ptr_eq(s21_strrchr(str, 0), strrchr(str, 0));
    ck_assert_ptr_null(s21_strrchr(str, 'e'));
}
END_TEST

START_TEST(strspnTest) {
    ck_assert_uint_eq(s21_strspn("aaaOOO", "O"), strspn("aaaOOO", "O"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaa", "O"), strspn("aaaOOOaa", "O"));
    ck_assert_uint_eq(s21_strspn("", "O"), strspn("", "O"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaa", ""), strspn("aaaOOOaa", ""));
    ck_assert_uint_eq(s21_strspn("aaaOOOaaPPP", "Oa"), strspn("aaaOOOaaPPP", "Oa"));
    ck_assert_uint_eq(s21_strspn("aaaOOOaaPPP", "aO"), strspn("aaaOOOaaPPP", "aO"));
}
END_TEST

START_TEST(strstrTest) {
    char* str = "It is test for test";
    char* empty = "";
    ck_assert_ptr_eq(s21_strstr(str, "It"), strstr(str, "It"));
    ck_assert_ptr_eq(s21_strstr(str, "IT"), strstr(str, "IT"));
    ck_assert_ptr_null(s21_strstr(str, "IT"));
    ck_assert_ptr_eq(s21_strstr(str, " test"), strstr(str, " test"));
    ck_assert_ptr_eq(s21_strstr(str, " "), strstr(str, " "));
    ck_assert_ptr_eq(s21_strstr(str, ""), strstr(str, ""));
    ck_assert_ptr_eq(s21_strstr(empty, ""), strstr(empty, ""));
    ck_assert_ptr_eq(s21_strstr(empty, " test"), strstr(empty, " test"));
}
END_TEST

START_TEST(strtokTest) {
    char str[] = "12|34*56|78m90";
    char s21_str[] = "12|34*56|78m90";
    char delim[] = "*m|";
    char* part = strtok(str, delim);
    char* s21_part = s21_strtok(s21_str, delim);
    ck_assert_str_eq(part, s21_part);

    while (part != NULL) {
        part = strtok(NULL, delim);
        s21_part = s21_strtok(NULL, delim);
        if (part != NULL) {
            ck_assert_str_eq(part, s21_part);
        } else {
            ck_assert_ptr_null(s21_part);
        }
    }

    char str1[] = "m12345m67890m";
    char s21_str1[] = "m12345m67890m";
    char delim1[] = "m";

    part = strtok(str1, delim1);
    s21_part = s21_strtok(s21_str1, delim1);
    ck_assert_str_eq(part, s21_part);

    while (part != NULL) {
        part = strtok(NULL, delim1);
        s21_part = s21_strtok(NULL, delim1);
        if (part != NULL) {
            ck_assert_str_eq(part, s21_part);
        } else {
            ck_assert_ptr_null(s21_part);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_c1) {
    char s1[64];
    char s2[64];
    char* format = "%c";
    char f = 'a';
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_c2) {
    char s1[64];
    char s2[64];
    char* format = "%10c";
    char f = 'a';
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_c3) {
    char s1[64];
    char s2[64];
    char* format = "%10.23c";
    char f = 'a';
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_c4) {
    char s1[64];
    char s2[64];
    char* format = "%10.23lc";
    unsigned long f = L'a';
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_c5) {
    int size_var = 10;
    char* format[] = {"%c", "%60c", "%-20c", "%+c", "%3c", "%.1c", "%.0c", "%.c", "%8.3c", "%.15c"};
    char val = 'c';

    for (int j = 0; j < size_var; j++) {
        char s1[64];
        char s2[64];

        ck_assert_int_eq(s21_sprintf(s1, format[j], val), sprintf(s2, format[j], val));
        ck_assert_str_eq(s1, s2);
    }
}
END_TEST

START_TEST(s21_sprintf_test_d1) {
    char s1[64];
    char s2[64];
    char* format = "% 10d";
    int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_d2) {
    char s1[64];
    char s2[64];
    char* format = "%ld";
    long int f = 232313;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_d3) {
    char s1[64];
    char s2[64];
    char* format = "%10.23hd";
    short int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_d4) {
    int i = 6987343;
    char str1[80] = "1";
    char str2[80] = "2";
    char format10[50] = "% -20d ";
    int res = sprintf(str1, format10, i);
    int res2 = s21_sprintf(str2, format10, i);
    ck_assert_int_eq(res, res2);
    ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(s21_sprintf_test_d5) {
    int size_var = 6;
    char* format[] = {"%+20.0d", "%.0d", "%-20.0d", "%-20.4d", "%-3.4d", "%20.1d"};
    int val[] = {0, +0, -0, 123, -123, +54};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_d6) {
    int size_var = 5;
    char* format[] = {"%+20.0ld", "%.0ld", "%-20.0ld", "%-20.4ld", "%-3.4ld"};
    long int val[] = {52836951, 0, +0, -0, 123, -123, +54};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(long int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_i1) {
    char s1[64];
    char s2[64];
    char* format = "% 10i";
    int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_i2) {
    char s1[64];
    char s2[64];
    char* format = "%+li";
    long int f = -10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_i3) {
    char s1[64];
    char s2[64];
    char* format = "%10.23hi";
    short int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_i4) {
    int size_var = 5;
    char* format[] = {"%+20.0i", "%.0i", "%-20.0i", "%-20.4i", "%-3.4i"};
    int val[] = {0, +0, -0, 123, -123, +54};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_i5) {
    int size_var = 5;
    char* format[] = {"%+20.0li", "%.0li", "%-20.0li", "%-20.4li", "%-3.4li"};
    long int val[] = {52836951, 0, +0, -0, 123, -123, +54};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(long int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_s1) {
    char s1[64];
    char s2[64];
    char* format = "%s";
    char* f = "hello";
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_s2) {
    char s1[64];
    char s2[64];
    char* format = "%s";
    char* f = "hello how how how ";
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_s3) {
    char s1[64];
    char s2[64];
    char* format = "%s";
    wchar_t* f = L"hello how how how ";
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_s4) {
    int size_var = 11;
    int size_var2 = 6;
    char* format[] = {"%3s", "%9s", "%3.8s", "%.5s", "%8.3s", "%.1s",
                      "%.0s", "%.s", "%15s", "%.15s", "%-20s"};
    char* val[] = {"asd", "qwert", "hello", "1234567", "qq", "hello every one verter sasat"};

    for (int j = 0; j < size_var; j++) {
        for (int i = 0; i < size_var2; i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_u1) {
    char s1[64];
    char s2[64];
    char* format = "%20u";
    char* format1 = " %1.21u ";
    unsigned int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_int_eq(s21_sprintf(s1, format1, 1233), sprintf(s2, format1, 1233));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_u2) {
    char s1[64];
    char s2[64];
    char* format = "%10.23hu";
    unsigned short int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_u3) {
    char s1[64];
    char s2[64];
    char* format = "%-0.23lu";
    unsigned long int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_u4) {
    char s1[64];
    char s2[64];
    char* format = "%-23.23lu";
    unsigned long int f = 3232;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_u5) {
    char s1[64];
    char s2[64];
    char* format = "%-23.23u";
    unsigned short int f = 10;
    ck_assert_int_eq(s21_sprintf(s1, format, f), sprintf(s2, format, f));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_u6) {
    char s1[64];
    char s2[64];
    char* format = "%.3u %u %20.3u";
    unsigned short int f = 12;
    unsigned short int f2 = 0;
    unsigned short int f3 = 13;
    ck_assert_int_eq(s21_sprintf(s1, format, f, f2, f3), sprintf(s2, format, f, f2, f3));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_u7) {
    int size_var = 5;
    char* format[] = {"%+20.0u", "%.0u", "%-20.0u", "%-20.4u", "%-3.4u"};
    unsigned int val[] = {0, +0, -0, 123, -123, 534, +54, 54, -44};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(unsigned int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_u8) {
    int size_var = 5;
    char* format[] = {"%+20.0lu", "%.0lu", "%-20.0lu", "%-20.4lu", "%-3.4lu"};
    unsigned long int val[] = {52836951, 0, +0, -0, 123123123, -123123, 534, +54, 54, -44};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(unsigned long int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_u9) {
    int size_var = 5;
    char* format[] = {"%+20.0hu", "%.0hu", "%-20.0hu", "%-20.4hu", "%-3.4hu"};
    unsigned short int val[] = {56951, 0, +0, -0, 123, -123, 534, +54, 54, -44};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(unsigned short int); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_percent2) {
    char s1[64];
    char s2[64];
    ck_assert_int_eq(s21_sprintf(s1, "hello %%"), sprintf(s2, "hello %%"));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_mix1) {
    char s1[64];
    char s2[64];
    char* format = "%s %d %lu";
    char* s = "hello";
    int d = 12;
    long unsigned int lu = 123;
    ck_assert_int_eq(s21_sprintf(s1, format, s, d, lu), sprintf(s2, format, s, d, lu));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_mix2) {
    char s1[64];
    char s2[64];
    char* format = "%.3s %+ d %-lu";
    char* s = "hello";
    int d = 12;
    long unsigned int lu = 123;
    ck_assert_int_eq(s21_sprintf(s1, format, s, d, lu), sprintf(s2, format, s, d, lu));
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_f1) {
    int size_var = 6;
    char* format[] = {"%6.1f", "%-7.2f", "% .3f", "%f", "%4f", "%2f"};
    float val[] = {-11.1234, 123.11, 0.12345218, 99.1, 123.2145};
    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(float); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_f2) {
    int size_var = 5;
    char* format[] = {"%20f", "%f", "%+f", "%-f", "% f"};
    float val[] = {15.1, 15.00010, 15.323, 0.0032, 0.000001, -15.00045};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(float); i++) {
            char s1[64];
            char s2[64];
            ck_assert_int_eq(s21_sprintf(s1, format[j], val[i]), sprintf(s2, format[j], val[i]));
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_f3) {
    int size_var = 10;
    char* format[] = {"%20.5f", "%.0f", "%.f", "%.1f", "%-.3f", "%.12f",
                      "%10.3f", "%+22.8f", "%6.0f", "%+.0f"};
    float val[] = {123.0, 1.6674, 0.555, 0.455, 0.445, -15.344,
                   0.0032, 0.00000000, -0, +0, 0, 15.236};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(float); i++) {
            char s1[64];
            char s2[64];
            ck_assert_int_eq(s21_sprintf(s1, format[j], val[i]), sprintf(s2, format[j], val[i]));
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_f4) {
    int size_var = 6;
    char* format[] = {"%20f", "%f", "%+f", "%-f", "% f", "% .3f"};
    float val[] = {123, 15.0, 15, 0.00000000};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(float); i++) {
            char s1[64];
            char s2[64];
            ck_assert_int_eq(s21_sprintf(s1, format[j], val[i]), sprintf(s2, format[j], val[i]));
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_f5) {
    int size_var = 6;
    char* format[] = {"%6.1f", "%-7.2f", "% .3f", "%f", "%4f", "%2f"};
    float val[] = {99.99992222222};
    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(float); i++) {
            char s1[64];
            char s2[64];
            int res2 = sprintf(s2, format[j], val[i]);
            int res = s21_sprintf(s1, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

START_TEST(s21_sprintf_test_f6) {
    char* format = "%.2f %f %.7f %.1f %.f % .5f";
    float val[] = {-11.1234, 123.11, 0.12345218, 99.1, 123.2145, 14.345};
    char s1[64];
    char s2[64];
    int res = s21_sprintf(s1, format, val[0], val[1], val[2], val[3], val[4], val[5]);
    int res2 = sprintf(s2, format, val[0], val[1], val[2], val[3], val[4], val[5]);
    ck_assert_int_eq(res, res2);
    ck_assert_str_eq(s1, s2);
}
END_TEST

START_TEST(s21_sprintf_test_f7) {
    int size_var = 7;
    char* format[] = {"%+20.0f", "%.0f", "%-20.0f", "%-20.4f", "%-3.4f", "%8.3f", "%3.8f"};
    float val[] = {-11.1234, 123.11, 0.12345218, 99.1, 123.2145, 14.345, 0, +0, -0, 123, -123, +54};

    for (int j = 0; j < size_var; j++) {
        for (s21_size_t i = 0; i < sizeof(val) / sizeof(float); i++) {
            char s1[64];
            char s2[64];
            int res = s21_sprintf(s1, format[j], val[i]);
            int res2 = sprintf(s2, format[j], val[i]);
            ck_assert_int_eq(res, res2);
            ck_assert_str_eq(s1, s2);
        }
    }
}
END_TEST

int main() {
    Suite* s1 = suite_create("Core");
    TCase* tc1_1 = tcase_create("Core");
    SRunner* sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, trimTest);
    tcase_add_test(tc1_1, insertTest);
    tcase_add_test(tc1_1, toupperTest);
    tcase_add_test(tc1_1, tolowerTest);
    tcase_add_test(tc1_1, strlenTest);
    tcase_add_test(tc1_1, strchrTest);
    tcase_add_test(tc1_1, strcmpTest);
    tcase_add_test(tc1_1, strncmpTest);
    tcase_add_test(tc1_1, strcatTest);
    tcase_add_test(tc1_1, strncatTest);
    tcase_add_test(tc1_1, memchrTest);
    tcase_add_test(tc1_1, memcmpTest);
    tcase_add_test(tc1_1, memsetTest);
    tcase_add_test(tc1_1, memcpyTest);
    tcase_add_test(tc1_1, memcpy_dest_bigger_srcTest);
    tcase_add_test(tc1_1, memcpy_src_bigger_destTest);
    tcase_add_test(tc1_1, memmoveTest);
    tcase_add_test(tc1_1, strcpyTest);
    tcase_add_test(tc1_1, strncpyTest);
    tcase_add_test(tc1_1, strcspnTest);
    tcase_add_test(tc1_1, strpbrkTest);
    tcase_add_test(tc1_1, strerrorTest);
    tcase_add_test(tc1_1, strrchrTest);
    tcase_add_test(tc1_1, strspnTest);
    tcase_add_test(tc1_1, strstrTest);
    tcase_add_test(tc1_1, strtokTest);

    tcase_add_test(tc1_1, s21_sprintf_test_c1);
    tcase_add_test(tc1_1, s21_sprintf_test_c2);
    tcase_add_test(tc1_1, s21_sprintf_test_c3);
    tcase_add_test(tc1_1, s21_sprintf_test_c4);
    tcase_add_test(tc1_1, s21_sprintf_test_c5);

    tcase_add_test(tc1_1, s21_sprintf_test_d1);
    tcase_add_test(tc1_1, s21_sprintf_test_d2);
    tcase_add_test(tc1_1, s21_sprintf_test_d3);
    tcase_add_test(tc1_1, s21_sprintf_test_d4);
    tcase_add_test(tc1_1, s21_sprintf_test_d5);
    tcase_add_test(tc1_1, s21_sprintf_test_d6);

    tcase_add_test(tc1_1, s21_sprintf_test_i1);
    tcase_add_test(tc1_1, s21_sprintf_test_i2);
    tcase_add_test(tc1_1, s21_sprintf_test_i3);
    tcase_add_test(tc1_1, s21_sprintf_test_i4);
    tcase_add_test(tc1_1, s21_sprintf_test_i5);

    tcase_add_test(tc1_1, s21_sprintf_test_s1);
    tcase_add_test(tc1_1, s21_sprintf_test_s2);
    tcase_add_test(tc1_1, s21_sprintf_test_s3);
    tcase_add_test(tc1_1, s21_sprintf_test_s4);

    tcase_add_test(tc1_1, s21_sprintf_test_u1);
    tcase_add_test(tc1_1, s21_sprintf_test_u2);
    tcase_add_test(tc1_1, s21_sprintf_test_u3);
    tcase_add_test(tc1_1, s21_sprintf_test_u4);
    tcase_add_test(tc1_1, s21_sprintf_test_u5);
    tcase_add_test(tc1_1, s21_sprintf_test_u6);
    tcase_add_test(tc1_1, s21_sprintf_test_u7);
    tcase_add_test(tc1_1, s21_sprintf_test_u8);
    tcase_add_test(tc1_1, s21_sprintf_test_u9);

    tcase_add_test(tc1_1, s21_sprintf_test_percent2);

    tcase_add_test(tc1_1, s21_sprintf_test_mix1);
    tcase_add_test(tc1_1, s21_sprintf_test_mix2);

    tcase_add_test(tc1_1, s21_sprintf_test_f1);
    tcase_add_test(tc1_1, s21_sprintf_test_f2);
    tcase_add_test(tc1_1, s21_sprintf_test_f3);
    tcase_add_test(tc1_1, s21_sprintf_test_f4);
    tcase_add_test(tc1_1, s21_sprintf_test_f5);
    tcase_add_test(tc1_1, s21_sprintf_test_f6);
    tcase_add_test(tc1_1, s21_sprintf_test_f7);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
