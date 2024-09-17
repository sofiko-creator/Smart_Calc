#include "mainwindow.h"

#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_minus, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_mod, SIGNAL(clicked()), this,
          SLOT(processing_numbers_and_operations()));
  connect(ui->pushButton_del_sym, SIGNAL(clicked()), this,
          SLOT(processing_del_sym()));
  connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(processing_dot()));

  connect(ui->pushButton_AC, SIGNAL(clicked()), this, SLOT(processing_AC()));

  connect(ui->pushButton_bracket1, SIGNAL(clicked()), this,
          SLOT(processing_brackets()));
  connect(ui->pushButton_bracket2, SIGNAL(clicked()), this,
          SLOT(processing_brackets()));

  connect(ui->pushButton_cos, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_sin, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,
          SLOT(processing_functions()));

  connect(ui->pushButton_ln, SIGNAL(clicked()), this,
          SLOT(processing_functions()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this,
          SLOT(processing_functions()));

  connect(ui->pushButton_Graph, SIGNAL(clicked()), this,
          SLOT(processing_Graph()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(processing_x()));

  connect(ui->pushButton_equal, SIGNAL(clicked()), this,
          SLOT(processing_equal()));

  credit_calc_ptr = new CalcCredit();
  connect(credit_calc_ptr, &CalcCredit::mainWindow, this, &MainWindow::show);

  deposit_calc_ptr = new CalcDeposit();
  connect(deposit_calc_ptr, &CalcDeposit::mainWindow, this, &MainWindow::show);
}
MainWindow::~MainWindow() { delete ui; }

void MainWindow::processing_equal() {
  QString old_label = ui->label->text();
  std::string str = old_label.toStdString();
  long double value_x = 0.0;
  int error_x = 0, empty_x = 0;
  if (old_label.contains('x')) {
    QDialog dialog(this);
    dialog.setWindowTitle("Введите значение x");
    dialog.resize(300, 20);
    QVBoxLayout layout(&dialog);
    QLineEdit edit(&dialog);
    layout.addWidget(&edit);
    QPushButton button("OK", &dialog);
    layout.addWidget(&button);
    connect(&button, &QPushButton::clicked, &dialog, &QDialog::accept);
    if (dialog.exec() == QDialog::Accepted) {
      QString x_qstr = edit.text();
      std::string x_str = x_qstr.toStdString();
      value_x = controller.GetX(x_str, &error_x);
    } else {
      empty_x = 1;
    }
  }
  controller.SetExpression(str, value_x);
  controller.Calculate();
  int error = controller.GetStatus();
  if ((error == 0) || (error_x == 1) || (str[0] == '\0')) {
    ui->label->setText("ERROR");
  } else if (empty_x == 0) {
    long double output = controller.GetResult();
    QString qstr = QString::number(output, 'g', 15);
    ui->label->setText(qstr);
  }
}

void MainWindow::processing_x() {
  QPushButton *button = (QPushButton *)sender();
  QString update_label = ui->label->text();
  string str = update_label.toStdString();
  if (str[str.size() - 1] != '.') {
    ui->label->setText(ui->label->text() + button->text());
  }
}

void MainWindow::processing_Graph() {
  QString old_label = ui->label->text();
  std::string str = old_label.toStdString();
  int control = controller.GetStatusValidInput(str);
  if ((control == 0) || (str[0] == '\0')) {
    ui->label->setText("ERROR");
  } else {
    form.show();
    QLabel *blya = form.findChild<QLabel *>("label_fun");
    blya->setText(ui->label->text());
  }
}

void MainWindow::processing_functions() {
  QPushButton *button = (QPushButton *)sender();
  QString update_label = ui->label->text();
  string str = update_label.toStdString();
  if ((ui->label->text() != "0") && (str[str.size() - 1] != '.')) {
    ui->label->setText(ui->label->text() + button->text() + "(");
  } else if (ui->label->text() == "0") {
    ui->label->setText(button->text() + "(");
  }
}

void MainWindow::processing_brackets() {
  QPushButton *button = (QPushButton *)sender();
  QString update_label = ui->label->text();
  string str = update_label.toStdString();
  if ((ui->label->text() != "0") && (str[str.size() - 1] != '.')) {
    ui->label->setText(ui->label->text() + button->text());
  } else if (ui->label->text() == "0") {
    ui->label->setText(button->text());
  }
}

void MainWindow::processing_numbers_and_operations() {
  QPushButton *button = (QPushButton *)sender();

  QString update_label = ui->label->text();
  string str = update_label.toStdString();

  if ((button->text() != "+") && (button->text() != "-") &&
      (button->text() != "/") && (button->text() != "*") &&
      (ui->label->text() != "0") && (button->text() != "^") &&
      (button->text() != "mod")) {
    ui->label->setText(ui->label->text() + button->text());
  } else if (((button->text() == "+") || (button->text() == "-") ||
              (button->text() == "/") || (button->text() == "*") ||
              (button->text() == "^") || (button->text() == "mod")) &&
             (str[str.size() - 1] != '.')) {
    ui->label->setText(ui->label->text() + button->text());
  } else if (ui->label->text() == "0") {
    ui->label->setText(button->text());
  }
}

void MainWindow::processing_del_sym() {
  QString label;

  label = ui->label->text();
  string str = label.toStdString();
  if (!str.empty()) {
    if (str[str.size() - 1] == 'd') {
      str.erase(str.size() - 2);
    } else if (((str[str.size() - 1] == 'n') && (str[str.size() - 2] == 'a') &&
                (str[str.size() - 3] == 'n')) ||
               ((str[str.size() - 1] == 'f') && (str[str.size() - 2] == 'n') &&
                (str[str.size() - 3] == 'i'))) {
      str.erase(str.size() - 2);
    } else if ((str[str.size() - 1] == 'R') && (str[str.size() - 2] == 'O') &&
               (str[str.size() - 3] == 'R') && (str[str.size() - 4] == 'R') &&
               (str[str.size() - 5] == 'E')) {
      str.erase(str.size() - 4);
    } else if (str[str.size() - 1] == '(') {
      if (str[str.size() - 2] == '^') {
        str.erase(str.size() - 1);
      } else if ((str[str.size() - 2] == 'n') && (str[str.size() - 3] == 'l')) {
        str.erase(str.size() - 2);
      } else if ((str[str.size() - 2] == 't') || (str[str.size() - 5] == 'a')) {
        str.erase(str.size() - 4);
      } else if ((str[str.size() - 2] == 'g') ||
                 ((str[str.size() - 2] == 'n') &&
                  (str[str.size() - 3] == 'i') &&
                  (str[str.size() - 4] == 's')) ||
                 ((str[str.size() - 2] == 's') &&
                  (str[str.size() - 3] == 'o') &&
                  (str[str.size() - 4] == 'c')) ||
                 ((str[str.size() - 2] == 'n') &&
                  (str[str.size() - 3] == 'a') &&
                  (str[str.size() - 4] == 't'))) {
        str.erase(str.size() - 3);
      }
    }
    str.erase(str.size() - 1);
  }
  QString qstr = QString::fromStdString(str);
  ui->label->setText(qstr);
}

void MainWindow::processing_dot() {
  QString update_label = ui->label->text();
  string str = update_label.toStdString();
  int ind = -1;
  for (unsigned int i = 0; i < str.size(); i++) {
    if ((str[i] == '+') || (str[i] == '-') || (str[i] == '*') ||
        (str[i] == '/') || (str[i] == '^') || (str[i] == 'd')) {
      ind = i;
    }
  }
  if (ind != -1) {
    string str_temp;
    str_temp.resize(str.size() - ind);
    for (unsigned int i = ind + 1, j = 0; i < str.size(); i++, j++) {
      str_temp[j] = str[i];
    }
    QString qstr = QString::fromStdString(str_temp);
    if (!(qstr.contains('.')) && (str[str.size() - 1] != '+') &&
        (str[str.size() - 1] != '-') && (str[str.size() - 1] != '*') &&
        (str[str.size() - 1] != '/') && (str[str.size() - 1] != '^') &&
        (str[str.size() - 1] != 'd') && (str[str.size() - 1] != '(') &&
        (str[str.size() - 1] != ')') && (str[str.size() - 1] != 'x'))
      ui->label->setText(ui->label->text() + ".");
  } else if (ind == -1) {
    QString qstr = QString::fromStdString(str);
    if ((!(qstr.contains('.')) && (ui->label->text() != "") &&
         (str[str.size() - 1] != '(') && (str[str.size() - 1] != ')') &&
         (str[str.size() - 1] != 'x'))) {
      ui->label->setText(ui->label->text() + ".");
    }
  }
}

void MainWindow::processing_AC() { ui->label->setText("\0"); }

void MainWindow::on_pushButton_CreditCalc_clicked() {
  credit_calc_ptr->show();
  this->close();
}

void MainWindow::on_pushButton_DepositCalc_clicked() {
  deposit_calc_ptr->show();
  this->close();
}
