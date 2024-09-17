#include <gtest/gtest.h>

#include "../model/calc_model.h"

TEST(SmartCalc, CheckInput) {
  s21::CalculatorModel obj;
  int err = 0;
  std::string strs = "1+2+3-log(6)*sqrt(10)+ln(10)";
  err = obj.valid_input(strs);
  EXPECT_EQ(1, err);

  std::string str_1 = "1+2+3*ln()";

  err = obj.valid_input(str_1);
  EXPECT_EQ(0, err);

  std::string string_2 = "1.123123+2mod4+(3*7)+sqrt(7)";

  err = obj.valid_input(string_2);
  EXPECT_EQ(1, err);

  std::string string_3 = "1+2mod4+3*(7+1)+acos(1/2)+5^2";

  err = obj.valid_input(string_3);
  EXPECT_EQ(1, err);

  std::string string_4 = "1+2mod4+3*(7+1)+asin(1/)";

  err = obj.valid_input(string_4);
  EXPECT_EQ(0, err);

  std::string string_5 = "^1+2mod4+3*(7+1)+atan(1/2)";

  err = obj.valid_input(string_5);
  EXPECT_EQ(0, err);

  std::string string_6 = "cos(1/2)+2mod4+3*(7+1)+sin(0)";

  err = obj.valid_input(string_6);
  EXPECT_EQ(1, err);

  std::string string_7 = "tan(1/2)+2mod4+3*(7+1)+asin(0)+atan(0)";

  err = obj.valid_input(string_7);
  EXPECT_EQ(1, err);

  std::string string_8 = "123456789+";

  err = obj.valid_input(string_8);
  EXPECT_EQ(0, err);

  std::string string_9 = "1/2+acos(3)-log(6)+ln(8)-asin(5)+atan(3)+cos(213)^";

  err = obj.valid_input(string_9);
  EXPECT_EQ(0, err);

  std::string string_11 = "1+4/";

  err = obj.valid_input(string_11);
  EXPECT_EQ(0, err);

  std::string string_12 = "1+4*";

  err = obj.valid_input(string_12);
  EXPECT_EQ(0, err);

  std::string string_13 = "1+5-4*)";

  err = obj.valid_input(string_13);
  EXPECT_EQ(0, err);

  std::string string_14 = "1+((5-4)/410";

  err = obj.valid_input(string_14);
  EXPECT_EQ(0, err);

  std::string string_15 = "4mod2+(5-4)";

  err = obj.valid_input(string_15);
  EXPECT_EQ(1, err);

  std::string string_16 = "00+(5-4)";

  err = obj.valid_input(string_16);
  EXPECT_EQ(1, err);

  std::string string_17 = "*0+(5-4)";

  err = obj.valid_input(string_17);
  EXPECT_EQ(0, err);

  std::string string_18 = "1/0+2";

  err = obj.valid_input(string_18);
  EXPECT_EQ(1, err);

  std::string string_19 = "1+";

  err = obj.valid_input(string_19);
  EXPECT_EQ(0, err);

  std::string string_error = "ERROR";

  err = obj.valid_input(string_error);
  EXPECT_EQ(0, err);

  std::string string_nan = "nan";

  err = obj.valid_input(string_nan);
  EXPECT_EQ(0, err);

  std::string string_inf = "inf";

  err = obj.valid_input(string_inf);
  EXPECT_EQ(0, err);

  std::string string_20 = "1+x";

  std::string str = "45.0";
  int err_x = 0;
  double value_x = obj.get_x(str, &err_x);
  err = obj.valid_input(string_20);
  EXPECT_EQ(1, err);
  EXPECT_EQ(0, err_x);
  EXPECT_EQ(45.0, value_x);

  std::string str0_1 = "\0";
  err_x = 0;
  value_x = obj.get_x(str0_1, &err_x);
  EXPECT_EQ(1, err_x);

  std::string str0_2 = "4.";
  err_x = 0;
  value_x = obj.get_x(str0_2, &err_x);
  EXPECT_EQ(1, err_x);

  std::string string_21 = "cos(x)-sin(4)";

  err_x = 0;
  std::string str1 = "45.0sd";
  value_x = obj.get_x(str1, &err_x);
  err = obj.valid_input(string_21);
  EXPECT_EQ(1, err);
  EXPECT_EQ(1, err_x);

  err_x = 0;
  std::string str2 = "45.0.0";
  value_x = obj.get_x(str2, &err_x);
  EXPECT_EQ(1, err_x);

  err_x = 0;
  std::string str3 = "-45";
  value_x = obj.get_x(str3, &err_x);
  EXPECT_EQ(0, err_x);

  std::string string_22 = "1x";

  err = obj.valid_input(string_22);
  EXPECT_EQ(0, err);

  std::string string_23 = "x5";

  err = obj.valid_input(string_23);
  EXPECT_EQ(0, err);

  std::string string_24 = "-mod9";

  err = obj.valid_input(string_24);
  EXPECT_EQ(0, err);

  std::string string_25 = "9mod-";

  err = obj.valid_input(string_25);
  EXPECT_EQ(0, err);

  std::string string_26 = "9.";

  err = obj.valid_input(string_26);
  EXPECT_EQ(0, err);
}

TEST(SmartCalc, Calculate) {
  long double answer = 0.0;
  long double res_original = 0.0;
  int error = 0;
  s21::CalculatorModel obj;

  std::string input = "(-1)*cos(1)+3";
  answer = 0.0;
  error = obj.valid_input(input);
  obj.SetInputStr(input);
  obj.Calculate();
  answer = obj.GetResult();
  res_original = -cos(1) + 3;
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_1 = "-0.1+0.2";
  answer = 0.0;
  error = obj.valid_input(input_1);
  obj.SetInputStr(input_1);
  obj.Calculate();
  answer = obj.GetResult();
  res_original = -0.1 + 0.2;
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_2 =
      "15.4121212121212/(7.1-(1.1+1.1))*3-(2+(1+1))*15.4/"
      "(7-(200.1+1))*3-(2+(1+1))*(15.0/"
      "(7-(1.1+1))*3.4-(2+(1+1))+15.23456789101112/(7.5-(1+1))*3.5-(2+(1+1)))";
  answer = 0.0;
  error = obj.valid_input(input_2);
  res_original = 15.4121212121212 / (7.1 - (1.1 + 1.1)) * 3 -
                 (2 + (1 + 1)) * 15.4 / (7 - (200.1 + 1)) * 3 -
                 (2 + (1 + 1)) * (15.0 / (7 - (1.1 + 1)) * 3.4 - (2 + (1 + 1)) +
                                  15.23456789101112 / (7.5 - (1 + 1)) * 3.5 -
                                  (2 + (1 + 1)));
  obj.SetInputStr(input_2);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error);

  std::string input_3 = "2^(2.1+1)-11mod2";
  answer = 0.0;
  error = obj.valid_input(input_3);
  res_original = pow(2, (2.1 + 1)) - fmod(11, 2);
  obj.SetInputStr(input_3);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_4 = "sin(0.5)-cos(1)+tan(0.5)+acos(0.5)-asin(1)-atan(1)";
  answer = 0.0;
  error = obj.valid_input(input_4);
  res_original = sin(0.5) - cos(1) + tan(0.5) + acos(0.5) - asin(1) - atan(1);
  obj.SetInputStr(input_4);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error);

  std::string input_5 = "sqrt(4.123456789)+3-1.12";
  answer = 0.0;
  error = obj.valid_input(input_5);
  res_original = sqrt(4.123456789) + 3 - 1.12;
  obj.SetInputStr(input_5);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error);

  std::string input_6 = "log(+10.2)-ln(10.2)";
  answer = 0.0;
  error = obj.valid_input(input_6);
  res_original = log10(10.2) - log(10.2);
  obj.SetInputStr(input_6);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_7 = "11+(-2)^5";
  answer = 0.0;
  error = obj.valid_input(input_7);
  res_original = 11 + pow(-2, 5);
  obj.SetInputStr(input_7);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_8 = "log(10.2)+ln(10.2)";
  answer = 0.0;
  error = obj.valid_input(input_8);
  res_original = log10(10.2) + log(10.2);
  obj.SetInputStr(input_8);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_9 = "sqrt(+4+1)+(-3+1)";
  answer = 0.0;
  error = obj.valid_input(input_9);
  res_original = sqrt(4 + 1) + (-3 + 1);
  obj.SetInputStr(input_9);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_10 = "sqrt(3+1)-(-3+1)";
  answer = 0.0;
  error = obj.valid_input(input_10);
  res_original = sqrt(3 + 1) - (-3 + 1);
  obj.SetInputStr(input_10);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_11 = "+1.1122-(-1)";
  answer = 0.0;
  error = obj.valid_input(input_11);
  res_original = +1.1122 - (-1);
  obj.SetInputStr(input_11);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);

  std::string input_12 = "2^(2.1+1)+(";
  answer = 0.0;
  error = obj.valid_input(input_12);
  EXPECT_EQ(0, error);

  std::string input_13 = "2^(2.1+1)+()";
  answer = 0.0;
  error = obj.valid_input(input_13);
  EXPECT_EQ(0, error);

  std::string input_14 = "2^(2.1+1)+2-(3+1)";
  answer = 0.0;
  error = obj.valid_input(input_14);
  EXPECT_EQ(1, error);

  std::string input_15 = "sqrt(+4*x+1)+(-3+1)";
  answer = 0.0;
  error = obj.valid_input(input_15);
  res_original = sqrt(4 * 5.8 + 1) + (-3 + 1);
  obj.SetX(5.8);
  obj.SetInputStr(input_15);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error);
}

TEST(SmartCalc, CalculationWithUnaryMinus) {
  s21::CalculatorModel obj;
  long double answer = 0.0;
  long double res_original = 0.0;
  int error2 = 0;
  std::string input = "-cos(1)+3";
  answer = 0.0;
  error2 = obj.valid_input(input);
  res_original = -cos(1) + 3;
  obj.SetInputStr(input);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error2);

  std::string input2 = "-sin(1)+3+(-log(8)+9)";
  answer = 0.0;
  error2 = obj.valid_input(input2);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  obj.SetInputStr(input2);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);

  std::string input3 = "-sin(1)+3+(-log(8)+9)";
  answer = 0.0;
  error2 = obj.valid_input(input3);
  res_original = -sin(1) + 3 + (-log10(8) + 9);
  obj.SetInputStr(input3);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);

  std::string input4 = "-sqrt(-9.9)-sin(3)";
  answer = 0.0;
  error2 = obj.valid_input(input4);
  res_original = -sqrt(-9.9) - sin(3);
  obj.SetInputStr(input4);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_TRUE(S21_IS_NAN(res_original));
  EXPECT_TRUE(S21_IS_NAN(answer));
  EXPECT_EQ(1, error2);

  std::string input5 = "-x+(-sin(3)-ln(99))";
  answer = 0.0;
  error2 = obj.valid_input(input5);
  res_original = -5.6 + (-sin(3) - log(99));
  obj.SetX(5.6);
  obj.SetInputStr(input5);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);

  std::string input6 = "-6*3+9*x";
  answer = 0.0;
  error2 = obj.valid_input(input6);
  res_original = -6 * 3 + 9 * (-3);
  obj.SetX(-3);
  obj.SetInputStr(input6);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error2);

  std::string input7 = "-x";
  answer = 0.0;
  error2 = obj.valid_input(input7);
  res_original = 3;
  obj.SetX(-3);
  obj.SetInputStr(input7);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error2);
}

TEST(SmartCalc, CalculationWithUnaryPlus) {
  s21::CalculatorModel obj;
  long double answer = 0.0;
  long double res_original = 0.0;
  int error2 = 0;
  std::string input = "+cos(1)+3";
  answer = 0.0;
  error2 = obj.valid_input(input);
  res_original = cos(1) + 3;
  obj.SetInputStr(input);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error2);

  std::string input2 = "+sin(1)+3+(+log(8)+9)";
  answer = 0.0;
  error2 = obj.valid_input(input2);
  res_original = sin(1) + 3 + (log10(8) + 9);
  obj.SetInputStr(input2);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);

  std::string input3 = "+sin(1)+3+(+log(8)+9)";
  answer = 0.0;
  error2 = obj.valid_input(input3);
  res_original = sin(1) + 3 + (log10(8) + 9);
  obj.SetInputStr(input3);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);

  std::string input4 = "+sqrt(+9.9)-sin(3)";
  answer = 0.0;
  error2 = obj.valid_input(input4);
  res_original = sqrt(9.9) - sin(3);
  obj.SetInputStr(input4);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);

  std::string input5 = "+x+(+sin(3)-ln(99))";
  answer = 0.0;
  error2 = obj.valid_input(input5);
  res_original = 5.6 + (sin(3) - log(99));
  obj.SetX(5.6);
  obj.SetInputStr(input5);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_NEAR(res_original, answer, 1e-9);
  EXPECT_EQ(1, error2);
}

TEST(SmartCalc, HardTest) {
  s21::CalculatorModel obj;
  long double answer = 0.0;
  long double res_original = 0.0;
  int error2 = 0;
  std::string input = "2^(3)^(2)";
  answer = 0.0;
  error2 = obj.valid_input(input);
  res_original = pow(2, pow(3, 2));
  obj.SetInputStr(input);
  obj.Calculate();
  answer = obj.GetResult();
  EXPECT_EQ(res_original, answer);
  EXPECT_EQ(1, error2);

  std::string input1 = "2^(3)^(2)+)(";
  answer = 0.0;
  error2 = obj.valid_input(input1);
  EXPECT_EQ(0, error2);
}