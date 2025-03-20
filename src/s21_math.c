#include "s21_math.h"

#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

//--------Арифметические функции------------//
/*
  0 - OK
  1 - число слишком велико или равно бесконечности
  2 - число слишком мало или равно отрицательной бесконечности
  3 - деление на 0
*/
// Сложение
/**
 * @brief Суммирует два числа.
 *
 * @param value_1 Первое десятичное число.
 * @param value_2 Второе десятичное число.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  int result_code = OK;
  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    sign_1 ? s21_negate(value_1, &value_1) : s21_negate(value_2, &value_2);
    result_code = sign_1 ? s21_sub(value_2, value_1, result)
                         : s21_sub(value_1, value_2, result);
  }
  if (sign_1 == sign_2) {
    s21_big_decimal val_1 = s21_zanulenie_big_dec(),
                    val_2 = s21_zanulenie_big_dec(),
                    res = s21_zanulenie_big_dec();
    s21_into_big_dec(value_1, &val_1);
    s21_into_big_dec(value_2, &val_2);
    s21_into_big_dec(s21_zanulenie_dec(), &res);
    s21_normalize(&val_1, &val_2);
    s21_set_scale_big(&res, s21_get_scale_big(val_1));
    for (int i = 0, temp = 0; i < 224; i++) {
      unsigned result_bit =
          s21_get_bit_big(val_1, i) + s21_get_bit_big(val_2, i) + temp;
      temp = result_bit / 2;
      result_bit %= 2;
      s21_set_bit_big(&res, i, result_bit);
    }
    if (s21_to_decimal(res, result)) result_code = sign_1 ? 2 : 1;
    if (result_code == OK && sign_1) s21_negate(*result, result);
  }
  return result_code;
}

// Вычитание
/**
 * @brief Вычитает одно число из другого.
 *
 * @param value_1 Уменьшаемое.
 * @param value_2 Вычитаемое.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1), sign_2 = s21_get_sign(value_2);
  int result_code = OK;
  if ((!sign_1 && sign_2) || (sign_1 && !sign_2)) {
    s21_negate(value_2, &value_2);
    result_code = s21_add(value_1, value_2, result);
  }
  if (sign_1 == sign_2) {
    if (sign_1) {
      s21_negate(value_1, &value_1);
      s21_negate(value_2, &value_2);
      s21_swap(&value_1, &value_2);
    }
    s21_decimal c_val_1 = value_1, c_val_2 = value_2;

    int is_swap = s21_is_less(c_val_1, c_val_2);
    s21_big_decimal val_1 = s21_zanulenie_big_dec(),
                    val_2 = s21_zanulenie_big_dec(),
                    res = s21_zanulenie_big_dec();
    s21_into_big_dec(is_swap ? value_2 : value_1, &val_1);
    s21_into_big_dec(is_swap ? value_1 : value_2, &val_2);
    s21_into_big_dec(s21_zanulenie_dec(), &res);
    s21_normalize(&val_1, &val_2);
    for (int i = 0, temp = 0; i < 224; i++) {
      int result_bit =
          s21_get_bit_big(val_1, i) - s21_get_bit_big(val_2, i) - temp;
      temp = result_bit < 0;
      if (temp) result_bit += 2;
      s21_set_bit_big(&res, i, result_bit);
    }
    s21_set_scale_big(&res, s21_get_scale_big(val_1));
    s21_to_decimal(res, result);
    if (is_swap) s21_negate(*result, result);
  }
  return result_code;
}

// умножение
/**
 * @brief Умножает одно число на другое.
 *
 * @param value_1 Первый множитель.
 * @param value_2 Второй множитель.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int sign_1 = s21_get_sign(value_1);
  int sign_2 = s21_get_sign(value_2);
  int result_operation = 0;
  s21_big_decimal v1, v2, res;
  // add clear decimal mb
  s21_into_big_dec(value_1, &v1);
  s21_into_big_dec(value_2, &v2);
  s21_into_big_dec(s21_zanulenie_dec(), &res);
  for (int i = 0; i < 224; i++) {
    if (s21_get_bit_big(v2, i) == 0) {
      continue;
    }
    s21_big_decimal shifted_buf = s21_zanulenie_big_dec();
    s21_shift_left_big(v1, i, &shifted_buf);

    for (int j = 0, carry = 0; j < 224; j++) {
      int bit_from_res = s21_get_bit_big(res, j);
      int bit_from_buf = s21_get_bit_big(shifted_buf, j);
      int sum = bit_from_res + bit_from_buf + carry;

      carry = sum / 2;
      sum %= 2;
      s21_set_bit_big(&res, j, sum);
    }
  }
  s21_set_scale_big(&res, s21_get_scale_big(v1) + s21_get_scale_big(v2));
  if (s21_to_decimal(res, result)) {
    result_operation = (sign_1 != sign_2) ? 2 : 1;
  }

  if (sign_1 != sign_2 && result_operation == 0) {
    s21_negate(*result, result);
  }
  return result_operation;
}

// Функция деления
/**
 * @brief Делит одно число на другое.
 *
 * @param value_1 Делимое.
 * @param value_2 Делитель.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  if (s21_is_zero(value_2)) return DEL_TO_ZERO_ERR;
  int result_code = OK;
  s21_big_decimal val_1 = s21_zanulenie_big_dec(),
                  val_2 = s21_zanulenie_big_dec();
  s21_into_big_dec(value_1, &val_1);
  s21_into_big_dec(value_2, &val_2);
  s21_normalize(&val_1, &val_2);
  s21_big_decimal result_int = s21_zanulenie_big_dec(),
                  ost = s21_zanulenie_big_dec();
  s21_delenie_stolb(val_1, val_2, &result_int, &ost);
  s21_set_scale_big(&result_int, 0);
  s21_set_scale_big(&ost, s21_get_scale_big(val_1));
  s21_big_decimal result_frac = s21_zanulenie_big_dec(),
                  result_big = s21_zanulenie_big_dec();
  if (s21_compare_big(ost, s21_zanulenie_big_dec())) {
    for (int i = 0; i < 28; i++) s21_simple_mul_10(ost, &ost);
    s21_delenie_stolb(ost, val_2, &result_frac, &val_1);
    s21_set_scale_big(&result_frac, 28);
    s21_set_scale_big(&result_big, 28);
  }
  s21_normalize(&result_int, &result_frac);
  for (int i = 0, temp = 0; i < 224; i++) {
    int result_bit =
        s21_get_bit_big(result_int, i) + s21_get_bit_big(result_frac, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(&result_big, i, result_bit);
  }
  *result = s21_zanulenie_dec();
  s21_set_sign_big(&result_big, s21_get_sign(value_1) ^ s21_get_sign(value_2));
  if (s21_to_decimal(result_big, result))
    result_code = s21_get_sign(*result) ? 2 : 1;
  return result_code;
}

// операторы сравнения
int s21_compare(s21_decimal val_1, s21_decimal val_2) {
  int flag = 5;
  int sign_val_1 = s21_get_sign(val_1);
  int sign_val_2 = s21_get_sign(val_2);

  // Обработка случая +0 и -0
  if (s21_is_zero(val_1) && s21_is_zero(val_2)) {
    flag = 0;
  }

  if (flag == 5 && sign_val_1 != sign_val_2) {
    flag = sign_val_1 ? -1 : 1;
  }

  if (flag == 5) {
    s21_big_decimal big_val1, big_val2;
    s21_into_big_dec(val_1, &big_val1);
    s21_into_big_dec(val_2, &big_val2);

    s21_normalize(&big_val1, &big_val2);

    // Сравнение битов от старшего к младшему, исключая бит знака
    flag = s21_compare_big(big_val1, big_val2);

    // Сравнение старшего слова без учета бита знака
    int value_1 = big_val1.bits[7] & 0x7FFFFFFF;
    int value_2 = big_val2.bits[7] & 0x7FFFFFFF;
    if (flag == 5 && (unsigned)value_1 > (unsigned)value_2) flag = 1;
    if (flag == 5 && (unsigned)value_1 < (unsigned)value_2) flag = -1;
    if (flag == 5) flag = OK;
  }
  if (sign_val_1 && sign_val_2 && flag != 0) flag *= -1;
  return flag;
}

int s21_is_zero(s21_decimal value) {
  return value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0;
}

int s21_is_less(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) == -1;
}

int s21_is_less_or_equal(s21_decimal val_1, s21_decimal val_2) {
  int cmp = s21_compare(val_1, val_2);
  return cmp == -1 || cmp == 0;
}

int s21_is_greater(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) == 1;
}

int s21_is_greater_or_equal(s21_decimal val_1, s21_decimal val_2) {
  int cmp = s21_compare(val_1, val_2);
  return cmp == 1 || cmp == 0;
}

int s21_is_equal(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) == 0;
}

int s21_is_not_equal(s21_decimal val_1, s21_decimal val_2) {
  return s21_compare(val_1, val_2) != 0;
}
//-----------------Функции преобразования-------------//
/*
  0 - OK
  1 - ошибка конвертации
*/
// Из int
/**
 * @brief Конвертирует int в s21_decimal
 *
 * @param src Целое число для конвертации.
 * @param dst Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */
//#include "s21_converters.h"
/*void s21_clear_decimal(s21_decimal *dec) {
  for (int i = 0; i < 4; i++) {
    dec->bits[i] = 0;
  }
}*/

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (!dst) return 1;

  s21_clear_decimal(dst);

  if (src < 0) {
    s21_set_sign(dst, 1);
  }
  dst->bits[0] = abs(src);
  return OK;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int code = OK;
  int overflow = 0;
  if (src.bits[1] != 0 || src.bits[2] != 0 || (!dst)) {
    code = 1;
    return code;
  }
  if (s21_get_scale(src) > 0) {
    s21_truncate(src, &src);
  }
  if ((s21_get_bit(src, 31) == 1)) {
    overflow = 1;
    code = 1;

    if (src.bits[0] == INT_MIN && (s21_get_sign(src) == 1)) {
      *dst = INT_MIN;
      code = OK;
    }
  }
  if (overflow == 0) {
    int sign_bit = s21_get_bit(src, 127);
    *dst = src.bits[0];
    if (sign_bit == 1) {
      *dst = -(*dst);
    }
  }
  return code;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return 1;

  double temp_result = 0.0;

  for (int i = 0; i < 96; i++) {
    if (src.bits[i / 32] & (1u << (i % 32))) {
      temp_result += pow(2, i);
    }
  }

  int scale = s21_get_scale(src);
  for (int i = 0; i < scale; i++) {
    temp_result /= 10.0;
  }

  *dst = (float)temp_result;
  if (s21_get_sign(src) == 1) {
    *dst = -(*dst);
  }

  return OK;
}

void s21_extract_parts(float src, int *int_p, int *fraction, int *exponent,
                       int f_n) {
  int flag = 0;
  char tmp[50] = {0};
  sprintf(tmp, "%.6E", src);
  char tmp_two[50] = {0};
  memcpy(tmp_two, tmp, strlen(tmp));
  *int_p = atoi(strtok(tmp, "."));
  *int_p = abs(*int_p);
  char *exp_sign = strchr(tmp_two, 'E');
  char ch_exponent[50] = {0};
  if (exp_sign != NULL) {
    strcpy(ch_exponent, exp_sign + 2);
    *exponent = atoi(ch_exponent);
    if (f_n == 1) {
      *exponent *= -1;
    }
    char *start = strchr(tmp_two, '.');
    char *end = strchr(tmp_two, 'E');
    size_t length = end - start - 1;
    char substr[50] = {0};
    if (flag == 0) {
      memcpy(substr, start + 1, length);
      *fraction = atoi(substr);
    }
  }
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int return_code = OK;
  int sign = 0;
  int f_n = 0;
  if (!dst || isinf(src) || isnan(src) || fabsf(src) > MAX_FLOAT_TO_CONVERT) {
    return_code = 1;
    return return_code;
  }
  s21_clear_decimal(dst);
  if (fabsf(src) < MIN_FLOAT_TO_CONVERT && fabsf(src) > 0) {
    return_code = 1;
  }
  if (return_code == OK) {
    if (src < 0.0f || (src == 0.0f && 1.0f / src == -INFINITY)) {
      sign = 1;
    }
    if (fabsf(src) > 0 && fabsf(src) < 1) {
      f_n = 1;
    }
    int int_p = 0;
    int fraction = 0;
    int exponent = 0;
    s21_extract_parts(src, &int_p, &fraction, &exponent, f_n);
    int_p = int_p * 1000000 + fraction;
    if (int_p != 0) {
      exponent -= 6;
    }
    while (int_p % 10 == 0 && int_p != 0) {
      int_p /= 10;
      exponent++;
    }
    int remainder = 0;
    while (exponent < -28) {
      remainder = int_p % 10;
      int_p /= 10;
      exponent++;
    }
    if (remainder >= 5) {
      int_p = int_p + 1;
    }
    s21_from_int_to_decimal(int_p, dst);
    s21_decimal dix = {{10, 0, 0, 0}};
    while (exponent > 0) {
      s21_mul(*dst, dix, dst);
      exponent--;
    }
    exponent *= -1;
    s21_set_scale(dst, (unsigned int)exponent);
    if (sign) s21_set_sign(dst, 1);
  }
  return return_code;
}
