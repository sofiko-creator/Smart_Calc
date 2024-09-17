#ifndef CONTROLLER_CALCULATOR_H_
#define CONTROLLER_CALCULATOR_H_

#include <string>

#include "../model/calc_model.h"

namespace s21 {
class CalculatorController {
 public:
  CalculatorController() = default;
  ~CalculatorController() = default;

  long double GetX(const std::string &input_x, int *error) noexcept;
  void SetExpression(const std::string &input_str,
                     const long double x) noexcept;

  void Calculate();

  long double GetResult() const noexcept;

  enum Status GetStatus() const noexcept;

  int GetStatusValidInput(std::string str) noexcept;

 private:
  CalculatorModel object_;

};  // CalculatorController

}  // namespace s21

#endif