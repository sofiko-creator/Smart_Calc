#ifndef CALC_MODEL_H_
#define CALC_MODEL_H_
#include <cmath>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <vector>

#include "members.h"
#define S21_IS_NAN(x) (x != x)

namespace s21 {
enum Status { kError, kOk };

class CalculatorModel {
 public:
  CalculatorModel() = default;
  ~CalculatorModel() = default;
  enum Status status_ = kOk;

  void Calculate();
  void SetInputStr(const std::string input_str_set) noexcept;
  void SetX(const long double x_set) noexcept;
  long double GetResult() const;
  enum Status GetStatus() const;
  long double get_x(std::string str, int* error) noexcept;
  int valid_input(std::string input);

 private:
  long double convert_to_number(std::string input, int i, int* digitCount);
  std::stack<s21::Members> stack_ptr;
  std::queue<s21::Members> output_queue;
  std::string input_str = "";
  std::string output_str = "";
  long double x_ = 0;
  long double result_ = 0;
  void convert_to_stack(std::string input);
  void add_value(double value);
  void add_bracket_open();
  void add_bracket_close();
  void convert_to_operation(std::string input, int i, Members* res);
  void set_member(Members* obj_stack_ptr, double value, int type);
  void convert_to_RPN();
  long double get_answer();
  long double calculate_two_value(long double val_1, long double val_2,
                                  const char* str);
  long double calculate_one_value(long double val_1, const char* str);
};  // CalculatorModel

}  // namespace s21
#endif