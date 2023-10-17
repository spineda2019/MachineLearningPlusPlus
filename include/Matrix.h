#ifndef LIBMACHINELEARNING_INCLUDE_MATRIX_H
#define LIBMACHINELEARNING_INCLUDE_MATRIX_H

#include <iostream>
#include <vector>

namespace tensor_math {
/**
 * @brief 
 * @tparam T 
*/
template <class T>
class Matrix {
 public:
  Matrix(const std::vector<std::vector<T>>& data);

  Matrix(const std::string& file_path);

  Matrix() : rows_{0}, columns_{0}, data_{std::vector<std::vector<T>>{}} {}

  Matrix(size_t rows, size_t cols)
      : rows_{rows},
        columns_{cols},
        data_{std::vector<std::vector<T>>(rows, std::vector<T>(cols, 0))} {}

  size_t GetRows() { return this->rows_; }

  template <class M>
  friend std::ostream& operator<<(std::ostream& os, const Matrix<M>& matrix);

 private:
  size_t rows_;
  size_t columns_;
  std::vector<std::vector<T>> data_;  // vector of rows
};

/**
 * @brief 
 * @tparam M 
 * @param os 
 * @param matrix 
 * @return 
*/
template <class M>
std::ostream& operator<<(std::ostream& os, const Matrix<M>& matrix) {
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
