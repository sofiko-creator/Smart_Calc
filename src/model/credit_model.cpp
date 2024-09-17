#include "credit_model.h"
namespace s21 {

CreditModel::CreditModel() {
  sum_value = 0.0;
  month_percent = 0.0;
  time_value = 0.0;
}

double CreditModel::GetMonthPay() {
  double month_pay = sum_value *
                     (month_percent * pow((1 + month_percent), time_value)) /
                     (pow((1 + month_percent), time_value) - 1);
  month_pay = round(month_pay * 100.0) / 100.0;
  return month_pay;
}

double CreditModel::GetFirstMonthPay() {
  double first_month_pay = (sum_value / time_value) + sum_value * month_percent;
  first_month_pay = round(first_month_pay * 100.0) / 100.0;
  return first_month_pay;
}

double CreditModel::GetLastMonthPay() {
  double last_month_pay =
      (sum_value / time_value) +
      (sum_value - (time_value - 1) * (sum_value / time_value)) * month_percent;
  last_month_pay = round(last_month_pay * 100.0) / 100.0;
  return last_month_pay;
}

double CreditModel::GetOverpaymentAnnuity() {
  double all_pay =
      (sum_value * (month_percent * pow((1 + month_percent), time_value)) /
       (pow((1 + month_percent), time_value) - 1)) *
      time_value;
  double res = all_pay - sum_value;
  res = round(res * 100.0) / 100.0;
  return res;
}

double CreditModel::GetOverpaymentDiff() {
  double all_pay = 0.0;
  for (int i = 1; i <= time_value; i++) {
    all_pay += (sum_value / time_value) +
               (sum_value - (i - 1) * (sum_value / time_value)) * month_percent;
  }
  double res = all_pay - sum_value;
  res = round(res * 100.0) / 100.0;
  return res;
}

double CreditModel::GetAllPayAnnuity() {
  double all_pay =
      (sum_value * (month_percent * pow((1 + month_percent), time_value)) /
       (pow((1 + month_percent), time_value) - 1)) *
      time_value;
  all_pay = round(all_pay * 100.0) / 100.0;
  return all_pay;
}

double CreditModel::GetAllPayDiff() {
  double all_pay = 0.0;
  for (int i = 1; i <= time_value; i++) {
    all_pay += (sum_value / time_value) +
               (sum_value - (i - 1) * (sum_value / time_value)) * month_percent;
  }
  all_pay = round(all_pay * 100.0) / 100.0;
  return all_pay;
}

void CreditModel::SetParametrs(double sum_value_other,
                               double month_percent_other,
                               double time_value_other) {
  sum_value = sum_value_other;
  month_percent = month_percent_other;
  time_value = time_value_other;
}

}  // namespace s21