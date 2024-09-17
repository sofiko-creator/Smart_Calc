#ifndef DEPOSIT_MODEL_H_
#define DEPOSIT_MODEL_H_
#include <math.h>

#include <iostream>

namespace s21 {
class DepositModel {
 public:
  DepositModel() = default;
  ~DepositModel() = default;
  double add_percent(double sum_value, double time_value, double percent_value,
                     bool flag);
  double add_percent_compound(double sum_value, double time_value,
                              double percent_value, bool flag);
  void SetAllParams(double monthly_rep_other, double quarterly_rep_other,
                    double annual_rep_other, double sum_sn_other, int ok_other,
                    int no_other);
  void SetOkNoParams(int ok_other, int no_other);
  void SetMonthQuartAnnualRep(double monthly_rep_other,
                              double quarterly_rep_other,
                              double annual_rep_other);
  void SetSumNumSn(double num_sn_other, double sum_sn_other);

  double GetSumEnd(double res_percent, double sum_value, double time_value);
  double GetTax(double res_percent, double time_value,
                double percent_nal_value);

 private:
  double max_ans_without_tax =
      1000000 * 15 / 100.0;  // с учётом ключевой ставки;
  double monthly_rep = 0.0;
  double quarterly_rep = 0.0;
  double annual_rep = 0.0;
  double sum_sn = 0.0;
  int ok = 0;
  int no = 0;
  double num_sn = -100;
};
}  // namespace s21

#endif