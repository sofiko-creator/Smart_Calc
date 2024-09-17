#include "calcdeposit.h"

#include <iostream>

#include "ui_calcdeposit.h"

CalcDeposit::CalcDeposit(QWidget *parent)
    : QWidget(parent), ui(new Ui::CalcDeposit) {
  ui->setupUi(this);
  connect(ui->pushButton, SIGNAL(clicked()), this,
          SLOT(on_pushButton_clicked()));
  connect(ui->pushButton_calc, SIGNAL(clicked()), this,
          SLOT(on_pushButton_calc_clicked()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(on_pushButton_popolnenie()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(on_pushButton_snyatie()));
  connect(ui->pushButton_yes, SIGNAL(clicked()), this,
          SLOT(on_pushButton_yes()));
  connect(ui->pushButton_no, SIGNAL(clicked()), this,
          SLOT(on_pushButton_no_clicked()));
}

CalcDeposit::~CalcDeposit() { delete ui; }

void CalcDeposit::on_pushButton_clicked() {
  controller_deposit.SetAllParams(0.0, 0.0, 0.0, 0.0, 0, 0);
  ui->textEdit_time->setText("");
  ui->textEdit_sum->setText("");
  ui->label_answer->setText("");
  ui->textEdit_percent->setText("");
  ui->textEdit_nal_percent->setText("");
  ui->Calculation_option_2->setCurrentIndex(0);
  ui->Calculation_option->setCurrentIndex(0);
  this->close();
  emit mainWindow();
}

void CalcDeposit::on_pushButton_popolnenie() {
  QDialog window(this);
  window.resize(300, 20);
  window.setWindowTitle("Введите пополнение");
  QVBoxLayout layout(&window);
  QLineEdit edit(&window);
  layout.addWidget(&edit);
  QPushButton button("OK", &window);
  QComboBox combo(&window);
  combo.addItem("Ежемесячно");
  combo.addItem("Ежеквартально");
  combo.addItem("Ежегодно");
  combo.setStyleSheet(
      "QComboBox { background-color: rgb(255, 190, 111); border-radius: 10px; "
      "}");
  layout.addWidget(&combo);
  button.setStyleSheet(
      "QPushButton { background-color:rgb(255, 190, 111); border-radius: 10px; "
      "} "
      "QPushButton:pressed { background-color: qlineargradient(x1: 0, y1: 0, "
      "x2: 0, y2: 1, stop: 0 #BEBEBE, stop: 1 #D7D7D7); }");
  layout.addWidget(&button);
  connect(&button, &QPushButton::clicked, &window, &QDialog::accept);

  if (window.exec() == QDialog::Accepted) {
    QString pop_qstr = edit.text();
    QByteArray pop_str_8bit = pop_qstr.toLocal8Bit();
    char *pop_str = pop_str_8bit.data();
    int error_pop = 0;
    double value_pop = controller.GetX(pop_str, &error_pop);
    if ((error_pop == 0) && (value_pop >= 0)) {
      if (combo.currentText() == "Ежемесячно") {
        controller_deposit.SetMonthQuartAnnualRep(value_pop, 0.0, 0.0);
        ui->label_answer->setText("Пополнение успешно ฅ(•ㅅ•❀)ฅ");
      } else if (combo.currentText() == "Ежеквартально") {
        controller_deposit.SetMonthQuartAnnualRep(0.0, value_pop, 0.0);
        ui->label_answer->setText("Пополнение успешно ฅ(•ㅅ•❀)ฅ");
      } else if (combo.currentText() == "Ежегодно") {
        controller_deposit.SetMonthQuartAnnualRep(0.0, 0.0, value_pop);
        ui->label_answer->setText("Пополнение успешно ฅ(•ㅅ•❀)ฅ");
      }
    } else
      ui->label_answer->setText("Ошибка пополнения (=ＴェＴ=)");
  }
}

void CalcDeposit::on_pushButton_snyatie() {
  QDialog dialog(this);
  dialog.resize(300, 20);
  dialog.setWindowTitle("Введите снятие");
  QVBoxLayout layout(&dialog);
  QLineEdit edit(&dialog);
  layout.addWidget(&edit);
  QPushButton button("OK", &dialog);
  button.setStyleSheet(
      "QPushButton { background-color:rgb(255, 190, 111); border-radius: 10px; "
      "} "
      "QPushButton:pressed { background-color: qlineargradient(x1: 0, y1: 0, "
      "x2: 0, y2: 1, stop: 0 #BEBEBE, stop: 1 #D7D7D7); }");
  layout.addWidget(&button);
  connect(&button, &QPushButton::clicked, &dialog, &QDialog::accept);

  if (dialog.exec() == QDialog::Accepted) {
    QString sn_qstr = edit.text();
    QByteArray sn_str_8bit = sn_qstr.toLocal8Bit();
    char *sn_str = sn_str_8bit.data();
    int error_sn = 0;
    double value_sn = controller.GetX(sn_str, &error_sn);
    if ((error_sn == 0) && (value_sn >= 0) &&
        ((ui->radioButton_month->isChecked() == true) ||
         (ui->radioButton_year->isChecked() == true))) {
      QString time = ui->textEdit_time->toPlainText();
      QByteArray time_8bit = time.toLocal8Bit();
      char *time_str = time_8bit.data();
      int error_time = 0;
      double time_value = controller.GetX(time_str, &error_time);
      QDialog dialog2(this);
      dialog2.resize(300, 20);
      dialog2.setWindowTitle("Введите номер периода снятия");
      QVBoxLayout layout(&dialog2);
      QLineEdit edit2(&dialog2);
      layout.addWidget(&edit2);
      QPushButton button2("OK", &dialog2);
      button2.setStyleSheet(
          "QPushButton { background-color:rgb(255, 190, 111); border-radius: "
          "10px; } "
          "QPushButton:pressed { background-color: qlineargradient(x1: 0, y1: "
          "0, "
          "x2: 0, y2: 1, stop: 0 #BEBEBE, stop: 1 #D7D7D7); }");
      layout.addWidget(&button2);
      connect(&button2, &QPushButton::clicked, &dialog2, &QDialog::accept);

      if (dialog2.exec() == QDialog::Accepted) {
        QString sn_qstr2 = edit2.text();
        QByteArray sn_str_8bit2 = sn_qstr2.toLocal8Bit();
        char *sn_str2 = sn_str_8bit2.data();
        int error_sn2 = 0;
        double value_sn2 = controller.GetX(sn_str2, &error_sn2);
        if ((error_sn2 == 0) && (value_sn2 - floor(value_sn2) == 0) &&
            (value_sn2 > 0) && (value_sn2 <= time_value)) {
          controller_deposit.SetSumNumSn(value_sn2, value_sn);
          ui->label_answer->setText("Снятие успешно ฅ(•ㅅ•❀)ฅ");
        } else
          ui->label_answer->setText("Неправильный номер периода");
      }
    } else
      ui->label_answer->setText("Ошибка снятия (=ＴェＴ=)");
  }
}

void CalcDeposit::on_pushButton_calc_clicked() {
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

  QString percent_nal = ui->textEdit_nal_percent->toPlainText();
  QByteArray percent_nal_8bit = percent_nal.toLocal8Bit();
  char *percent_nal_str = percent_nal_8bit.data();
  int error_nal_percent = 0;
  double percent_nal_value =
      controller.GetX(percent_nal_str, &error_nal_percent);
  if ((error_sum == 1) || (error_time == 1) || (error_percent == 1) ||
      (error_nal_percent == 1) ||
      ((ui->radioButton_month->isChecked() == false) &&
       (ui->radioButton_year->isChecked() == false)) ||
      ((ok == 0) && (no == 0)) || (sum_value <= 0) || (time_value <= 0) ||
      (percent_value <= 0) || (percent_nal_value <= 0) ||
      (time_value - floor(time_value) != 0.0)) {
    ui->label_answer->setText("Calculation problem ψ(▼へ▼メ)～→");
  } else {
    percent_value /= 100.0;
    percent_nal_value /= 100.0;
    if (ui->radioButton_year->isChecked() == true)
      time_value = time_value * 12.0;
    if (ui->Calculation_option->currentText() == "Начисленные проценты") {
      double res_percent = 0;
      if (no == 1) {
        bool flag = ui->radioButton_year->isChecked();
        res_percent = controller_deposit.add_percent(sum_value, time_value,
                                                     percent_value, flag);
      } else if (ok == 1) {
        bool flag = ui->radioButton_year->isChecked();
        res_percent = controller_deposit.add_percent_compound(
            sum_value, time_value, percent_value, flag);
      }
      res_percent = round(res_percent * 100.0) / 100.0;
      QString qstr = QString::number(res_percent, 'g', 15);
      ui->label_answer->setText(qstr);
    } else if (ui->Calculation_option->currentText() ==
               "Сумма на вкладе к концу срока") {
      double sum_end = 0, res_percent = 0;
      if (no == 1) {
        bool flag = ui->radioButton_year->isChecked();
        res_percent = controller_deposit.add_percent(sum_value, time_value,
                                                     percent_value, flag);
      } else if (ok == 1) {
        bool flag = ui->radioButton_year->isChecked();
        res_percent = controller_deposit.add_percent_compound(
            sum_value, time_value, percent_value, flag);
      }
      sum_end =
          controller_deposit.GetSumEnd(res_percent, sum_value, time_value);
      QString qstr = QString::number(sum_end, 'g', 15);
      ui->label_answer->setText(qstr);
    } else if (ui->Calculation_option->currentText() == "Сумма налога") {
      double tax = 0, res_percent = 0;
      if (no == 1) {
        bool flag = ui->radioButton_year->isChecked();
        res_percent = controller_deposit.add_percent(sum_value, time_value,
                                                     percent_value, flag);
      } else if (ok == 1) {
        bool flag = ui->radioButton_year->isChecked();
        res_percent = controller_deposit.add_percent_compound(
            sum_value, time_value, percent_value, flag);
      }
      time_value /= 12.0;
      tax =
          controller_deposit.GetTax(res_percent, time_value, percent_nal_value);
      QString qstr = QString::number(tax, 'g', 15);
      ui->label_answer->setText(qstr);
    }
  }
}

void CalcDeposit::on_pushButton_yes() {
  controller_deposit.SetOkNoParams(1, 0);
  ok = 1;
  no = 0;
  ui->label_answer->setText("Капитализация включена ฅ(•ㅅ•❀)ฅ");
}

void CalcDeposit::on_pushButton_no_clicked() {
  controller_deposit.SetOkNoParams(0, 1);
  ok = 0;
  no = 1;
  ui->label_answer->setText("Капитализация не установлена");
}
