#include "controller_calculator.h"

namespace s21 {
void CalculatorController::SetExpression(const std::string &input_str,
                                         const long double x) noexcept {
  object_.SetInputStr(input_str);
  object_.SetX(x);
}

void CalculatorController::Calculate() { object_.Calculate(); }

long double CalculatorController::GetX(const std::string &input_x,
                                       int *error) noexcept {
  long double result = object_.get_x(input_x, error);
  return result;
}

long double CalculatorController::GetResult() const noexcept {
  return object_.GetResult();
}

enum Status CalculatorController::GetStatus() const noexcept {
  return object_.GetStatus();
}

int CalculatorController::GetStatusValidInput(std::string str) noexcept {
  int res = object_.valid_input(str);
  return res;
}
}  // namespace s21