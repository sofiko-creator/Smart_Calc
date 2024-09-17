#ifndef CREDIT_MODEL_H_
#define CREDIT_MODEL_H_
#include <math.h>

#include <iostream>

namespace s21 {
class CreditModel {
 public:
  CreditModel();
  ~CreditModel() = default;
  double GetMonthPay();
  double GetFirstMonthPay();
  double GetLastMonthPay();
  double GetOverpaymentAnnuity();
  double GetOverpaymentDiff();
  double GetAllPayAnnuity();
  double GetAllPayDiff();
  void SetParametrs(double sum_value_other, double month_percent_other,
                    double time_value_other);

 private:
  double sum_value;
  double month_percent;
  double time_value;
};
}  // namespace s21

#endif