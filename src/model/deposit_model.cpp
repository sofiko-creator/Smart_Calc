#include "deposit_model.h"
namespace s21 {
double DepositModel::add_percent(double sum_value, double time_value,
                                 double percent_value, bool flag) {
  double percent = 0, res_percent = 0;
  if (flag == true) num_sn *= 12;
  for (int i = 0; i < time_value; i++) {
    if ((i % 12 == 0) && (i != time_value - 1) && (i != 0))
      sum_value += annual_rep;
    if ((i % 3 == 0) && (i != time_value - 1) && (i != 0))
      sum_value += quarterly_rep;
    if ((i != time_value - 1) && (i != 0)) sum_value += monthly_rep;
    if (i + 1 == num_sn) sum_value -= sum_sn;
    percent = sum_value * percent_value / 12.0;
    res_percent += percent;
  }

  return res_percent;
}

double DepositModel::add_percent_compound(double sum_value, double time_value,
                                          double percent_value, bool flag) {
  double percent = 0, res_percent = 0;
  if (flag == true) num_sn *= 12;
  for (int i = 0; i < time_value; i++) {
    if ((i % 12 == 0) && (i != time_value - 1) && (i != 0))
      sum_value += annual_rep;
    if ((i % 3 == 0) && (i != time_value - 1) && (i != 0))
      sum_value += quarterly_rep;
    if ((i != time_value - 1) && (i != 0)) sum_value += monthly_rep;
    if (i + 1 == num_sn) sum_value -= sum_sn;
    percent = (sum_value + res_percent) * percent_value / 12.0;
    res_percent += percent;
  }

  return res_percent;
}

void DepositModel::SetAllParams(double monthly_rep_other,
                                double quarterly_rep_other,
                                double annual_rep_other, double sum_sn_other,
                                int ok_other, int no_other) {
  monthly_rep = monthly_rep_other;
  quarterly_rep = quarterly_rep_other;
  annual_rep = annual_rep_other;
  sum_sn = sum_sn_other;
  ok = ok_other;
  no = no_other;
}

void DepositModel::SetOkNoParams(int ok_other, int no_other) {
  ok = ok_other;
  no = no_other;
}

void DepositModel::SetMonthQuartAnnualRep(double monthly_rep_other,
                                          double quarterly_rep_other,
                                          double annual_rep_other) {
  monthly_rep = monthly_rep_other;
  quarterly_rep = quarterly_rep_other;
  annual_rep = annual_rep_other;
}

void DepositModel::SetSumNumSn(double num_sn_other, double sum_sn_other) {
  num_sn = num_sn_other;
  sum_sn = sum_sn_other;
}

double DepositModel::GetSumEnd(double res_percent, double sum_value,
                               double time_value) {
  double sum_end = sum_value + res_percent + monthly_rep * (time_value - 1) +
                   quarterly_rep * (floor(time_value / 3) - 1) +
                   annual_rep * (floor(time_value / 12) - 1) - sum_sn;
  sum_end = round(sum_end * 100.0) / 100.0;
  return sum_end;
}

double DepositModel::GetTax(double res_percent, double time_value,
                            double percent_nal_value) {
  double tax =
      (res_percent - max_ans_without_tax * time_value) * percent_nal_value;
  if (tax < 0) tax = 0;
  tax = round(tax * 100.0) / 100.0;
  return tax;
}
}  // namespace s21