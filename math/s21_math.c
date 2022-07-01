#include "s21_math.h"

int s21_abs(int x) {
    if (x < 0) {
        x = -x;
    }
    return x;
}

long double s21_acos(double x) {
    long double rez = 0;
    if (x < 0) {
        rez = s21_PI - s21_atan(s21_sqrt(1 - s21_pow(x * -1.0, 2)) / (x * -1.0));
    } else {
        rez = s21_atan(s21_sqrt(1.0 - (x * x)) / x);
    }
    return rez;
}

long double s21_asin(double x) {
    return s21_atan(x / s21_sqrt(1.0 - (x * x)));
}

long double s21_atan(double x) {
    int isneg = 0;
    long double res = 0;
    if (x != x) {
        res = s21_NAN;
    } else {
        if (x < 0) {
            x *= -1;
            isneg = 1;
        }
        if (x == 1.0)
            res = s21_PI / 4;
        if (x < 1) {
            if (x <= 2 - s21_sqrt(3)) {
                res = x - s21_pow(x, 3) / 3.0;
                for (int i = 5, j = -1; i < 100; i += 2, j *= -1)
                    res = res - j * s21_pow(x, i) / i;
            } else {
                res = s21_PI / 6.0 + s21_atan((s21_sqrt(3.0) * x - 1.0) / (s21_sqrt(3.0) + x));
            }
        }
        if (x > 1)
            res = s21_PI / 2.0 - s21_atan(1.0 / x);
        if (isneg)
            res *= -1;
    }
    return res;
}

long double s21_ceil(double x) {
    double sign = 1.0;
    if (x < 0)
        sign = -1.0;

    long double res = (long)(x);
    long double res2 = x - res;

    if (res2 > 1e-15)
        res += 1.0;

    if (sign == -1.0 && res == 0)
        res *= sign;
    return res;
}

long double s21_cos(double x) {
    x = s21_fmod(x, 2.0 * s21_PI);
    long double eps = 0.000000001;
    long double n = 1.0;
    long double sum = 0.0;
    long double i = 1.0;

    while (s21_fabs(n) > eps) {
        sum += n;
        n *= -1.0 * x * x / ((2.0 * i - 1.0) * (2.0 * i));
        i += 1.0;
    }

    return sum;
}

long double s21_exp(double x) {
    long double res = 0, tmpres = -1000, a = 1;
    if (x == s21_INF) {
        res = s21_INF;
    } else if (x == 0 || x == -0) {
        res = 1;
    } else if (x == (s21_INF * (-1))) {
        res = 0;
    } else {
        for (int i = 0; s21_fabs(res - tmpres) > 1e-10; i++) {
            tmpres = res;
            res += a;
            a *= x / (i + 1);
        }
    }
    return res;
}

long double s21_fabs(double x) {
    if (x < 0) {
        x = -x;
    }
    return x;
}

long double s21_floor(double x) {
    int d = x;
    if (d != x)
        if (x < 0)
            d = d - 1;
    return d;
}

long double s21_fmod(double x, double y) {
    int sym = 1;
    if (x < 0) {
        sym = -1;
    }
    if (y == 0) {
        x = s21_NAN;
    } else {
        x = s21_fabs(x);
        y = s21_fabs(y);
        while (x - y >= 0) {
            x -= y;
        }
    }
    return x * sym;
}

long double s21_log(double x) {
    long double res = 0;
    if (x == s21_INF) {
        res = x;
    } else {
        if (x == 0) {
            res = s21_INF * (-1);
        } else {
            if (x > 1) {
                int exdegree = 0;
                long double temp = 0;

                while (x >= s21_EXP) {
                    x /= s21_EXP;
                    exdegree++;
                }
                for (int i = 0; i < 100; i++) {
                    temp = res;
                    res = temp + 2 * (x - s21_exp(temp)) / (x + s21_exp(temp));
                }
                res += exdegree;
            } else {
                double z = (x - 1.0) / (x + 1.0);
                for (int i = 1; i < 12000; i += 2) {
                    res += special_pow(z, i) / i;
                }
                res *= 2.0;
            }
        }
    }
    return res;
}

long double special_pow(double num, int degree) {
    long double res = 1;
    int f = 1;
    if (degree < 0) {
        f = -f;
        degree = -degree;
    }
    if (degree == 0) {
        res = 1;
    } else {
        for (int i = 0; i < degree; i++) {
            res *= num;
        }
    }

    if (f == -1)
        res = 1.0 / res;
    return res;
}

long double s21_pow(double num, double degree) {
    long double res;
    if (degree == 0) {
        res = 1;
    } else {
        if (degree < 1 && degree > -1) {
            res = s21_exp(degree * s21_log(num));
        } else {
            res = special_pow(num, (int)degree);
            if (degree != (int)degree) {
                degree = degree - (int)degree;
                res *= s21_exp(degree * s21_log(num));
            }
        }
    }
    return res;
}

long double s21_sin(double x) {
    x = s21_fmod(x, 2.0 * s21_PI);
    long double n = x;
    long double sum = 0.0;
    long double eps = 0.000000001;
    int i = 1;

    while (s21_fabs(n) > eps) {
        sum += n;
        n *= -1.0 * x * x / ((2.0 * i) * (2.0 * i + 1.0));
        i++;
    }

    return sum;
}

long double f(long double y) {
    return y * y;
}

long double s21_sqrt(double x) {
    int n = 0;
    long double a, b, c;
    long double eps = 0.000000001;
    a = 0.0;
    b = 1.0;
    if (x > b)
        b = x;
    c = s21_NAN;
    if (x >= 0) {
        while (b - a >= eps) {
            c = (a + b) / 2.0;
            if (f(c) >= x)
                b = c;
            else if (f(c) <= x)
                a = c;
            n += 1;
        }
    }
    return c;
}

long double s21_tan(double x) {
    return s21_sin(x) / s21_cos(x);
}
