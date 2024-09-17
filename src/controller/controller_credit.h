#ifndef CONTROLLER_CREDIT_H_
#define CONTROLLER_CREDIT_H_
#include "../model/credit_model.h"

namespace s21 {
class ControllerCredit {
 public:
  ControllerCredit() = default;
  ~ControllerCredit() = default;
  double GetMonthPay();
  double GetFirstMonthPay();
  double GetLastMonthPay();
  double GetOverpaymentAnnuity();
  double GetOverpaymentDiff();
  double GetAllPayAnnuity();
  double GetAllPayDiff();
  void SetParametrs(double sum_value, double month_percent, double time_value);

 private:
  CreditModel object_;
};
}  // namespace s21
#endif