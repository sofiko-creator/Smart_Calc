#ifndef CALCDEPOSIT_H
#define CALCDEPOSIT_H

#include <QDialog>
#include <QGroupBox>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QWidget>

#include "../controller/controller_calculator.h"
#include "../controller/controller_deposit.h"

namespace Ui {
class CalcDeposit;
}

class CalcDeposit : public QWidget {
  Q_OBJECT

 public:
  explicit CalcDeposit(QWidget *parent = nullptr);
  ~CalcDeposit();

 private:
  Ui::CalcDeposit *ui;
  s21::CalculatorController controller;
  s21::ControllerDeposit controller_deposit;
  int ok = 0;
  int no = 0;

 signals:
  void mainWindow();
 private slots:
  void on_pushButton_clicked();
  void on_pushButton_popolnenie();
  void on_pushButton_snyatie();
  void on_pushButton_calc_clicked();
  void on_pushButton_yes();
  void on_pushButton_no_clicked();
};

#endif  // CALCDEPOSIT_H
