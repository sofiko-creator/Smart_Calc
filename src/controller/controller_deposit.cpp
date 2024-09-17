#include "controller_deposit.h"

namespace s21 {
double ControllerDeposit::add_percent(double sum_value, double time_value,
                                      double percent_value, bool flag) {
  double result =
      object_.add_percent(sum_value, time_value, percent_value, flag);
  return result;
}

double ControllerDeposit::add_percent_compound(double sum_value,
                                               double time_value,
                                               double percent_value,
                                               bool flag) {
  double result =
      object_.add_percent_compound(sum_value, time_value, percent_value, flag);
  return result;
}

void ControllerDeposit::SetAllParams(double monthly_rep_other,
                                     double quarterly_rep_other,
                                     double annual_rep_other,
                                     double sum_sn_other, int ok_other,
                                     int no_other) {
  object_.SetAllParams(monthly_rep_other, quarterly_rep_other, annual_rep_other,
                       sum_sn_other, ok_other, no_other);
}
void ControllerDeposit::SetOkNoParams(int ok_other, int no_other) {
  object_.SetOkNoParams(ok_other, no_other);
}

void ControllerDeposit::SetMonthQuartAnnualRep(double monthly_rep_other,
                                               double quarterly_rep_other,
                                               double annual_rep_other) {
  object_.SetMonthQuartAnnualRep(monthly_rep_other, quarterly_rep_other,
                                 annual_rep_other);
}
void ControllerDeposit::SetSumNumSn(double num_sn_other, double sum_sn_other) {
  object_.SetSumNumSn(num_sn_other, sum_sn_other);
}

double ControllerDeposit::GetSumEnd(double res_percent, double sum_value,
                                    double time_value) {
  double result = object_.GetSumEnd(res_percent, sum_value, time_value);
  return result;
}

double ControllerDeposit::GetTax(double res_percent, double time_value,
                                 double percent_nal_value) {
  double result = object_.GetTax(res_percent, time_value, percent_nal_value);
  return result;
}
}  // namespace s21