#include "calccredit.h"

#include "ui_calccredit.h"

CalcCredit::CalcCredit(QWidget *parent)
    : QWidget(parent), ui(new Ui::CalcCredit) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
  connect(ui->pushButton_calculate, SIGNAL(clicked()), this,
          SLOT(on_pushButton_calculate_clicked()));
}

CalcCredit::~CalcCredit() { delete ui; }

void CalcCredit::on_pushButton_clicked() {
  ui->textEdit_sum->setText("");
  ui->textEdit_time->setText("");
  ui->textEdit_percent->setText("");
  ui->label_answer->setText("");
  ui->comboBox_type->setCurrentIndex(0);
  ui->Calculation_option->setCurrentIndex(0);
  this->close();
  emit mainWindow();
}

void CalcCredit::on_pushButton_calculate_clicked() {
  QString sum = ui->textEdit_sum->toPlainText();
  QByteArray sum_8bit = sum.toLocal8Bit();
  char *sum_str = sum_8bit.data();
  int error_sum = 0;
  double sum_value = controller.GetX(sum_str, &error_sum);

  QString time = ui->textEdit_time->toPlainText();
  QByteArray time_8bit = time.toLocal8Bit();
  char *time_str = time_8bit.data();
  int error_time = 0;
  double time_value = controller.GetX(time_str, &error_time);

  QString percent = ui->textEdit_percent->toPlainText();
  QByteArray percent_8bit = percent.toLocal8Bit();
  char *percent_str = percent_8bit.data();
  int error_percent = 0;
  double percent_value = controller.GetX(percent_str, &error_percent);

  if ((error_sum == 1) || (error_time == 1) || (error_percent == 1) ||
      ((ui->radioButton->isChecked() == false) &&
       (ui->radioButton_2->isChecked() == false)) ||
      (sum_value <= 0) || (time_value <= 0) || (percent_value <= 0) ||
      (time_value - floor(time_value) != 0.0)) {
    ui->label_answer->setText("Calculation problem ψ(▼へ▼メ)～→");
  } else {
    double month_percent = percent_value / 1200.0;
    if (ui->radioButton_2->isChecked() == true) time_value *= 12;
    controller_credit.SetParametrs(sum_value, month_percent, time_value);
    if (ui->Calculation_option->currentText() == "Ежемесячный платёж") {
      if (ui->comboBox_type->currentText() == "Аннуитетные") {
        double month_pay = controller_credit.GetMonthPay();
        QString qstr = QString::number(month_pay, 'g', 15);
        ui->label_answer->setText(qstr);
      } else if (ui->comboBox_type->currentText() == "Дифференцированные") {
        double first_month_pay = controller_credit.GetFirstMonthPay();
        double last_month_pay = controller_credit.GetLastMonthPay();
        QString first_qstr = QString::number(first_month_pay, 'g', 15);
        QString last_qstr = QString::number(last_month_pay, 'g', 15);
        ui->label_answer->setText(first_qstr + " ... " + last_qstr);
      }
    } else if (ui->Calculation_option->currentText() ==
               "Переплата по кредиту") {
      double res = 0.0;
      if (ui->comboBox_type->currentText() == "Аннуитетные") {
        res = controller_credit.GetOverpaymentAnnuity();
      } else if (ui->comboBox_type->currentText() == "Дифференцированные") {
        res = controller_credit.GetOverpaymentDiff();
      }
      QString res_qstr = QString::number(res, 'g', 15);
      ui->label_answer->setText(res_qstr);
    } else if (ui->Calculation_option->currentText() == "Общая выплата") {
      double all_pay = 0.0;
      if (ui->comboBox_type->currentText() == "Аннуитетные") {
        all_pay = controller_credit.GetAllPayAnnuity();
      } else if (ui->comboBox_type->currentText() == "Дифференцированные") {
        all_pay = controller_credit.GetAllPayDiff();
      }
      QString all_pay_qstr = QString::number(all_pay, 'g', 15);
      ui->label_answer->setText(all_pay_qstr);
    }
  }
}
