#ifndef MEMBERS_H_
#define MEMBERS_H_
#include <algorithm>  // Для std::copy
#include <cstring>    // Для std::strlen
#include <string>

namespace s21 {
class Members {
 private:
  double value;
  int priority;
  char operation_name[5];
  int type;  // тип данных

 public:
  // Конструкторы
  Members() : value(0.0), priority(0), type(0) {
    std::fill(std::begin(operation_name), std::end(operation_name), '\0');
  }

  Members(double val, int prio, const char* op_name, int tp)
      : value(val), priority(prio), type(tp) {
    setOperationName(op_name);
  }

  // Деструктор
  ~Members() {}

  // Сеттеры
  void setValue(double val) { value = val; }
  void setPriority(int prio) { priority = prio; }
  void setOperationName(const char* op_name) {
    std::size_t len =
        std::min(std::strlen(op_name), sizeof(operation_name) - 1);
    std::copy(op_name, op_name + len, operation_name);
    operation_name[len] = '\0';
  }
  void setType(int tp) { type = tp; }

  // Геттеры
  double getValue() const { return value; }
  int getPriority() const { return priority; }
  const char* getOperationName() const { return operation_name; }
  int getType() const { return type; }
};  // Members
}  // namespace s21
#endif