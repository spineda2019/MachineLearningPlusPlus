#ifndef LIBMACHINELEARNING_INCLUDE_MATRIX_H
#define LIBMACHINELEARNING_INCLUDE_MATRIX_H

#include <iostream>
#include <vector>

#include "MatrixExceptions.h"

namespace tensor_math {
/**
 * @brief
 * @tparam T
 */
template <class T>
class Matrix {
 public:
  /**
   * @brief Initialize a matrix with a 2d vector
   * @param data The 2d Vector to be created
   */
  Matrix(const std::vector<std::vector<T>>& data)
      : rows_{(data[0]).size()}, columns_{data.size()}, data_{data} {
    size_t matrix_width = (this->data_[0]).size();

    for (const std::vector<T>& row : data) {
      if (row.size() != matrix_width) {
        throw BadDataConstructorException();
      }
    }
  }

  Matrix(const std::string& file_path);

  Matrix() : rows_{0}, columns_{0}, data_{std::vector<std::vector<T>>{}} {}

  /**
   * @brief Default Initializer of Matrix (fills with all 0s)
   * @param rows Number of rows in Matrix
   * @param cols Number of columns in Matrix
   */
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
