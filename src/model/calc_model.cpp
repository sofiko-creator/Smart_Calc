#include "calc_model.h"
namespace s21 {

void CalculatorModel::Calculate() {
  if (valid_input(input_str) == kOk) {
    status_ = kOk;
    convert_to_stack(input_str);
    convert_to_RPN();
    result_ = get_answer();
  } else {
    status_ = kError;
  }
}

long double CalculatorModel::get_x(std::string str, int* error) noexcept {
  int count_dot = 0, flag_fraction = 0, fraction_count = 0, flag_minus = 0,
      flag_empty = 0, flag_empty_after_dot = 0;
  long double res = 0.0;
  if (str[0] == '-') {
    flag_minus = 1;
  }
  int i = 0;
  if (flag_minus == 1) {
    i++;
  }
  for (; str[i] != '\0'; i++) {
    if ((str[i] != '.') && ((str[i] < '0') || (str[i] > '9'))) {
      *error = 1;
      break;
    } else if (str[i] == '.') {
      flag_fraction = 1;
      count_dot++;
      if (count_dot == 2) {
        *error = 1;
        break;
      }
    } else if (flag_fraction == 0) {
      res = res * 10 + (str[i] - '0');
    } else {
      flag_empty_after_dot = 1;
      fraction_count++;
      double temp = str[i] - '0';
      temp /= pow(10, fraction_count);
      res += temp;
    }
    flag_empty = 1;
  }
  if (flag_minus == 1) {
    res *= -1;
  }
  if ((flag_empty == 0) ||
      ((flag_fraction == 1) && (flag_empty_after_dot == 0))) {
    *error = 1;
  }
  return res;
}

int CalculatorModel::valid_input(std::string input) {
  int out_value = 1;
  int count_bracket = 0;
  for (int i = 0; input[i] != '\0'; i++) {
    if (((i >= 2) && (((input[i] == 'n') && (input[i - 1] == 'a') &&
                       (input[i - 2] == 'n')) ||
                      ((input[i] == 'f') && (input[i - 1] == 'n') &&
                       (input[i - 2] == 'i')))) ||
        ((i >= 4) &&
         ((input[i] == 'R') && (input[i - 1] == 'O') && (input[i - 2] == 'R') &&
          (input[i - 3] == 'R') && (input[i - 4] == 'E')))) {
      out_value = 0;
    } else if (input[i] == 'x') {
      if (((input[i + 1] <= '9') && (input[i + 1] >= '0')) ||
          ((i >= 1) && ((input[i - 1] <= '9') && (input[i - 1] >= '0'))) ||
          ((i >= 1) && (input[i - 1] == 'x')) || (input[i + 1] == 'x') ||
          ((i >= 1) && (input[i - 1] == ')'))) {
        out_value = 0;
      }
    } else if (input[i] == '(') {
      count_bracket++;
    } else if (input[i] == ')') {
      count_bracket--;
    } else if ((input[i] == '*') || (input[i] == '/') || (input[i] == '^')) {
      if ((i == 0) || (input[i + 1] == '\0') ||
          ((i >= 1) && ((input[i - 1] < '0') || (input[i - 1] > '9')) &&
           (input[i - 1] != ')') && (input[i - 1] != 'x')) ||
          (((input[i + 1] < '0') || (input[i + 1] > '9')) &&
           (input[i + 1] != '(') && (input[i + 1] != 'x') &&
           ((input[i + 1] != 'a') && (input[i + 1] != 's') &&
            (input[i + 1] != 'l') && (input[i + 1] != 't') &&
            (input[i + 1] != 'c')))) {
        out_value = 0;
      }
    } else if ((input[i] == '-') || (input[i] == '+')) {
      if ((((input[i + 1] < '0') || (input[i + 1] > '9')) &&
           (input[i + 1] != '(') && (input[i + 1] != 'x') &&
           ((input[i + 1] != 'a') && (input[i + 1] != 's') &&
            (input[i + 1] != 'l') && (input[i + 1] != 't') &&
            (input[i + 1] != 'c'))) ||
          (input[i + 1] == '\0')) {
        out_value = 0;
      }
    } else if ((i >= 2) && (input[i] == 'd') && (input[i - 1] == 'o') &&
               (input[i - 2] == 'm')) {
      if ((i - 2 == 0) || (input[i + 1] == '\0') ||
          (((input[i + 1] < '0') || (input[i + 1] > '9')) &&
           (input[i + 1] != '(') && (input[i + 1] != 'x')) ||
          ((i >= 3) && ((input[i - 3] < '0') || (input[i - 3] > '9')) &&
           (input[i - 3] != ')') && (input[i - 3] != 'x'))) {
        out_value = 0;
      }
    } else if ((input[i] == '.') && (input[i + 1] == '\0')) {
      out_value = 0;
    } else if ((input[i] <= '9') && (input[i] >= '0')) {
      if ((input[i + 1] == 'a') || (input[i + 1] == 's') ||
          (input[i + 1] == 'l') || (input[i + 1] == 't') ||
          (input[i + 1] == 'c') || (input[i + 1] == 'x') ||
          ((i >= 1) && (input[i - 1] == ')')) || (input[i + 1] == '(')) {
        out_value = 0;
      }
    }
    if (count_bracket < 0) {
      out_value = 0;
      break;
    }
  }
  if (count_bracket != 0) {
    out_value = 0;
  }
  int ind_brackets = 0;
  for (int i = 0; (input[i] != '\0') && (out_value == 1); i++) {
    if (input[i] == '(') {
      ind_brackets++;
    } else if (input[i] == ')') {
      if (ind_brackets == 1) {
        out_value = 0;
        break;
      } else
        ind_brackets = 0;
    } else if (ind_brackets >= 1)
      ind_brackets++;
  }

  return out_value;
}

void CalculatorModel::SetInputStr(const std::string input_str_set) noexcept {
  input_str = input_str_set;
}

void CalculatorModel::SetX(const long double x_set) noexcept { x_ = x_set; }

long double CalculatorModel::GetResult() const { return result_; }

enum Status CalculatorModel::GetStatus() const { return status_; }

long double CalculatorModel::convert_to_number(std::string input, int i,
                                               int* digitCount) {
  long double res = 0;
  int flag_fraction = 0;
  int inputCount = 0;
  for (int j = i;; j++) {
    if ((input[j] == '+') || (input[j] == '\0') || (input[j] == '-') ||
        (input[j] == '/') || (input[j] == '*') || (input[j] == '^') ||
        (input[j] == ')') || (input[j] == 'm')) {
      break;
    }
    if (input[j] == '.') {
      flag_fraction = 1;
      (*digitCount)++;
    } else if (flag_fraction == 0) {
      res = res * 10 + (input[j] - '0');
      (*digitCount)++;
    } else if ((flag_fraction == 1) && (input[j] != '.')) {
      inputCount++;
      long double temp = input[j] - '0';
      temp /= pow(10, inputCount);
      res = res + temp;
      (*digitCount)++;
    }
  }
  return res;
}

void CalculatorModel::add_value(double value) {
  stack_ptr.push(s21::Members(value, 0, "\0", 0));
}

void CalculatorModel::add_bracket_open() {
  stack_ptr.push(s21::Members(0.0, 0, "(\0", 3));
}

void CalculatorModel::add_bracket_close() {
  stack_ptr.push(s21::Members(0.0, 0, ")\0", 3));
}

void CalculatorModel::set_member(Members* obj_stack_ptr, double value,
                                 int type) {
  (*obj_stack_ptr).setValue(value);
  (*obj_stack_ptr).setType(type);
}

void CalculatorModel::convert_to_operation(std::string input, int i,
                                           Members* res) {
  int ind = 0;
  char arr_operation_name[5] = {'\0'};
  for (int j = i;; j++) {
    if ((strcmp(arr_operation_name, "+") == 0) ||
        (strcmp(arr_operation_name, "-") == 0)) {
      (*res).setPriority(1);
      break;
    } else if ((strcmp(arr_operation_name, "/") == 0) ||
               (strcmp(arr_operation_name, "*") == 0) ||
               (strcmp(arr_operation_name, "mod") == 0)) {
      (*res).setPriority(2);
      break;
    } else if (strcmp(arr_operation_name, "^") == 0) {
      (*res).setPriority(3);
      break;
    } else if ((strcmp(arr_operation_name, "cos") == 0) ||
               (strcmp(arr_operation_name, "acos") == 0) ||
               (strcmp(arr_operation_name, "sin") == 0) ||
               (strcmp(arr_operation_name, "asin") == 0) ||
               (strcmp(arr_operation_name, "tan") == 0) ||
               (strcmp(arr_operation_name, "atan") == 0) ||
               (strcmp(arr_operation_name, "ln") == 0) ||
               (strcmp(arr_operation_name, "log") == 0) ||
               (strcmp(arr_operation_name, "sqrt") == 0)) {
      (*res).setPriority(4);
      break;
    } else {
      arr_operation_name[ind] = input[j];
      ind++;
      arr_operation_name[ind] = '\0';
    }
  }
  (*res).setOperationName(arr_operation_name);
}

void CalculatorModel::convert_to_stack(std::string input) {
  int count = input.size();
  for (int i = 0; input[i] != '\0'; i++) {
    if ((input[i] >= '0') && (input[i] <= '9')) {
      int digit_count = 0;
      add_value(convert_to_number(input, i, &digit_count));
      i = i + digit_count - 1;
      continue;
    } else if (((input[i] == '-') || (input[i] == '+')) &&
               ((i <= count - 1) &&
                (((input[i + 1] >= '0') && (input[i + 1] <= '9')) ||
                 (input[i + 1] == 'x') || (input[i + 1] == 'a') ||
                 (input[i + 1] == 's') || (input[i + 1] == 'l') ||
                 (input[i + 1] == 't') || (input[i + 1] == 'c'))) &&
               (((i >= 1) && (input[i - 1] == '(')) || (i == 0))) {
      add_bracket_open();
      if (input[i] == '-') {
        add_value(-1.0);
      } else {
        add_value(1.0);
      }
      add_bracket_close();
      stack_ptr.push(s21::Members(0, 2, "*\0", 1));
      continue;
    } else if (input[i] == 'x') {
      add_value(x_);
      continue;
    } else if ((input[i] == '+') || (input[i] == '-') || (input[i] == '*') ||
               (input[i] == '/') || (input[i] == '^')) {
      Members tmp;
      convert_to_operation(input, i, &tmp);
      set_member(&tmp, 0, 1);  // знак операции
      stack_ptr.push(tmp);
      continue;
    } else if (((i <= count - 2) && (input[i + 2] == 'd') &&
                (input[i + 1] == 'o') && (input[i] == 'm')) ||
               ((i <= count - 2) && (input[i + 2] == 'n') &&
                (input[i + 1] == 'i') && (input[i] == 's')) ||
               ((i <= count - 2) && (input[i + 2] == 's') &&
                (input[i + 1] == 'o') && (input[i] == 'c')) ||
               ((i <= count - 2) && (input[i + 2] == 'n') &&
                (input[i + 1] == 'a') && (input[i] == 't')) ||
               ((i <= count - 2) && (input[i + 2] == 'g') &&
                (input[i + 1] == 'o') && (input[i] == 'l')) ||
               ((i <= count - 1) && (input[i] == 'l') &&
                (input[i + 1] == 'n'))) {
      Members tmp;
      convert_to_operation(input, i, &tmp);
      tmp.setType(0);
      if ((i <= count - 2) && (input[i + 2] == 'd') && (input[i + 1] == 'o') &&
          (input[i] == 'm')) {
        tmp.setType(1);  // знак операции
      }
      if (tmp.getType() == 0) tmp.setType(2);  // функция
      tmp.setValue(0);
      if ((i <= count - 1) && (input[i] == 'l') && (input[i + 1] == 'n'))
        i = i + 1;
      else
        i = i + 2;
      stack_ptr.push(tmp);
      continue;
    } else if (input[i] == '(') {
      add_bracket_open();
      continue;
    } else if (input[i] == ')') {
      add_bracket_close();
      continue;
    } else if (((i <= count - 3) && (input[i + 3] == 't') &&
                (input[i + 2] == 'r') && (input[i + 1] == 'q') &&
                (input[i] == 's')) ||
               ((i <= count - 3) && (input[i + 3] == 'n') &&
                (input[i + 2] == 'a') && (input[i + 1] == 't') &&
                (input[i] == 'a')) ||
               ((i <= count - 3) && (input[i + 3] == 'n') &&
                (input[i + 2] == 'i') && (input[i + 1] == 's') &&
                (input[i] == 'a')) ||
               ((i <= count - 3) && (input[i + 3] == 's') &&
                (input[i + 2] == 'o') && (input[i + 1] == 'c') &&
                (input[i] == 'a'))) {
      Members tmp;
      convert_to_operation(input, i, &tmp);
      set_member(&tmp, 0, 2);  // функция
      stack_ptr.push(tmp);
      i += 3;
      continue;
    }
  }
}

void CalculatorModel::convert_to_RPN() {
  std::stack<Members> support_stack;
  // Копирование элементов стека в другой стек для инвертирования порядка
  std::stack<Members> reverse_stack;
  while (!stack_ptr.empty()) {
    reverse_stack.push(stack_ptr.top());
    stack_ptr.pop();
  }

  // Обработка инвертированного стека
  while (!reverse_stack.empty()) {
    Members token = reverse_stack.top();
    reverse_stack.pop();

    if (token.getType() == 0) {  // Если это число
      output_queue.push(token);
    } else if (token.getType() == 1 ||
               token.getType() == 2) {  // Если это операция или функция
      while (!support_stack.empty() &&
             ((support_stack.top().getPriority() > token.getPriority()) ||
              (support_stack.top().getPriority() == token.getPriority() &&
               token.getOperationName()[0] != '^')) &&
             (support_stack.top().getType() !=
              3)) {  // Не обрабатываем скобки в стеке
        output_queue.push(support_stack.top());
        support_stack.pop();
      }
      support_stack.push(token);
    } else if (token.getType() == 3) {  // Если это скобки
      if (token.getOperationName()[0] == '(') {
        support_stack.push(token);
      } else if (token.getOperationName()[0] == ')') {
        while (!support_stack.empty() &&
               support_stack.top().getOperationName()[0] != '(') {
          output_queue.push(support_stack.top());
          support_stack.pop();
        }
        if (!support_stack.empty()) {  // Удаляем оставшуюся "("
          support_stack.pop();
        }
      }
    }
  }

  while (!support_stack.empty()) {
    output_queue.push(support_stack.top());
    support_stack.pop();
  }
}

long double CalculatorModel::get_answer() {
  std::stack<long double> temp_stack;

  while (!output_queue.empty()) {
    Members member = output_queue.front();
    output_queue.pop();

    if (member.getType() == 0) {  // Если это число
      temp_stack.push(member.getValue());
    } else if (member.getType() == 1) {  // Если это операция с двумя операндами
      long double val_2 = temp_stack.top();
      temp_stack.pop();
      long double val_1 = temp_stack.top();
      temp_stack.pop();

      long double result =
          calculate_two_value(val_1, val_2, member.getOperationName());
      temp_stack.push(result);
    } else if (member.getType() == 2) {  // Если это функция с одним операндом
      long double val_1 = temp_stack.top();
      temp_stack.pop();

      long double result =
          calculate_one_value(val_1, member.getOperationName());
      temp_stack.push(result);
    }
  }

  return temp_stack.top();  // Возвращаем результат
}

long double CalculatorModel::calculate_two_value(long double val_1,
                                                 long double val_2,
                                                 const char* str) {
  long double result = 0;
  if (!strcmp(str, "+")) {
    result = val_1 + val_2;
  } else if (!strcmp(str, "-")) {
    result = val_1 - val_2;
  } else if (!strcmp(str, "*")) {
    result = val_1 * val_2;
  } else if (!strcmp(str, "/")) {
    result = val_1 / val_2;
  } else if (!strcmp(str, "mod")) {
    result = fmod(val_1, val_2);
  } else if (!strcmp(str, "^")) {
    result = pow(val_1, val_2);
  }
  return result;
}

long double CalculatorModel::calculate_one_value(long double val_1,
                                                 const char* str) {
  long double result = 0;
  if (!strcmp(str, "sqrt")) {
    result = sqrt(val_1);
  } else if (!strcmp(str, "log")) {
    result = log10(val_1);
  } else if (!strcmp(str, "ln")) {
    result = log(val_1);
  } else if (!strcmp(str, "sin")) {
    result = sin(val_1);
  } else if (!strcmp(str, "asin")) {
    result = asin(val_1);
  } else if (!strcmp(str, "cos")) {
    result = cos(val_1);
  } else if (!strcmp(str, "acos")) {
    result = acos(val_1);
  } else if (!strcmp(str, "tan")) {
    result = tan(val_1);
  } else if (!strcmp(str, "atan")) {
    result = atan(val_1);
  }
  return result;
}

}  // namespace s21
