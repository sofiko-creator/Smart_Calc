#include "form.h"

#include "ui_form.h"

Form::Form(QWidget *parent) : QWidget(parent), ui(new Ui::Form) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
}

Form::~Form() { delete ui; }

void Form::on_pushButton_clicked() {
  ui->widget->clearGraphs();
  QString x_min = ui->textEdit_x_min->toPlainText();
  std::string x_min_str = x_min.toStdString();
  int error_x_min = 0;
  xBegin = controller.GetX(x_min_str, &error_x_min);

  QString x_max = ui->textEdit_x_max->toPlainText();
  std::string x_max_str = x_max.toStdString();
  int error_x_max = 0;
  xEnd = controller.GetX(x_max_str, &error_x_max);

  QString y_min = ui->textEdit_y_min->toPlainText();
  std::string y_min_str = y_min.toStdString();
  int error_y_min = 0;
  yBegin = controller.GetX(y_min_str, &error_y_min);

  QString y_max = ui->textEdit_y_max->toPlainText();
  std::string y_max_str = y_max.toStdString();
  int error_y_max = 0;
  yEnd = controller.GetX(y_max_str, &error_y_max);

  if ((error_x_min == 1) || (error_x_max == 1) || (error_y_min == 1) ||
      (error_y_max == 1) || (xBegin == xEnd) || (yBegin == yEnd)) {
    ui->label_msg->setText("Incorrect value (ﾉಥ益ಥ)ﾉ");
  } else {
    ui->label_msg->setText("The graph is built (ﾉ◕ヮ◕)ﾉ*:･ﾟ✧");
    if (xBegin < -1000000) {
      xBegin = -1000000;
    } else if (yBegin < -1000000) {
      yBegin = -1000000;
    } else if (xEnd > 1000000) {
      xEnd = 1000000;
    } else if (yEnd > 1000000) {
      yEnd = 1000000;
    }
    ui->widget->xAxis->setRange(xBegin, xEnd);
    ui->widget->yAxis->setRange(yBegin, yEnd);

    choose_step(&step, xBegin, xEnd);

    QString old_label = ui->label_fun->text();
    QByteArray arr_8bit = old_label.toLocal8Bit();
    char *str = arr_8bit.data();

    for (X = xBegin; X <= xEnd; X += step) {
      x.push_back(X);
      long double result = 0.0;
      long double value_x = X;
      controller.SetExpression(str, value_x);
      controller.Calculate();
      result = controller.GetResult();
      if ((result >= yBegin) && (result <= yEnd)) {
        y.push_back(result);
      } else {
        y.push_back(S21_NAN);
      }
    }
    ui->widget->addGraph();
    ui->widget->graph(0)->addData(x, y);
    ui->widget->replot();
    x.clear();
    y.clear();
  }
}

void Form::choose_step(double *step, double xBegin, double xEnd) {
  if (xEnd - xBegin <= 10)
    *step = 0.00001;
  else if (xEnd - xBegin <= 100)
    *step = 0.0001;
  else if (xEnd - xBegin <= 1000)
    *step = 0.001;
  else if (xEnd - xBegin <= 10000)
    *step = 0.01;
  else if (xEnd - xBegin <= 100000)
    *step = 0.1;
  else if (xEnd - xBegin > 100000)
    *step = 0.5;
}