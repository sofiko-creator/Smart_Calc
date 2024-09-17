#ifndef CONTROLLER_DEPOSIT_H_
#define CONTROLLER_DEPOSIT_H_
#include "../model/deposit_model.h"

namespace s21 {
class ControllerDeposit {
 public:
  ControllerDeposit() = default;
  ~ControllerDeposit() = default;
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
  DepositModel object_;
};
}  // namespace s21
#endif