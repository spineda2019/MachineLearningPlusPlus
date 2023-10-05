#ifndef LIBMACHINELEARNING_INCLUDE_MATRIX_H
#define LIBMACHINELEARNING_INCLUDE_MATRIX_H

#include <vector>
#include <iostream>

namespace tensor_math {
template <class T>
class Matrix {
 public:
  Matrix(const std::vector<std::vector<T>>& data);

  Matrix(const std::string& file_path);

  Matrix() : rows_{0}, columns_{0}, data_{std::vector<std::vector<T>>{}} {}

  size_t GetRows() { return this->rows_; }

  friend std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix);

 private:
  size_t rows_;
  size_t columns_;
  std::vector<std::vector<T>> data_;  // vector of rows
};

template <class T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& matrix) {
  // write obj to stream
  for (size_t row = 0; row < matrix.rows_; row++) {
    for (size_t col = 0; col < matrix.columns_; col++) {
      os << matrix.data_[row][col] << ", ";
    }
    os << std::endl;
  }

  return os;
}

}  // namespace tensor_math

#endif  // LIBMACHINELEARNING_INCLUDE_MATRIX_H
