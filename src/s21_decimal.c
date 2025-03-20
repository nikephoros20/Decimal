
#include "s21_math.h"

//----------Вспомогательные функции-------------//
// Получение бита по индексу из битового массива
// bits - битовый массив, bits_size - размер массива, index - индекс бита
int s21_get_bit(s21_decimal a, int g) {
  int mask = 1 << (g % 32);
  return (a.bits[g / 32] & mask) ? 1 : 0;
}

// Установка бита по указанному индексу в битовом массиве
// bits - битовый массив, bits_size - размер массива, g - индекс бита, bit -
// значение бита (0 или 1)//
void s21_set_bit(s21_decimal *a, int g, int bit) {
  int mask = 1 << (g % 32);
  if (bit == 1)
    a->bits[g / 32] |= mask;  // Устанавливаем бит 1
  else
    a->bits[g / 32] &= ~mask;  // Устанавливаем бит 0
}

// setters and getters for bit
int s21_get_bit_big(s21_big_decimal value, int bit) {
  return (value.bits[bit / 32] >> (bit % 32)) & 1;
}

void s21_set_bit_big(s21_big_decimal *num, int bit, unsigned value) {
  if (value) {
    num->bits[bit / 32] |= (1 << (bit % 32));
  } else {
    num->bits[bit / 32] &= ~(1 << (bit % 32));
  }
}

// Устанавливат размерность в нужные биты структуры децимал
void s21_set_scale(s21_decimal *a, const int value_scale) {
  a->bits[3] &= ~(0x00ff0000);  // Зануляем значения старого скейла
  a->bits[3] |= (value_scale << 16);  // Устанавливем новое значение
}

// Показывает размерность в десятичной системе числа

int s21_get_scale(const s21_decimal a) { return (a.bits[3] >> 16) & 0x7F; }

void s21_set_scale_big(s21_big_decimal *num, unsigned value) {
  num->bits[7] &= ~(0xFF << 16);
  num->bits[7] |= (value & 0xFF) << 16;
}

int s21_get_scale_big(s21_big_decimal num) {
  return (num.bits[7] >> 16) & 0xFF;
}

// Показывает знак числа, если + то возравщает 0
int s21_get_sign(const s21_decimal a) { return ((a.bits[3] >> 31) & 1) != 0; }

// Устанавливает знак числа
// 0 - possitive, 1 - negative
void s21_set_sign(s21_decimal *a, const int sign) {
  if (sign == 1)
    a->bits[3] |= (1U << 31);
  else
    a->bits[3] &= ~(1U << 31);
}
// Установка знакового бита в битовом массиве
// bits - битовый массив, bits_size - размер массива, sign - значение знакового
// бита (0 или 1)
void s21_set_sign_big(s21_big_decimal *num, unsigned value) {
  s21_set_bit_big(num, 255, value);
}

//перевод децимала в бигдецимал
void s21_into_big_dec(s21_decimal src, s21_big_decimal *result) {
  for (int i = 0; i < 3; i++) result->bits[i] = src.bits[i];
  for (int i = 3; i < 7; i++) result->bits[i] = 0;
  result->bits[7] = src.bits[3];
}
//функция s21_to_decimal предназначена для преобразования s21_big_decimal в
// s21_decimal Проверка переполнения и масштабирования:
// s21_overflow_check(&src))
//&& s21_get_scale_big(src) Инициализация результата и копирование битов:
// s21_zanulenie_dec() Установка масштаба:
int s21_to_decimal(s21_big_decimal src, s21_decimal *result) {
  int result_code = OK;
  if ((result_code = s21_overflow_check(&src)) && s21_get_scale_big(src) > 0)
    result_code = s21_bank(&src);  // банк окргул (возвр Err при переполнении)
  if (result_code == OK) {
    *result = s21_zanulenie_dec();
    for (int i = 0; i < 3; i++) result->bits[i] = src.bits[i];
    result->bits[3] = src.bits[7];
    s21_set_scale(result, s21_get_scale_big(src));
  }
  return result_code;
}
// Функция, сдвигающая все биты в массиве влево.
int s21_shift_left_big(s21_big_decimal value, int num,
                       s21_big_decimal *result) {
  *result = s21_zanulenie_big_dec();
  for (int i = 0; i < 224 - num; i++) {
    s21_set_bit_big(result, i + num, s21_get_bit_big(value, i));
  }

  return OK;
}
//переставляет два значения местами
void s21_swap(s21_decimal *value_1, s21_decimal *value_2) {
  s21_decimal buf = *value_1;
  *value_1 = *value_2;
  *value_2 = buf;
}

void s21_copy_decimal(s21_decimal src, s21_decimal *dst) {
  for (int i = 0; i < 4; i++) {
    dst->bits[i] = src.bits[i];
  }
}
//зануление децимала
s21_decimal s21_zanulenie_dec() {
  s21_decimal result = {{0, 0, 0, 0}};
  return result;
}

s21_big_decimal s21_zanulenie_big_dec() {
  s21_big_decimal result = {{0}};
  for (size_t i = 0; i < 8; i++) result.bits[i] = 0;
  return result;
}

// проверка на переполнение
int s21_overflow_check(s21_big_decimal *value) {
  return value->bits[3] || value->bits[4] || value->bits[5] || value->bits[6];
}

void s21_div_10(s21_big_decimal *value, int *ost) {
  unsigned long long remainder = 0;
  for (int i = 6; i >= 0; --i) {
    unsigned long long current = (remainder << 32) | value->bits[i];
    value->bits[i] = current / 10;
    remainder = current % 10;
  }
  *ost = (int)remainder;
  if (s21_get_scale_big(*value) > 0)
    s21_set_scale_big(value, s21_get_scale_big(*value) - 1);
}

int s21_bank(s21_big_decimal *value) {
  int err = OK;
  int ost = 0;
  while ((s21_overflow_check(value) && s21_get_scale_big(*value) > 0) ||
         s21_get_scale_big(*value) > 28) {
    s21_div_10(value, &ost);
  }
  if (s21_overflow_check(value)) err = 1;
  if (!err && (ost > 5 || (ost == 5 && s21_get_bit_big(*value, 0)))) {
    for (int i = 0, temp = 1; i < 224; i++) {
      int result_bit = s21_get_bit_big(*value, i) + temp;
      temp = result_bit / 2;
      result_bit %= 2;
      s21_set_bit_big(value, i, result_bit);
    }
  }
  if (s21_overflow_check(value)) err = 1;
  return err;
}

int s21_compare_big(s21_big_decimal val1, s21_big_decimal val2) {
  int result_code = 0;
  for (int i = 223; i >= 0 && !result_code; i--) {
    result_code = s21_get_bit_big(val1, i) - s21_get_bit_big(val2, i);
  }
  return result_code;
}

int s21_get_length_big(s21_big_decimal value) {
  int result = 0;
  for (int i = 223; i >= 0 && !result; i--) {
    if (s21_get_bit_big(value, i)) result = i + 1;
  }
  return result;
}

void s21_add_bit(s21_big_decimal *value, int bit) {
  s21_shift_left_big(*value, 1, value);
  for (int i = 0, temp = 1; i < 224 && bit; i++) {
    int result_bit = s21_get_bit_big(*value, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(value, i, result_bit);
  }
}

void s21_delenie_stolb(s21_big_decimal value_1, s21_big_decimal value_2,
                       s21_big_decimal *result, s21_big_decimal *ost) {
  if (s21_compare_big(value_1, value_2) == -1) {
    *result = s21_zanulenie_big_dec();
    *ost = value_1;
    return;
  }
  int length = s21_get_length_big(value_1);
  int count = 0;
  int flag = 0;
  *ost = s21_zanulenie_big_dec();
  while (count < length) {
    int iterations = 0;
    for (int i = length - 1 - count;
         i >= 0 && s21_compare_big(*ost, value_2) == -1; i--) {
      s21_add_bit(ost, s21_get_bit_big(value_1, i));
      iterations++;
      if (flag && iterations > 1) s21_add_bit(result, 0);
    }
    count += iterations;
    int buf2 = s21_compare_big(*ost, value_2);
    for (int i = 0, temp = 0; i < 224 && buf2 != -1; i++) {
      int result_bit =
          s21_get_bit_big(*ost, i) - s21_get_bit_big(value_2, i) - temp;
      temp = result_bit < 0;
      if (temp) result_bit += 2;
      s21_set_bit_big(ost, i, result_bit);
    }
    s21_add_bit(result, buf2 != -1);
    flag = 1;
  }
}
// Функция нормализации двух массивов битов.
// В первом цикле инкрементируется масштаб первого массива, пока его масштаб не
// станет больше масштаба второго. Во втором цикле декрементируется масштаб
// второго массива, пока его масштаб не станет равным масштабу первого.
int s21_normalize(s21_big_decimal *v1, s21_big_decimal *v2) {
  int code = 5, scale_v1 = s21_get_scale_big(*v1),
      scale_v2 = s21_get_scale_big(*v2);

  if (scale_v1 == scale_v2) code = OK;

  if (code == 5) {
    int scale_max = scale_v1 > scale_v2 ? scale_v1 : scale_v2;

    if (s21_scale_update(v1, scale_max) || s21_scale_update(v2, scale_max)) {
      code = 1;
    } else {
      code = OK;
    }
  }
  return code;
}
// Получение степени мантиссы децимального числа из битового массива
// bits - битовый массив, bits_size - размер массива
// Установка степени мантиссы децимального числа в битовом массиве
// bits - битовый массив, bits_size - размер массива, scale - значение степени
int s21_scale_update(s21_big_decimal *src, int scale) {
  int error = OK;
  int current_scale = s21_get_scale_big(*src);
  if (scale < 0 || scale > 28) error = BIG_ETER_ERR;
  while (current_scale < scale && error == OK) {
    s21_simple_mul_10(*src, src);
    current_scale++;
  }
  s21_set_scale_big(src, current_scale);
  return error;
}
// Функция для умножения битового массива на 10 с использованием битовых сдвигов
// и простого сложения. Возвращает ошибку, если в процессе возникли проблемы.
int s21_simple_mul_10(s21_big_decimal src, s21_big_decimal *result) {
  s21_big_decimal v1 = s21_zanulenie_big_dec(), v2 = s21_zanulenie_big_dec();

  s21_shift_left_big(src, 3, &v1);  // умножение на 8
  s21_shift_left_big(src, 1, &v2);  // Умножение на 2
  for (int i = 0, temp = 0; i < 224; i++) {
    int result_bit = s21_get_bit_big(v1, i) + s21_get_bit_big(v2, i) + temp;
    temp = result_bit / 2;
    result_bit %= 2;
    s21_set_bit_big(result, i, result_bit);
  }
  return s21_overflow_check(result);
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  if (!result) return BIG_ETER_ERR;
  int sign = s21_get_sign(value);
  int flag = OK;
  int scale = s21_get_scale(value);
  if (scale < 0 || scale > 28) flag = BIG_ETER_ERR;
  if (flag == OK) {
    // получаем unsigned_value
    s21_decimal unsigned_value = s21_zanulenie_dec();
    s21_copy_decimal(value, &unsigned_value);
    s21_set_sign(&unsigned_value, 0);

    // получаем модуль truncated_unsigned_value
    s21_decimal truncated_unsigned_value = s21_zanulenie_dec();
    s21_copy_decimal(unsigned_value, &truncated_unsigned_value);

    // отбрасываем всю дробную часть
    s21_truncate(truncated_unsigned_value, &truncated_unsigned_value);

    s21_decimal fractal = s21_zanulenie_dec(),
                zero_decimal = s21_zanulenie_dec();

    // получаем дробную часть
    flag = s21_sub(unsigned_value, truncated_unsigned_value, &fractal);

    // если дробная часть больше 0 и число было отрицательным то добавляем
    // единицу
    if (flag == OK && s21_is_greater(fractal, zero_decimal) && sign == 1) {
      s21_decimal one = {{1, 0, 0, 0}};
      flag = s21_add(truncated_unsigned_value, one, &truncated_unsigned_value);
    }

    s21_set_sign(&truncated_unsigned_value, sign);

    s21_copy_decimal(truncated_unsigned_value, result);
  }

  return flag;
}

// Негация
/**
 * @brief Умножает число на -1, тем самым меняя его знак.
 *
 * @param value Десятичное число, которое нужно инвертировать.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */

int s21_negate(s21_decimal value, s21_decimal *result) {
  s21_clear_decimal(
      result);  // Сначала устанавливаем result в "нулевое" состояние
  *result = value;  // Копируем значение в result

  // Изменяем знак значения (устанавливаем/сбрасываем знак)
  // В битах 3 (старший бит) хранится знак
  if (value.bits[3] & (1 << 31)) {
    // Если знак уже отрицательный, делаем его положительным
    result->bits[3] &= ~(1 << 31);  // Сбрасываем старший бит
  } else {
    // Если знак положительный, делаем его отрицательным
    result->bits[3] |= (1 << 31);  // Устанавливаем старший бит
  }

  return OK;  // Возвращаем статус выполнения
}

//зануление всего децимала

void s21_clear_decimal(s21_decimal *result) {
  // Обнуляем все биты
  for (int i = 0; i < 4; i++) {
    result->bits[i] = 0;
  }
}

// Округление
/**
 * @brief Округляет число до ближайшего целого числа.
 *
 * @param value Десятичное число, которое нужно округлить.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */
int s21_round(s21_decimal value, s21_decimal *result) {
  if (!result) return BIG_ETER_ERR;
  int code = OK;
  unsigned int sign = s21_get_sign(value);
  if (sign) s21_set_sign(&value, 0);  // abs(value)

  s21_decimal fract = s21_zanulenie_dec(), half_of_one = {{5, 0, 0, 0}},
              one = {{1, 0, 0, 0}};
  s21_set_scale(&half_of_one, 1);
  if (s21_truncate(value, result) || s21_sub(value, *result, &fract)) {
    code = 1;
  }

  if (!code && s21_is_greater_or_equal(fract, half_of_one)) {
    s21_add(*result, one, result);
  }
  s21_set_sign(result, sign);
  return code;
}

// Отбрасывание дробной части
/**
 * @brief Удаляет дробную часть числа, оставляя только целую часть.
 *
 * @param a Десятичное число, дробная часть которого должна быть удалена.
 * @param result Указатель на переменную типа s21_decimal, где будет храниться
 * результат.
 * @return int Возвращает код ошибки.
 */
// Приведение децимала к 0 размерности

int s21_truncate(s21_decimal value, s21_decimal *result) {
  if (!result) return 1;
  int code = OK;

  // копируем память из value в result
  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }

  // объявляем временную переменную big
  s21_big_decimal temp = s21_zanulenie_big_dec();
  s21_into_big_dec(value, &temp);

  int scale = s21_get_scale_big(temp);
  if (scale < 0 || scale > 28) code = BIG_ETER_ERR;
  if (code == OK && scale > 0) {
    for (int i = 0; i < scale; ++i) {
      int ost;
      s21_div_10(&temp, &ost);
    }

    s21_set_scale_big(&temp, 0);
    code = s21_to_decimal(temp, result);
  }
  return code;
}
