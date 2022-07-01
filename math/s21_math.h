#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define s21_PRECISION 1e-6
#define s21_EXP 2.71828182845904523536
#define s21_PI 3.1415926535897932384626433832795
#define s21_NAN 0.0 / 0.0
#define s21_INF 1.0 / 0.0

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double special_pow(double num, int degree);
long double s21_pow(double a, double b);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

#endif  // SRC_S21_MATH_H_
