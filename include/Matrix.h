#ifndef LIBMACHINELEARNING_INCLUDE_MATRIX_H
#define LIBMACHINELEARNING_INCLUDE_MATRIX_H

#include <algorithm>
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

  template <class T>
  friend Matrix<T> operator*(float x, const Matrix<T>& y);

  template <class T>
  friend Matrix<T> operator*(const Matrix<T>& x, float y);

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
    if (row == 0) {
      os << std::endl;
    }
    for (size_t col = 0; col < matrix.columns_; col++) {
      if (col == 0) {
        os << "|";
      }

      os << matrix.data_[row][col];

      if (col != matrix.columns_ - 1) {
        os << ", ";
      } else {
        os << "|";
      }
    }
    os << std::endl;
  }

  return os;
}

template <class T>
Matrix<T> operator*(float x, const Matrix<T>& y) {
  std::vector<std::vector<T>> new_matrix_data(y.rows_,
                                              std::vector<T>(y.columns_));
  // potential parallel execution with
  // #if _HAS_CXX20
  for (size_t row = 0; row < y.data_.size(); row++) {
    std::transform(y.data_[row].begin(), y.data_[row].end(),
                   new_matrix_data[row].begin(),
                   [x](T entry) { return entry * static_cast<T>(x); });
  }

  return Matrix(new_matrix_data);
}

template <class T>
Matrix<T> operator*(const Matrix<T>& x, float y) {
  std::vector<std::vector<T>> new_matrix_data(x.rows_,
                                              std::vector<T>(x.columns_));
  // potential parallel execution with
  // #if _HAS_CXX20
  for (size_t row = 0; row < x.data_.size(); row++) {
    std::transform(x.data_[row].begin(), x.data_[row].end(),
                   new_matrix_data[row].begin(),
                   [y](T entry) { return entry * static_cast<T>(y); });
  }

  return Matrix(new_matrix_data);
}

}  // namespace tensor_math

#endif  // LIBMACHINELEARNING_INCLUDE_MATRIX_H
