#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <calccredit.h>
#include <calcdeposit.h>
#include <form.h>

#include <QDialog>
#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QVector>

#include "../controller/controller_calculator.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
  Form form;
  CalcCredit* credit_calc_ptr;
  CalcDeposit* deposit_calc_ptr;
  s21::CalculatorController controller;

 private slots:
  void processing_numbers_and_operations();
  void processing_del_sym();
  void processing_dot();
  void processing_AC();
  void processing_brackets();
  void processing_functions();
  void processing_Graph();
  void processing_x();
  void processing_equal();
  void on_pushButton_CreditCalc_clicked();
  void on_pushButton_DepositCalc_clicked();
};
#endif  // MAINWINDOW_H
