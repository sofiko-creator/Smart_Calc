#ifndef FORM_H
#define FORM_H

#include <qcustomplot.h>

#include <QPainter>
#include <QVector>
#include <QWidget>

#include "../controller/controller_calculator.h"
#define S21_NAN 0.0 / 0.0

namespace Ui {
class Form;
}

class Form : public QWidget {
  Q_OBJECT

 public:
  explicit Form(QWidget *parent = nullptr);
  ~Form();

 private slots:
  void on_pushButton_clicked();

 private:
  Ui::Form *ui;
  double xBegin, xEnd, step, X, yBegin, yEnd;
  QVector<double> x, y;
  void choose_step(double *step, double xBegin, double xEnd);
  s21::CalculatorController controller;
};

#endif  // FORM_H
