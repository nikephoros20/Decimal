#include <check.h>

#include "s21_decimal.h"
#include "s21_math.h"

START_TEST(add_test_1) {
  float value_1 = 122e-2, value_2 = 12e-2, result = 0, expected = 134e-2;
  s21_decimal value_1_decimal = s21_zanulenie_dec(),
              value_2_decimal = s21_zanulenie_dec(),
              value_3_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_add(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(add_test_2) {
  float result = 0, expected = 1.32;

  // d_1 = 1.2, d_2 = 0.12
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{12, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 2);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_add(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(add_test_3) {
  float result = 0, expected = 1.0;

  // d_1 = 1.2, d_2 = 0.12
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{2, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 1);
  s21_set_sign(&d_2, 1);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_add(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(s21_div_3) {
  s21_decimal src1, src2, result;
  int a = 32768;
  int b = 2;
  int res_our_dec = 0;
  s21_from_int_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  int res_origin = 16384;
  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  s21_from_decimal_to_int(result, &res_our_dec);
  ck_assert_int_eq(res_our_dec, res_origin);
  ck_assert_int_eq(check, check_origin);
}
END_TEST

// 1.22 * 0.12 = 0.1464
START_TEST(mul_test_1) {
  float value_1 = 122e-2f, value_2 = 12e-2f, result = 0.0f, expected = 1464e-4f;
  s21_decimal value_1_decimal = s21_zanulenie_dec(),
              value_2_decimal = s21_zanulenie_dec(),
              value_3_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_mul(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -1.22 * 0.105 = -0.1281
START_TEST(mul_test_2) {
  float result = 0.0f, expected = -1281e-4f;

  s21_decimal d_1 = {{122, 0, 0, 0}}, d_2 = {{105, 0, 0, 0}};
  s21_set_scale(&d_1, 2);
  s21_set_scale(&d_2, 3);

  s21_set_sign(&d_1, 1);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.105 * -1.22 = 0.1281
START_TEST(mul_test_3) {
  float result = 0.0f, expected = 1281e-4f;

  s21_decimal d_1 = {{105, 0, 0, 0}}, d_2 = {{122, 0, 0, 0}};
  s21_set_scale(&d_1, 3);
  s21_set_scale(&d_2, 2);

  s21_set_sign(&d_2, 1);
  s21_set_sign(&d_1, 1);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.15 * -1.22 = 0.183
START_TEST(mul_test_4) {
  float result = 0.0f, expected = 183e-3f;

  s21_decimal d_1 = {{15, 0, 0, 0}}, d_2 = {{122, 0, 0, 0}};
  s21_set_scale(&d_1, 2);
  s21_set_scale(&d_2, 2);

  s21_set_sign(&d_1, 1);
  s21_set_sign(&d_2, 1);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.15 * -1.22 = 0.183
START_TEST(mul_test_5) {
  float v_1 = -0.15f, v_2 = -1.22f, result = 0.0f, expected = 183e-3f;

  s21_decimal d_1 = s21_zanulenie_dec(), d_2 = s21_zanulenie_dec();
  s21_from_float_to_decimal(v_1, &d_1);
  s21_from_float_to_decimal(v_2, &d_2);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_mul(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

START_TEST(mul_test_6) {
  // 0.9999999999999999999999999999
  s21_decimal decimal1 = {{0xFFFFFFF, 0x3E250261, 0x204FCE5E, 0x1C0000}};
  // 0.0000000000000025
  s21_decimal decimal2 = {{0x19, 0x0, 0x0, 0x100000}};
  // 0.0000000000000025000000000000
  //  s21_decimal decimal_check = {{0xC41E9000, 0x16BC, 0x0, 0x1C0000}};

  s21_decimal res = {0};

  int code = s21_mul(decimal1, decimal2, &res);

  //  s21_print_decimal(decimal_check);
  //  s21_print_decimal(res);
  ck_assert_int_eq(code, OK);
}
END_TEST

// 11,9 -> 12
START_TEST(round_test_1) {
  s21_decimal value = {{119, 0, 0, 0}}, result = s21_zanulenie_dec(),
              expected = {{12, 0, 0, 0}};
  s21_set_scale(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_equal(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// −0,9 -> −1
START_TEST(round_test_2) {
  s21_decimal value = {{9, 0, 0, 0}}, result = s21_zanulenie_dec(),
              expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);

  s21_set_scale(&value, 1);
  s21_set_sign(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_equal(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// −1,1 -> −1;
START_TEST(round_test_3) {
  s21_decimal value = {{11, 0, 0, 0}}, result = s21_zanulenie_dec(),
              expected = {{1, 0, 0, 0}};
  s21_set_sign(&expected, 1);

  s21_set_scale(&value, 1);
  s21_set_sign(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_equal(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// 2,5 -> 3
START_TEST(round_test_4) {
  s21_decimal value = {{25, 0, 0, 0}}, result = s21_zanulenie_dec(),
              expected = {{3, 0, 0, 0}};

  s21_set_scale(&value, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_equal(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// -2,49999 -> -2
START_TEST(round_test_5) {
  s21_decimal value = {{249999, 0, 0, 0}}, result = s21_zanulenie_dec(),
              expected = {{2, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 5);

  s21_set_sign(&expected, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_equal(result, expected);

  ck_assert_int_eq(is_eq, 1);
}
END_TEST

// result = -2 != expected = -2
START_TEST(round_test_6) {
  s21_decimal value = {{249999, 0, 0, 0}}, result = s21_zanulenie_dec(),
              expected = {{3, 0, 0, 0}};

  s21_set_sign(&value, 1);
  s21_set_scale(&value, 5);

  s21_set_sign(&expected, 1);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, OK);

  int is_eq = s21_is_equal(result, expected);

  ck_assert_int_ne(is_eq, 1);
}
END_TEST

START_TEST(round_test_7) {
  s21_decimal value = {{-1, -1, -1, 0}}, result = s21_zanulenie_dec();

  s21_set_scale(&value, 30);

  int code = s21_round(value, &result);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(s21_div_11) {
  s21_decimal src1, src2, result;
  src1.bits[0] = 0x0006BFD0;
  src1.bits[1] = 0x00000000;
  src1.bits[2] = 0x00000000;
  src1.bits[3] = 0x00000000;

  src2.bits[0] = 0x00000028;
  src2.bits[1] = 0x00000000;
  src2.bits[2] = 0x00000000;
  src2.bits[3] = 0x00000000;

  int check = s21_div(src1, src2, &result);
  int check_origin = 0;
  ck_assert_int_eq(check_origin, check);
  ck_assert_int_eq(result.bits[3], 0x00000000);
  ck_assert_int_eq(result.bits[2], 0x00000000);
  ck_assert_int_eq(result.bits[1], 0x00000000);
  ck_assert_int_eq(result.bits[0], 0x00002B32);
}
END_TEST

START_TEST(test_s21_is_equal_1) {
  s21_decimal a = {{0}}, b = {{0}};
  // -3.14
  a.bits[0] = 0x0000013A;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x80020000;
  // -3.14
  b.bits[0] = 0x0000013A;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal a = {{0}}, b = {{0}};
  // 8888.888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00030000;
  // 8888.88
  b.bits[0] = 0x000D9038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal a = {{0}}, b = {{0}};
  // 111222333
  a.bits[0] = 0x06A11E3D;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // -111222333
  b.bits[0] = 0x06A11E3D;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80000000;

  ck_assert_int_eq(s21_is_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x00000000;

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x00000000;
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal a = {{0}}, b = {{0}};
  ck_assert_int_eq(s21_is_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_1) {
  s21_decimal a = {{0}}, b = {{0}};
  // 56
  a.bits[0] = 0x00000038;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 57
  b.bits[0] = 0x00000039;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal a = {{0}}, b = {{0}};
  // 57
  a.bits[0] = 0x00000039;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 57
  b.bits[0] = 0x00000039;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal a = {{0}}, b = {{0}};
  // 57
  a.bits[0] = 0x00000039;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 56
  b.bits[0] = 0x00000038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal a = {{0}}, b = {{0}};
  // 10.0
  a.bits[0] = 0x00000064;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00010000;
  // 88.88888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00050000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFF0FFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x00090000;

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x00090000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x80000000;

  b.bits[0] = 0x11111122;
  b.bits[1] = 0x11111111;
  b.bits[2] = 0x11111111;
  b.bits[3] = 0x801A0000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 234;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0x80040000;

  b.bits[0] = 234;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0x801A0000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_8) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 1;
  a.bits[1] = 0;
  a.bits[2] = 0;
  a.bits[3] = 0x00050000;

  b.bits[0] = 1;
  b.bits[1] = 0;
  b.bits[2] = 0;
  b.bits[3] = 0x001A0000;

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_9) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 0x11111122;
  a.bits[1] = 0x11111111;
  a.bits[2] = 0x11111111;
  a.bits[3] = 0x80000000;

  b.bits[0] = 0x11111122;
  b.bits[1] = 0x11111111;
  b.bits[2] = 0x11111111;
  b.bits[3] = 0x801A0000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_10) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 57000;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00040000;
  // 8888.888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80030000;

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_11) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 570001;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x80030000;
  // 8888.888
  b.bits[0] = 570002;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80030000;

  ck_assert_int_eq(s21_is_less(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_12) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 123456789;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00040000;

  b.bits[0] = 12345679;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00030000;

  ck_assert_int_eq(s21_is_less(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal a = {{0}}, b = {{0}};
  // 57
  a.bits[0] = 0x00000039;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 56
  b.bits[0] = 0x00000038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal a = {{0}}, b = {{0}};
  // -1112223334445556667
  b.bits[0] = 0xD88723BB;
  b.bits[1] = 0x0F6F693A;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80000000;
  // 1112223334445556667
  b.bits[0] = 0xD88723BB;
  b.bits[1] = 0x0F6F693A;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal a = {{0}}, b = {{0}};
  // 56
  a.bits[0] = 0x00000038;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 57
  b.bits[0] = 0x00000039;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal a = {{0}}, b = {{0}};
  // 57
  a.bits[0] = 0x00000039;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 57
  b.bits[0] = 0x00000039;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_1) {
  s21_decimal a = {{0}}, b = {{0}};
  // 8888.888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00030000;
  // 8888.88
  b.bits[0] = 0x000D9038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal a = {{0}}, b = {{0}};
  // 79,228,162,514,264,337,593,543,950,335
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x00000000;
  // 79,228,162,514,264,337,593,543,950,334
  b.bits[0] = 0xFFFFFFFE;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal a = {{0}}, b = {{0}};
  // 8888.888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00030000;
  // 8888.88
  b.bits[0] = 0x000D9038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal a = {{0}}, b = {{0}};
  // -8888.888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x80030000;
  // -8888.888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80030000;

  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_greater_5) {
  s21_decimal a = {{0}}, b = {{0}};
  // 88.88888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00050000;
  // 10.0
  b.bits[0] = 0x00000064;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00010000;

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_6) {
  s21_decimal a = {{0}}, b = {{0}};
  // 88.88888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00050000;
  // 100
  b.bits[0] = 0x00000064;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_greater_7) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0x0FFFFFFF;
  a.bits[3] = 0x00020000;

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x00080000;

  ck_assert_int_eq(s21_is_greater(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_8) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x00090000;

  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x00030000;

  ck_assert_int_eq(s21_is_greater(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal a = {{0}}, b = {{0}};
  // -8888.888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x80030000;
  // -8888.88
  b.bits[0] = 0x000D9038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal a = {{0}}, b = {{0}};
  // -8888.888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80030000;
  // -8888.88
  a.bits[0] = 0x000D9038;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x80020000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal a = {{0}}, b = {{0}};
  // 57
  a.bits[0] = 0x00000039;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 56
  b.bits[0] = 0x00000038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal a = {{0}}, b = {{0}};
  // 8888.888
  a.bits[0] = 0x0087A238;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00030000;
  // 8888.88
  b.bits[0] = 0x000D9038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00020000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal a = {{0}}, b = {{0}};
  // 8888.88
  a.bits[0] = 0x000D9038;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00020000;
  // 8888.888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00030000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_6) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 570;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x80020000;
  // 8888.888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80030000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_7) {
  s21_decimal a = {{0}}, b = {{0}};
  a.bits[0] = 570001;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00040000;
  // 8888.888
  b.bits[0] = 0x0087A238;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x80030000;

  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_1) {
  s21_decimal a = {{0}}, b = {{0}};
  // 57
  a.bits[0] = 0x00000039;
  a.bits[1] = 0x00000000;
  a.bits[2] = 0x00000000;
  a.bits[3] = 0x00000000;
  // 56
  b.bits[0] = 0x00000038;
  b.bits[1] = 0x00000000;
  b.bits[2] = 0x00000000;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal a = {{0}}, b = {{0}};
  // 79,228,162,514,264,337,593,543,950,335
  a.bits[0] = 0xFFFFFFFF;
  a.bits[1] = 0xFFFFFFFF;
  a.bits[2] = 0xFFFFFFFF;
  a.bits[3] = 0x00000000;
  // 79,228,162,514,264,337,593,543,950,335
  b.bits[0] = 0xFFFFFFFF;
  b.bits[1] = 0xFFFFFFFF;
  b.bits[2] = 0xFFFFFFFF;
  b.bits[3] = 0x00000000;

  ck_assert_int_eq(s21_is_not_equal(a, b), 0);
}
END_TEST

START_TEST(manual_div_1) {
  // scale 0
  // 10 / 0 = ERROR 3
  s21_decimal dec_1 = {{0xa, 0x0, 0x0, 0x0}};
  s21_decimal dec_2 = {{0x0, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  int res = s21_div(dec_1, dec_2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(manual_div_5) {
  // scale 0
  // (-10) / 5 = -2
  s21_decimal dec_1 = {{0xa, 0x0, 0x0, 0x80000000}};
  s21_decimal dec_2 = {{0x5, 0x0, 0x0, 0x0}};
  s21_decimal result = {{0}};
  int res = s21_div(dec_1, dec_2, &result);
  s21_decimal answer = {{0x2, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(answer.bits[0], result.bits[0]);
  ck_assert_int_eq(answer.bits[1], result.bits[1]);
  ck_assert_int_eq(answer.bits[2], result.bits[2]);
  ck_assert_int_eq(answer.bits[3], result.bits[3]);
}
END_TEST

START_TEST(manual_div_6) {
  // scale 0
  // 10 / (-5) = -2
  s21_decimal dec_1 = {{0xa, 0x0, 0x0, 0}};
  s21_decimal dec_2 = {{0x5, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {{0}};
  int res = s21_div(dec_1, dec_2, &result);
  s21_decimal answer = {{0x2, 0x0, 0x0, 0x80000000}};
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(answer.bits[0], result.bits[0]);
  ck_assert_int_eq(answer.bits[1], result.bits[1]);
  ck_assert_int_eq(answer.bits[2], result.bits[2]);
  ck_assert_int_eq(answer.bits[3], result.bits[3]);
}
END_TEST

START_TEST(manual_div_7) {
  // scale 0
  // (-10) / (-5) = 2
  s21_decimal dec_1 = {{0xa, 0x0, 0x0, 0x80000000}};
  s21_decimal dec_2 = {{0x5, 0x0, 0x0, 0x80000000}};
  s21_decimal result = {{0}};
  int res = s21_div(dec_1, dec_2, &result);
  s21_decimal answer = {{0x2, 0x0, 0x0, 0}};
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(answer.bits[0], result.bits[0]);
  ck_assert_int_eq(answer.bits[1], result.bits[1]);
  ck_assert_int_eq(answer.bits[2], result.bits[2]);
  ck_assert_int_eq(answer.bits[3], result.bits[3]);
}
END_TEST

START_TEST(dtof_test_1) {
  int code, rnd = rand();
  s21_decimal test = {{rnd, 0, 0, 0}};
  float tolerance = rnd * 0.01;
  for (int j = 0; j < 100; j++) {
    rnd = rand();
    test.bits[0] = rnd;
    for (int i = 0; i < 29; i++) {
      s21_set_scale(&test, i);
      float test_float = (float)rnd / pow(10, i);
      float result_float = 0.0;
      code = s21_from_decimal_to_float(test, &result_float);
      ck_assert_float_eq_tol(test_float, result_float, tolerance);
      ck_assert_int_eq(code, OK);
    }
  }
}
END_TEST

// MAX DEC -> Float
START_TEST(dtof_test_2) {
  s21_decimal test = {{-1, -1, -1, 0}};
  float check_res = 79228162514264337593543950335.0f;
  float result_float = 0.0;
  int code;
  code = s21_from_decimal_to_float(test, &result_float);
  ck_assert_float_eq(check_res, result_float);
  ck_assert_int_eq(code, OK);
}
END_TEST

START_TEST(dtof_test_3) {
  // -1012308.0780731047111141553152
  s21_decimal decimal = {{0x6F5AF400, 0xBC59A53E, 0x20B59DBC, 0x80160000}};
  float check_res = -1012308.0f;

  float result_float = 0.0;
  int code;
  code = s21_from_decimal_to_float(decimal, &result_float);

  ck_assert_float_eq_tol(check_res, result_float, 0.1);
  ck_assert_int_eq(code, OK);

  //  test_from_decimal_to_float(decimal, check);
}

// conversion with sign flip
START_TEST(dtoi_test_1) {
  int y = 0, code = 3, rnd = rand();
  s21_decimal test = {{rnd, 0, 0, 0}};

  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq(rnd, y);
  ck_assert_int_eq(code, 0);

  test.bits[3] |= (1u << 31);
  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq((rnd * -1), y);
  ck_assert_int_eq(code, 0);
}
END_TEST

// incorrect conversion with overflow
START_TEST(dtoi_test_2) {
  int y = 0;
  int rnd = rand();
  s21_decimal test = {{rnd, rnd, 0, 0}};
  int code = s21_from_decimal_to_int(test, &y);

  // код ошибки должен быть 1
  ck_assert_int_eq(code, 1);

  // переменная для записи должна остаться неизменной
  ck_assert_int_eq(0, y);
}
END_TEST

// conversion with truncate decimal part after dot
START_TEST(dtoi_test_3) {
  int scale = 2, y = 0, z = 128;

  s21_decimal test = {
      {z, 0, 0,
       0}};  // z = 128, scale = 2, float value from decimal = 128 / 10^2 = 1.28
  s21_set_scale(&test, scale);

  int code = s21_from_decimal_to_int(test, &y);  // 1.28 to int = 1

  // код ошибки должен быть 0
  ck_assert_int_eq(code, 0);

  // переменная для записи должна остаться неизменной
  ck_assert_int_eq(1, y);
}
END_TEST

// conversion with truncate decimal part after dot
START_TEST(dtoi_test_4) {
  int scale = 1 + (int)(28.0 * rand() / (RAND_MAX + 1.0));
  int y = 0;
  int rnd = rand();
  int expected = (int)(rnd / (pow(10, scale)));  // (int) (rnd / 10^scale)
  s21_decimal test = {{rnd, 0, 0, 0}};
  s21_set_scale(&test, scale);

  int code = s21_from_decimal_to_int(test, &y);

  // код ошибки должен быть 0
  ck_assert_int_eq(code, 0);

  // переменная для записи должна остаться неизменной
  ck_assert_int_eq(expected, y);
}
END_TEST

START_TEST(dtoi_test_5) {
  int y = 0, code = 3, rnd = 1u << 31;
  s21_decimal test = {{rnd, 0, 0, 1u << 31}};

  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq(rnd, y);
  ck_assert_int_eq(code, 0);

  test.bits[3] |= (1u << 31);
  code = s21_from_decimal_to_int(test, &y);
  ck_assert_int_eq((rnd * -1), y);
  ck_assert_int_eq(code, 0);
}
END_TEST

// START_TEST(dtoi_test_6) {
//   float y = 875.45612345;
//   int answer;
//   s21_decimal test = {{0, 0, 0, 0}};
//   s21_from_float_to_decimal(y, &test);
//   int code = s21_from_decimal_to_int(test, &answer);
//   printf("%d", answer);
//   ck_assert_int_eq(code, 0);
//   ck_assert_int_eq(875, answer);
// }
// END_TEST

// START_TEST(ftod_test_1) {
//   s21_decimal result_decimal = {{0, 0, 0, 0}};
//   float result = 0.;
//   float expected = -1.234567;
//   float tolerance = 0.001;
//   int code =
//       s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
//   ck_assert_int_eq(OK, code);

//   code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
//   ck_assert_int_eq(OK, code);

//   ck_assert_float_eq_tol(result, expected, tolerance);
// }
// END_TEST

// START_TEST(ftod_test_2) {
//   s21_decimal result_decimal = {{0, 0, 0, 0}};
//   float result = 0.;
//   float expected = 1.234567;
//   float tolerance = 0.001;
//   int code =
//       s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
//   ck_assert_int_eq(OK, code);

//   code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
//   ck_assert_int_eq(OK, code);

//   ck_assert_float_eq_tol(result, expected, tolerance);
// }
// END_TEST

// START_TEST(ftod_test_3) {
//   s21_decimal result_decimal = {{0, 0, 0, 0}};
//   float result = 0.;
//   float expected = 1.2345678;  // 7 значимых цифр после точки
//   float tolerance = 0.001;
//   int code =
//       s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
//   ck_assert_int_eq(OK, code);

//   code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
//   ck_assert_int_eq(OK, code);

//   ck_assert_float_eq_tol(result, expected, tolerance);
// }
// END_TEST

// START_TEST(ftod_test_4) {
//   s21_decimal result_decimal = {{0, 0, 0, 0}};
//   float result = 0.;
//   float expected = -1.2345678;  // 7 значимых цифр после точки
//   float tolerance = 0.001;
//   int code =
//       s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
//   ck_assert_int_eq(OK, code);

//   code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
//   ck_assert_int_eq(OK, code);

//   ck_assert_float_eq_tol(result, expected, tolerance);
// }
// END_TEST

// START_TEST(ftod_test_5) {
//   s21_decimal result_decimal = {{0, 0, 0, 0}};
//   float result = 0.;
//   float expected = -12345678.0;  // 7 значимых цифр после точки
//   float tolerance = 10;
//   int code =
//       s21_from_float_to_decimal(expected, &result_decimal);  // val = temp
//   ck_assert_int_eq(OK, code);

//   code = s21_from_decimal_to_float(result_decimal, &result);  // val -> res
//   ck_assert_int_eq(OK, code);

//   ck_assert_float_eq_tol(result, expected, tolerance);
// }
// END_TEST

// START_TEST(ftod_test_6) {
//   float f = 1234567890123456789012345678.0;
//   s21_decimal result_decimal = {{0x5000000, 0x62516078, 0x3FD35F1, 0x0}};
//   s21_decimal result = {{0, 0, 0, 0}};
//   s21_from_float_to_decimal(f, &result);  // val -> res
//   for (int i = 0; i < 4; i++)
//     ck_assert_int_eq(result_decimal.bits[i], result.bits[i]);
// }

START_TEST(ftod_test_7) {
  float f = 989989898989898989898989898989898989898.9;
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &result);  // f -> res
  ck_assert_int_eq(code, BIG_ETER_ERR);
}

START_TEST(ftod_test_8) {
  float f = 9899898989898989898989898989898989.9f;
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &result);  // f -> res
  ck_assert_int_eq(code, BIG_ETER_ERR);
}

START_TEST(ftod_test_unnormal1) {
  float f = 0.0;
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(ftod_test_unnormal2) {
  float f = -0.0;
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x80000000}};

  int code = s21_from_float_to_decimal(f, &result);

  int sign_check = s21_get_sign(check);
  int sign_result = s21_get_sign(result);

  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
  ck_assert_int_eq(sign_check, sign_result);
}
END_TEST

START_TEST(ftod_test_unnormal3) {
  float f = INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal4) {
  float f = -INFINITY;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal5) {
  float f = NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

START_TEST(ftod_test_unnormal6) {
  float f = -NAN;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

/*START_TEST(ftod_test_unnormal7) {
  float f = -1.91731719E-25;
  s21_decimal result;

  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST*/

START_TEST(itod_test_1) {
  int x = rand();
  s21_decimal expected = {{x, 0, 0, 0}};
  s21_decimal result = s21_zanulenie_dec();

  s21_from_int_to_decimal(x, &result);

  ck_assert_int_eq(expected.bits[0], result.bits[0]);
}
END_TEST

// conversion with negative integer
/*START_TEST(itod_test_2) {
  int x = rand();
  s21_decimal expected = {{x, 0, 0, 0}};
  expected.bits[3] |= (1u << 31);

  s21_decimal result = s21_zanulenie_dec();

  s21_from_int_to_decimal(x * -1, &result);

  ck_assert_int_eq(expected.bits[0], result.bits[0]);
  ck_assert_int_eq(expected.bits[3], result.bits[3]);
}
END_TEST*/

START_TEST(test_s21_is_zero_non_zero) {
  s21_decimal decimal = {.bits = {1, 0, 0, 0}};
  ck_assert_int_eq(s21_is_zero(decimal), 0);
}

START_TEST(test_s21_is_zero_zero) {
  s21_decimal decimal = {.bits = {0, 0, 0, 0}};
  ck_assert_int_eq(s21_is_zero(decimal), 1);
}

START_TEST(test_s21_is_less) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 1);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 0);

  // 2.4 < 24
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 24;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 24;
  s21_set_scale(&decimal_1, 1);
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 1);

  // Max_Dec^28 > Max_Dec
  decimal_1.bits[3] = 0, decimal_1.bits[2] = -1, decimal_1.bits[1] = -1,
  decimal_1.bits[0] = -1;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = -1, decimal_2.bits[1] = -1,
  decimal_2.bits[0] = -1;
  s21_set_scale(&decimal_1, 28);
  ck_assert_int_eq(s21_is_less(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_less_or_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 0);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_less_or_equal(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_greater) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 1);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater(decimal_1, decimal_2), 0);
}

START_TEST(test_s21_is_greater_or_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 0);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_greater_or_equal(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 0);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 0);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_equal(decimal_1, decimal_2), 1);
}

START_TEST(test_s21_is_not_equal) {
  // 1 < 2
  s21_decimal decimal_1 = {.bits = {-133248880, 240, 0, -2147483648}};
  s21_decimal decimal_2 = {.bits = {333425, 0, 0, 0}};
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 1);

  // 1 == 2
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 240,
  decimal_1.bits[1] = 0, decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);

  // 1 > 2
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 240, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = -2147483648;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 240,
  decimal_2.bits[1] = 0, decimal_2.bits[0] = -2147483648;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 1);

  // 0 = 0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);

  // -0 = 0
  decimal_1.bits[3] = -133248880, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = 0, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);

  // 0 = -0
  decimal_1.bits[3] = 0, decimal_1.bits[2] = 0, decimal_1.bits[1] = 0,
  decimal_1.bits[0] = 0;
  decimal_2.bits[3] = -133248880, decimal_2.bits[2] = 0, decimal_2.bits[1] = 0,
  decimal_2.bits[0] = 0;
  ck_assert_int_eq(s21_is_not_equal(decimal_1, decimal_2), 0);
}

// START_TEST(s21_normalize_test_1) {
//   // write test like s21_decimal = {{0xFF, 0, 0, 0xACDC}}
//   // d_1 = 1.2, d_2 = 0.12
//   s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{12, 0, 0, 0}};
//   s21_set_scale(&d_1, 1);
//   s21_set_scale(&d_2, 2);

//   s21_big_decimal bd_1, bd_2;
//   s21_zanulenie_dec(d_1, &bd_1);
//   s21_zanulenie_dec(d_2, &bd_2);

//   int code = s21_normalize(&bd_1, &bd_2);
//   ck_assert_int_eq(OK, code);

//   code = s21_to_decimal(bd_1, &d_1);
//   ck_assert_int_eq(OK, code);

//   code = s21_to_decimal(bd_2, &d_2);
//   ck_assert_int_eq(OK, code);

//   int scale = s21_get_scale(d_1);
//   ck_assert_int_eq(scale, 2);

//   ck_assert_int_eq(s21_get_scale(d_2), 2);

//   float f_1 = 0.0, f_2 = 0.0;

//   code = s21_from_decimal_to_float(d_1, &f_1);
//   ck_assert_int_eq(OK, code);

//   code = s21_from_decimal_to_float(d_2, &f_2);
//   ck_assert_int_eq(OK, code);

//   ck_assert_float_eq(f_1, 1.2);
//   ck_assert_float_eq(f_2, 0.12);
// }
// END_TEST

START_TEST(s21_normalize_test_2) {
  // write test like s21_decimal = {{0xFF, 0, 0, 0xACDC}}
  // d_1 = 1.2, d_2 = 0.12

  s21_big_decimal bd_1 = {{12, 0, 0, 0, 0, 0, 0, 0}},
                  bd_2 = {{12, 0, 0, 0, 0, 0, 0, 0}};
  s21_set_scale_big(&bd_1, -1);
  int code = s21_normalize(&bd_1, &bd_2);
  ck_assert_int_eq(1, code);
}
END_TEST

START_TEST(s21_shift_left_big_test_1) {
  s21_decimal test = s21_zanulenie_dec(), result_decimal = s21_zanulenie_dec();
  int result = 0, expected = 20, code = OK;

  code = s21_from_int_to_decimal(10, &test);
  ck_assert_int_eq(code, OK);

  s21_big_decimal big_result_decimal, big_test;
  s21_into_big_dec(test, &big_test);
  s21_into_big_dec(result_decimal, &big_result_decimal);

  code = s21_shift_left_big(big_test, 1, &big_result_decimal);
  ck_assert_int_eq(code, OK);

  s21_to_decimal(big_result_decimal, &result_decimal);

  code = s21_from_decimal_to_int(result_decimal, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(result, expected);
}
END_TEST

// x*10 = x*6 + x*4
START_TEST(s21_shift_left_big_test_2) {
  s21_decimal test = s21_zanulenie_dec(), v_result = s21_zanulenie_dec();

  int rnd = 1 + (int)(214748365.0 * rand() / (RAND_MAX + 1.0));
  int result = 0, expected = rnd * 10, code = OK;

  s21_from_int_to_decimal(rnd, &test);
  s21_decimal v_1 = s21_zanulenie_dec(), v_2 = s21_zanulenie_dec();

  s21_big_decimal big_v_1, big_v_2, big_test;
  s21_into_big_dec(v_1, &big_v_1);
  s21_into_big_dec(v_2, &big_v_2);
  s21_into_big_dec(test, &big_test);

  code = s21_shift_left_big(big_test, 3, &big_v_1);  // x*8
  ck_assert_int_eq(code, OK);

  code = s21_shift_left_big(big_test, 1, &big_v_2);  // x*2
  ck_assert_int_eq(code, OK);

  s21_to_decimal(big_v_1, &v_1);
  s21_to_decimal(big_v_2, &v_2);

  code = s21_add(v_1, v_2, &v_result);
  ck_assert_int_eq(code, OK);

  s21_from_decimal_to_int(v_result, &result);

  ck_assert_int_eq(result, expected);
}
END_TEST

START_TEST(floor_test_1) {
  float value = -1.2, expected = -2.0, result_float = 0;
  s21_decimal float_decimal = s21_zanulenie_dec(),
              result_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value, &float_decimal);

  s21_floor(float_decimal, &result_decimal);

  s21_from_decimal_to_float(result_decimal, &result_float);

  ck_assert_float_eq(result_float, expected);
}
END_TEST

// -1.2 -> -2
START_TEST(floor_test_2) {
  s21_decimal float_decimal = {{12, 0, 0, 0}},
              expected_decimal = {{2, 0, 0, 0}}, result_decimal = {{0}};

  s21_set_scale(&float_decimal, 1);
  s21_set_sign(&float_decimal, 1);

  s21_set_sign(&expected_decimal, 1);

  s21_floor(float_decimal, &result_decimal);

  ck_assert_int_eq(s21_is_equal(result_decimal, expected_decimal), 1);
}
END_TEST

START_TEST(floor_test_3) {
  s21_decimal float_decimal = {{12, 0, 0, 0}},
              expected_decimal = {{1, 0, 0, 0}}, result_decimal = {{0}};

  s21_set_scale(&float_decimal, 1);

  s21_floor(float_decimal, &result_decimal);

  ck_assert_int_eq(s21_is_equal(result_decimal, expected_decimal), 1);
}
END_TEST

START_TEST(floor_test_4) {
  float value = 1.2, expected = 1.0, result_float = 0;
  s21_decimal float_decimal = s21_zanulenie_dec(),
              result_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value, &float_decimal);

  s21_floor(float_decimal, &result_decimal);

  s21_from_decimal_to_float(result_decimal, &result_float);

  ck_assert_float_eq(result_float, expected);
}
END_TEST

START_TEST(floor_test_5) {
  // 79228162514264337593543950335
  s21_decimal decimal = {0};
  //  s21_set_sign(decimal, 1);
  s21_big_decimal dec = {
      {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0, 0, 0, 0}};
  s21_set_sign_big(&dec, 1);
  s21_to_decimal(dec, &decimal);
  int code = s21_floor(decimal, NULL);

  ck_assert_int_eq(code, 1);
}

START_TEST(negate_test_1) {
  s21_decimal test = s21_zanulenie_dec(), test_modify = s21_zanulenie_dec();
  s21_from_int_to_decimal(12, &test);

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = -12, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(negate_test_2) {
  s21_decimal test = {{12, 0, 0, 0}};
  s21_decimal test_modify = s21_zanulenie_dec();

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = -12, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

START_TEST(negate_test_3) {
  s21_decimal test = {{0, 0, 0, 0}};
  s21_decimal test_modify = s21_zanulenie_dec();

  int code = s21_negate(test, &test_modify);
  ck_assert_int_eq(code, OK);

  int expected = 0, result = 0;

  code = s21_from_decimal_to_int(test_modify, &result);
  ck_assert_int_eq(code, OK);

  ck_assert_int_eq(expected, result);
}
END_TEST

// START_TEST(negate_test_4) {
//   s21_decimal test = s21_zanulenie_dec(),
//               test_modify = s21_zanulenie_dec();
//   s21_from_int_to_decimal(-5, &test);

//   int code = s21_negate(test, &test_modify);
//   ck_assert_int_eq(code, OK);

//   int expected = 5, result = 0;

//   code = s21_from_decimal_to_int(test_modify, &result);
//   ck_assert_int_eq(code, OK);

//   ck_assert_int_eq(expected, result);
// }
// END_TEST

// 1.2 - 0.2 = 1.0
START_TEST(sub_test_1) {
  float value_1 = 12e-1f, value_2 = 2e-1f, value_3 = 0.0f, expected = 1.0f;
  s21_decimal value_1_decimal = s21_zanulenie_dec(),
              value_2_decimal = s21_zanulenie_dec(),
              value_3_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_sub(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &value_3);

  ck_assert_float_eq(value_3, expected);
}
END_TEST

// 1.2 - 0.2 = 1.0
START_TEST(sub_test_2) {
  float result = 0.0f, expected = 1.08f;

  // d_1 = 1.2, d_2 = 0.12, d3 = d_1 - d_2 = 1.08
  s21_decimal d_1 = {{12, 0, 0, 0}}, d_2 = {{12, 0, 0, 0}};
  s21_set_scale(&d_1, 1);
  s21_set_scale(&d_2, 2);

  s21_decimal d_3 = s21_zanulenie_dec();

  s21_sub(d_1, d_2, &d_3);

  s21_from_decimal_to_float(d_3, &result);

  ck_assert_float_eq(result, expected);
}
END_TEST

// -0.103 - 0.104 = -0.207
START_TEST(sub_test_3) {
  float value_1 = -103e-3f, value_2 = 104e-3f, value_3 = 0.0f,
        expected = -0.207f;
  s21_decimal value_1_decimal = s21_zanulenie_dec(),
              value_2_decimal = s21_zanulenie_dec(),
              value_3_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_sub(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &value_3);

  ck_assert_float_eq(value_3, expected);
}
END_TEST

// -0.103 - (-0.104) = 0.001
START_TEST(sub_test_4) {
  float value_1 = -103e-3f, value_2 = -104e-3f, value_3 = 0.0f,
        expected = 0.001f;
  s21_decimal value_1_decimal = s21_zanulenie_dec(),
              value_2_decimal = s21_zanulenie_dec(),
              value_3_decimal = s21_zanulenie_dec();

  s21_from_float_to_decimal(value_1, &value_1_decimal);
  s21_from_float_to_decimal(value_2, &value_2_decimal);

  s21_sub(value_1_decimal, value_2_decimal, &value_3_decimal);

  s21_from_decimal_to_float(value_3_decimal, &value_3);

  ck_assert_float_eq(value_3, expected);
}
END_TEST

// 123.999 -> 123
START_TEST(truncate_test_1) {
  s21_decimal test = {{123999, 0, 0, 0}}, result_decimal = s21_zanulenie_dec();
  float expected_float = 123.0, res_float = 0.0;
  int expected_int = 123, res_int = 0;

  s21_set_scale(&test, 3);
  s21_truncate(test, &result_decimal);

  s21_from_decimal_to_float(result_decimal, &res_float);
  ck_assert_float_eq(expected_float, res_float);

  s21_from_decimal_to_int(result_decimal, &res_int);
  ck_assert_int_eq(expected_int, res_int);
}
END_TEST

START_TEST(truncate_test_2) {
  // 2640938750475477919784798344.5
  s21_decimal decimal = {{0x55555555, 0x55555555, 0x55555555, 0x10000}};
  s21_decimal result = s21_zanulenie_dec();
  // 2640938750475477919784798344
  s21_decimal decimal_check = {{0x88888888, 0x88888888, 0x8888888, 0x0}};

  s21_truncate(decimal, &result);

  ck_assert_int_eq(s21_is_equal(result, decimal_check), 1);
}

START_TEST(from_dec_to_float_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_scale(&val, 5);
  float res = 1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_dec_to_float_2) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_bit(&val, 127, 1);
  s21_set_scale(&val, 5);
  float res = -1234.56789;
  float tmp = 0.;
  float *dst = &tmp;
  s21_from_decimal_to_float(val, dst);
  ck_assert_float_eq(*dst, res);
}
END_TEST

START_TEST(from_dec_to_float_4) {
  s21_decimal dec = {{0x50fa5a3, 0x0, 0x0, 0x60000}};
  float initial = 84.911523;
  float result = 0;
  int expected_error_code = 0;
  int result_error_code = -1;

  result_error_code = s21_from_decimal_to_float(dec, &result);
  ck_assert_float_eq(initial, result);
  ck_assert_int_eq(expected_error_code, result_error_code);
}
END_TEST

START_TEST(from_dec_to_float_5) {
  s21_decimal dec = {{0x5f22a5, 0x0, 0x0, 0x60000}};
  float *ptr = NULL;
  int expected_error_code = 1;
  int result_error_code = -1;

  result_error_code = s21_from_decimal_to_float(dec, ptr);
  ck_assert_int_eq(expected_error_code, result_error_code);
}
END_TEST

START_TEST(from_dec_to_float_6) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-2, fres);
}
END_TEST

START_TEST(from_dec_to_float_7) {
  s21_decimal val = {{2, 0, 0, ~(UINT_MAX / 2)}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(-1, fres);
}
END_TEST

START_TEST(from_dec_to_float_8) {
  s21_decimal val = {{2, 0, 0, 0}};
  s21_decimal res = {0};
  s21_set_scale(&val, 5);
  s21_floor(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  ck_assert_float_eq(0, fres);
}
END_TEST

START_TEST(from_dec_to_float_9) {
  s21_decimal val = {{7, 7, 7, 0}};
  s21_decimal res = {0};
  s21_round(val, &res);
  float fres = 0;
  s21_from_decimal_to_float(res, &fres);
  float need = 129127208515966861312.0;
  ck_assert_float_eq(need, fres);

  // FROM DECIMAL TO INT
}
END_TEST

START_TEST(from_dec_to_int_1) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_scale(&val, 5);
  int res = 1234;
  int tmp = 0;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_dec_to_int_2) {
  s21_decimal val = {{123456789, 0, 0, 0}};
  s21_set_bit(&val, 127, 1);
  s21_set_scale(&val, 5);
  int res = -1234;
  int tmp = 0.;
  int *dst = &tmp;
  s21_from_decimal_to_int(val, dst);
  ck_assert_int_eq(*dst, res);
}
END_TEST

START_TEST(from_dec_to_int_3) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = 123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_dec_to_int_4) {
  s21_decimal val = {{0, 0, 0, 0}};
  int res = 0;
  int tmp = -123456789;
  s21_from_int_to_decimal(tmp, &val);
  s21_from_decimal_to_int(val, &res);
  ck_assert_int_eq(res, tmp);
}
END_TEST

START_TEST(from_dec_to_int_5) {
  int num_int = 2;
  s21_decimal num_decimal = {{254, 0, 0, 0x80000000}};
  int expected_int = -254;
  int expected_error_code = 0;
  int error_code = s21_from_decimal_to_int(num_decimal, &num_int);
  ck_assert_int_eq(error_code, expected_error_code);
  ck_assert_int_eq(num_int, expected_int);
}
END_TEST

START_TEST(from_dec_to_int_6) {
  int num_int = 0;
  s21_decimal num_decimal = {{0x7FFFFFFF, 0xF, 0x0, 0x0}};
  int expected_int = 1;

  ck_assert_int_eq(s21_from_decimal_to_int(num_decimal, &num_int),
                   expected_int);
}
END_TEST

START_TEST(from_dec_to_int_7) {
  s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x140000}};
  int code = s21_from_decimal_to_int(decimal, NULL);

  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(from_dec_to_int_8) {
  s21_decimal decimal = {{-1, 0, 0, 0x1D0000}};
  int result;
  int code = s21_from_decimal_to_int(decimal, &result);

  ck_assert_int_eq(code, 1);
}
END_TEST

// START_TEST(from_dec_to_int_9) {
// #line 170
//   s21_decimal decimal = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF}};
//   int result;
//   int code = s21_from_decimal_to_int(decimal, &result);
//   s21_from_int_to_decimal;
//   ck_assert_int_eq(code, 1);

//   // FROM INT TO DECIMAL
// }
// END_TEST

START_TEST(from_int_to_dec_1) {
  s21_decimal dec;
  int num = -10;
  s21_from_int_to_decimal(num, &dec);
  ck_assert_int_eq(dec.bits[0], 10);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(s21_get_bit(dec, 127), 1);
}
END_TEST

START_TEST(from_int_to_dec_2) {
  int x = 123451;
  s21_decimal expected = {{x, 0, 0, 0}};
  s21_decimal result = s21_zanulenie_dec();

  s21_from_int_to_decimal(x, &result);

  ck_assert_int_eq(expected.bits[0], result.bits[0]);
}
END_TEST

START_TEST(from_int_to_dec_3) {
  s21_decimal dec;
  int num = -12345678;
  s21_from_int_to_decimal(num, &dec);
  ck_assert_int_eq(dec.bits[0], 12345678);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(s21_get_bit(dec, 127), 1);
}
END_TEST

START_TEST(from_int_to_dec_4) {
  s21_decimal dec;
  int num = 12345678;
  s21_from_int_to_decimal(num, &dec);
  ck_assert_int_eq(dec.bits[0], 12345678);
  ck_assert_int_eq(dec.bits[1], 0);
  ck_assert_int_eq(dec.bits[2], 0);
  ck_assert_int_eq(s21_get_bit(dec, 127), 0);
}
END_TEST

START_TEST(from_int_to_dec_5) {
  int x = 654321;
  s21_decimal expected = {{x, 0, 0, 0}};
  expected.bits[3] |= (1u << 31);

  s21_decimal result = s21_zanulenie_dec();

  s21_from_int_to_decimal(x * -1, &result);

  ck_assert_int_eq(expected.bits[0], result.bits[0]);
  ck_assert_int_eq(expected.bits[3], result.bits[3]);

  // FROM FLOAT TO DECIMAL
}
END_TEST

START_TEST(from_float_to_dec_1) {
  float num1 = 1234567890123456789012345.678;
  float num2 = 0.0;
  s21_decimal dec;
  int error = s21_from_float_to_decimal(num1, &dec);
  s21_from_decimal_to_float(dec, &num2);
  ck_assert_int_eq(0, error);
  ck_assert_float_eq(num1, num2);
}
END_TEST

START_TEST(from_float_to_dec_2) {
  float initial_float = 545706772;
  s21_decimal *ptr = NULL;
  int error_code = -1;
  int expected_error_code = 1;
  error_code = s21_from_float_to_decimal(initial_float, ptr);
  ck_assert_int_eq(error_code, expected_error_code);
}
END_TEST

START_TEST(from_float_to_dec_3) {
  float f = 1234567890123456789012345678.0;
  s21_decimal result_decimal = {{0x5000000, 0x62516078, 0x3FD35F1, 0x0}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(f, &result);
  for (int i = 0; i < 4; i++)
    ck_assert_int_eq(result_decimal.bits[i], result.bits[i]);
}
END_TEST

START_TEST(from_float_to_dec_4) {
  float f = 989989898989898989898989898989898989898.9;
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

START_TEST(from_float_to_dec_5) {
  float f = 9899898989898989898989898989898989.9f;
  s21_decimal result = {{0, 0, 0, 0}};
  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

START_TEST(from_float_to_dec_6) {
  float f = 0.0;
  s21_decimal result;
  s21_decimal check = {{0x0, 0x0, 0x0, 0x0}};
  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, OK);
  ck_assert_int_eq(s21_is_equal(result, check), 1);
}
END_TEST

START_TEST(from_float_to_dec_7) {
  float f = NAN;
  s21_decimal result;
  int code = s21_from_float_to_decimal(f, &result);
  ck_assert_int_eq(code, BIG_ETER_ERR);
}
END_TEST

void srunner_add_arithmetic_tests(SRunner *sr) {
  Suite *save_v1 = suite_create("Operations");
  TCase *tc1_1 = tcase_create("Operations");
  suite_add_tcase(save_v1, tc1_1);
  tcase_add_test(tc1_1, add_test_1);
  tcase_add_test(tc1_1, add_test_2);
  tcase_add_test(tc1_1, add_test_3);
  // tcase_add_test(tc1_1, s21_div_2);
  tcase_add_test(tc1_1, s21_div_3);
  tcase_add_test(tc1_1, mul_test_1);
  tcase_add_test(tc1_1, mul_test_2);
  tcase_add_test(tc1_1, mul_test_3);
  tcase_add_test(tc1_1, mul_test_4);
  tcase_add_test(tc1_1, mul_test_5);
  tcase_add_test(tc1_1, mul_test_6);

  tcase_add_test(tc1_1, s21_div_11);
  tcase_add_test(tc1_1, manual_div_1);

  tcase_add_test(tc1_1, manual_div_5);
  tcase_add_test(tc1_1, manual_div_6);
  tcase_add_test(tc1_1, manual_div_7);

  tcase_add_test(tc1_1, round_test_1);
  tcase_add_test(tc1_1, round_test_2);
  tcase_add_test(tc1_1, round_test_3);
  tcase_add_test(tc1_1, round_test_4);
  tcase_add_test(tc1_1, round_test_5);
  tcase_add_test(tc1_1, round_test_6);
  tcase_add_test(tc1_1, round_test_7);

  tcase_add_test(tc1_1, negate_test_1);
  tcase_add_test(tc1_1, negate_test_2);
  tcase_add_test(tc1_1, negate_test_3);
  // tcase_add_test(tc1_1, negate_test_4);

  tcase_add_test(tc1_1, floor_test_1);
  tcase_add_test(tc1_1, floor_test_2);
  tcase_add_test(tc1_1, floor_test_3);
  tcase_add_test(tc1_1, floor_test_4);
  tcase_add_test(tc1_1, floor_test_5);

  tcase_add_test(tc1_1, sub_test_1);
  tcase_add_test(tc1_1, sub_test_2);
  tcase_add_test(tc1_1, sub_test_3);
  tcase_add_test(tc1_1, sub_test_4);

  tcase_add_test(tc1_1, truncate_test_1);
  tcase_add_test(tc1_1, truncate_test_2);

  tcase_add_test(tc1_1, test_s21_is_equal_1);
  tcase_add_test(tc1_1, test_s21_is_equal_2);
  tcase_add_test(tc1_1, test_s21_is_equal_3);
  tcase_add_test(tc1_1, test_s21_is_equal_4);
  tcase_add_test(tc1_1, test_s21_is_equal_5);
  tcase_add_test(tc1_1, test_s21_is_less_1);
  tcase_add_test(tc1_1, test_s21_is_less_2);
  tcase_add_test(tc1_1, test_s21_is_less_3);
  tcase_add_test(tc1_1, test_s21_is_less_4);
  tcase_add_test(tc1_1, test_s21_is_less_5);
  tcase_add_test(tc1_1, test_s21_is_less_6);
  tcase_add_test(tc1_1, test_s21_is_less_7);
  tcase_add_test(tc1_1, test_s21_is_less_8);
  tcase_add_test(tc1_1, test_s21_is_less_9);
  tcase_add_test(tc1_1, test_s21_is_less_10);
  tcase_add_test(tc1_1, test_s21_is_less_11);
  tcase_add_test(tc1_1, test_s21_is_less_12);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_greater_1);
  tcase_add_test(tc1_1, test_s21_is_greater_2);
  tcase_add_test(tc1_1, test_s21_is_greater_3);
  tcase_add_test(tc1_1, test_s21_is_greater_4);
  tcase_add_test(tc1_1, test_s21_is_greater_5);
  tcase_add_test(tc1_1, test_s21_is_greater_6);
  tcase_add_test(tc1_1, test_s21_is_greater_7);
  tcase_add_test(tc1_1, test_s21_is_greater_8);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_5);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_6);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_7);
  tcase_add_test(tc1_1, test_s21_is_not_equal_1);
  tcase_add_test(tc1_1, test_s21_is_not_equal_2);

  tcase_add_test(tc1_1, dtof_test_1);
  tcase_add_test(tc1_1, dtof_test_2);
  tcase_add_test(tc1_1, dtof_test_3);

  tcase_add_test(tc1_1, dtoi_test_1);
  tcase_add_test(tc1_1, dtoi_test_2);
  tcase_add_test(tc1_1, dtoi_test_3);
  tcase_add_test(tc1_1, dtoi_test_4);
  tcase_add_test(tc1_1, dtoi_test_5);

  tcase_add_test(tc1_1, ftod_test_7);
  tcase_add_test(tc1_1, ftod_test_8);
  tcase_add_test(tc1_1, ftod_test_unnormal1);
  tcase_add_test(tc1_1, ftod_test_unnormal2);
  tcase_add_test(tc1_1, ftod_test_unnormal3);
  tcase_add_test(tc1_1, ftod_test_unnormal4);
  tcase_add_test(tc1_1, ftod_test_unnormal5);
  tcase_add_test(tc1_1, ftod_test_unnormal6);
  // tcase_add_test(tc1_1, ftod_test_unnormal7);

  tcase_add_test(tc1_1, itod_test_1);
  // tcase_add_test(tc1_1, itod_test_2);

  tcase_add_test(tc1_1, test_s21_is_zero_non_zero);
  tcase_add_test(tc1_1, test_s21_is_zero_zero);

  tcase_add_test(tc1_1, test_s21_is_less);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal);

  tcase_add_test(tc1_1, test_s21_is_greater);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal);

  tcase_add_test(tc1_1, test_s21_is_equal);
  tcase_add_test(tc1_1, test_s21_is_not_equal);

  // tcase_add_test(tc1_1, s21_normalize_test_1);
  tcase_add_test(tc1_1, s21_normalize_test_2);

  tcase_add_test(tc1_1, s21_shift_left_big_test_1);
  tcase_add_test(tc1_1, s21_shift_left_big_test_2);

  tcase_add_test(tc1_1, from_dec_to_float_1);
  tcase_add_test(tc1_1, from_dec_to_float_2);
  tcase_add_test(tc1_1, from_dec_to_float_4);
  tcase_add_test(tc1_1, from_dec_to_float_5);
  tcase_add_test(tc1_1, from_dec_to_float_6);
  tcase_add_test(tc1_1, from_dec_to_float_7);
  tcase_add_test(tc1_1, from_dec_to_float_8);
  tcase_add_test(tc1_1, from_dec_to_float_9);
  tcase_add_test(tc1_1, from_dec_to_int_1);
  tcase_add_test(tc1_1, from_dec_to_int_2);
  tcase_add_test(tc1_1, from_dec_to_int_3);
  tcase_add_test(tc1_1, from_dec_to_int_4);
  tcase_add_test(tc1_1, from_dec_to_int_5);
  tcase_add_test(tc1_1, from_dec_to_int_6);
  tcase_add_test(tc1_1, from_dec_to_int_7);
  tcase_add_test(tc1_1, from_dec_to_int_8);
  // tcase_add_test(tc1_1, from_dec_to_int_9);
  tcase_add_test(tc1_1, from_int_to_dec_1);
  tcase_add_test(tc1_1, from_int_to_dec_2);
  tcase_add_test(tc1_1, from_int_to_dec_3);
  tcase_add_test(tc1_1, from_int_to_dec_4);
  tcase_add_test(tc1_1, from_int_to_dec_5);
  tcase_add_test(tc1_1, from_float_to_dec_1);
  tcase_add_test(tc1_1, from_float_to_dec_2);
  tcase_add_test(tc1_1, from_float_to_dec_3);
  tcase_add_test(tc1_1, from_float_to_dec_4);
  tcase_add_test(tc1_1, from_float_to_dec_5);
  tcase_add_test(tc1_1, from_float_to_dec_6);
  tcase_add_test(tc1_1, from_float_to_dec_7);

  srunner_add_suite(sr, save_v1);
}

int main(void) {
  Suite *s = suite_create("Decimal tests");
  SRunner *sr = srunner_create(s);
  int nf;
  srunner_add_arithmetic_tests(sr);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
