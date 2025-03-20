#ifndef S21_MATH_H
#define S21_MATH_H

#include "s21_decimal.h"

//--------Арифметические функции-----Ляйля---Илья----//
/*
  0 - OK
  1 - число слишком велико или равно бесконечности
  2 - число слишком мало или равно отрицательной бесконечности
  3 - деление на 0
  Ляйля
  int s21_add
  int s21_sub
  int s21_div
  Илья
  int s21_mul

*/
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

//---------------Функции сравнения----------Андрей------//
/*
  0 - FALSE
  1 - TRUE

*/
int s21_compare(s21_decimal a, s21_decimal b);

int s21_is_zero(s21_decimal value);
int s21_is_less(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

//-----------------Функции преобразования--------Илья-----//
/*
  0 - OK
  1 - ошибка конвертации

*/
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

//-----------------Другие функции----------Ильнур-------//
/*
  0 - OK
  1 - ошибка вычисления
  Ильнур
*/
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal a, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);

int s21_is_zero(s21_decimal value);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_compare_less_same_order(s21_decimal a, s21_decimal b);
int s21_less_check_remainder(int sign_a, int scale_a, int scale_b);
void s21_check_bit_zero(int sign_a, s21_decimal a, s21_decimal b, int *gg,
                        int *result);
s21_decimal get_next_number(s21_decimal a, s21_decimal b);
char *s21_extract_fraction(const char *str);
int s21_is_smaller(s21_decimal val_1, s21_decimal val_2);

#endif  // S21_MATH_H