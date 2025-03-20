#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Sign
#define S21_SIGN_PLUS 0
#define S21_SIGN_MINUS 1

// float
#define S21_MIN_DECIMAL \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f
#define S21_MAX_DECIMAL 79228162514264337593543950335.0f
#define MAX_FLOAT_TO_CONVERT 79228162514264337593543950335.0f
#define MIN_FLOAT_TO_CONVERT 0.0000000000000000000000000001
// Decimal struct
#define S21_DEC_BITS_CNT 3
#define S21_DEC_ARR_CNT 4

typedef struct s21_decimal {
  int bits[4];
} s21_decimal;

typedef struct s21_big_decimal {
  unsigned bits[8];
} s21_big_decimal;

typedef enum returnValue {
  OK = 0,
  BIG_ETER_ERR = 1,
  SMALL_ETER_ERR = 2,
  DEL_TO_ZERO_ERR = 3,
} returnValue;

//----------Вспомогательные функции-------------//

void s21_into_big_dec(s21_decimal src, s21_big_decimal *result);

// Возвращает 1 если overflow, иначе 0
int s21_to_decimal(s21_big_decimal src, s21_decimal *result);

/******** setters and getters for scale ********/
void s21_set_scale(s21_decimal *a, const int value_scale);
void s21_set_scale_big(s21_big_decimal *num, unsigned value);
int s21_get_scale(const s21_decimal a);
int s21_get_scale_big(s21_big_decimal num);

/******** setters and getters for sign ********/
int s21_get_sign(const s21_decimal a);
void s21_set_sign(s21_decimal *a, const int sign);
void s21_set_sign_big(s21_big_decimal *num, unsigned value);

/******** setters and getters for bit ********/
int s21_get_bit_big(s21_big_decimal value, int bit);
int s21_get_bit(s21_decimal a, int g);
void s21_set_bit(s21_decimal *a, int g, int bit);
void s21_set_bit_big(s21_big_decimal *num, int bit, unsigned value);

/******** manipulations with decimal ********/

int s21_shift_left_big(s21_big_decimal value, int num, s21_big_decimal *result);
void s21_swap(s21_decimal *value_1, s21_decimal *value_2);
void s21_copy_decimal(s21_decimal src, s21_decimal *dst);

/********  normalization ********/

// нормализует два decimal числа, возвращает 1 в случае overflow, 0 в случае
// успеха
int s21_normalize(s21_big_decimal *v1, s21_big_decimal *v2);

// return 1 if any errors, else return 0

// возвращает 1 в случае если src не умещается в decimal
int s21_scale_update(s21_big_decimal *src, int scale);

// возвращает 1 в случае если result не умещается в decimal
int s21_simple_mul_10(s21_big_decimal src, s21_big_decimal *result);

/******** debug ********/
// void print_big_decimal(s21_big_decimal value);
// void print_decimal(s21_decimal value);

/******** others ********/
// Возвращает 1 если big_decimal не умещается в decimal, 0 если иначе
int s21_overflow_check(s21_big_decimal *value);

s21_decimal s21_zanulenie_dec();
s21_big_decimal s21_zanulenie_big_dec();

/******** Banking rounding ********/

// банковское огругление к ближайшему четному числу, возвращает 1 в случае
// overflow
int s21_bank(s21_big_decimal *value);

void s21_div_10(s21_big_decimal *value, int *ost);

/// Функции для деления
int s21_compare_big(s21_big_decimal val1, s21_big_decimal val2);
int s21_get_length_big(s21_big_decimal value);
void s21_add_bit(s21_big_decimal *value, int bit);
void s21_delenie_stolb(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result, s21_big_decimal *ost);

int s21_floor(s21_decimal value, s21_decimal *result);

// Округляет Decimal до ближайшего целого числа.
// 11,9 -> 12; −0,9 -> −1; −1,1 -> −1; 2,5 -> 3
// Возвращает 1 в случае overflow
int s21_round(s21_decimal value, s21_decimal *result);

// Записывает в result целые цифры указанного Decimal числа; любые дробные цифры
// отбрасываются, включая конечные нули. Возвращает 1 в случае overflow
int s21_truncate(s21_decimal a, s21_decimal *result);

// Возвращает результат умножения указанного Decimal на -1.
int s21_negate(s21_decimal value, s21_decimal *result);

void s21_clear_decimal(s21_decimal *result);
#endif  // S21_DECIMAL_H

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);