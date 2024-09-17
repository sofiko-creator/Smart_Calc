#include "controller_credit.h"

namespace s21 {
double ControllerCredit::GetMonthPay() {
  double res = object_.GetMonthPay();
  return res;
}

double ControllerCredit::GetFirstMonthPay() {
  double res = object_.GetFirstMonthPay();
  return res;
}

double ControllerCredit::GetLastMonthPay() {
  double res = object_.GetLastMonthPay();
  return res;
}

double ControllerCredit::GetOverpaymentAnnuity() {
  double res = object_.GetOverpaymentAnnuity();
  return res;
}
double ControllerCredit::GetOverpaymentDiff() {
  double res = object_.GetOverpaymentDiff();
  return res;
}

double ControllerCredit::GetAllPayAnnuity() {
  double res = object_.GetAllPayAnnuity();
  return res;
}
double ControllerCredit::GetAllPayDiff() {
  double res = object_.GetAllPayDiff();
  return res;
}

void ControllerCredit::SetParametrs(double sum_value, double month_percent,
                                    double time_value) {
  object_.SetParametrs(sum_value, month_percent, time_value);
}
}  // namespace s21