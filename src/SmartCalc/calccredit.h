#ifndef CALCCREDIT_H
#define CALCCREDIT_H

#include <QWidget>

#include "../controller/controller_calculator.h"
#include "../controller/controller_credit.h"

namespace Ui {
class CalcCredit;
}

class CalcCredit : public QWidget {
  Q_OBJECT

 public:
  explicit CalcCredit(QWidget *parent = nullptr);
  ~CalcCredit();

 private slots:
  void on_pushButton_clicked();

  void on_pushButton_calculate_clicked();

 private:
  Ui::CalcCredit *ui;
  s21::CalculatorController controller;
  s21::ControllerCredit controller_credit;

 signals:
  void mainWindow();
};

#endif  // CALCCREDIT_H
