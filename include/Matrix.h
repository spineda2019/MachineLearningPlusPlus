#ifndef LIBMACHINELEARNING_INCLUDE_MATRIX_H
#define LIBMACHINELEARNING_INCLUDE_MATRIX_H

#include <algorithm>
#include <execution>
#include <iostream>
#include <numeric>
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
      : rows_{data.size()}, columns_{(data[0]).size()}, data_{data} {
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

  size_t GetRows() const { return this->rows_; }

  /**
   * @brief
   * @return
   */
  Matrix<T> SubSquareMatrix(size_t column) const {
    // Matrix must be a square
    if (this->rows_ != this->columns_) {
      throw InvalidDeterminantException();
    }

    std::vector<std::vector<T>> sub_data(this->rows_ - 1,
                                         std::vector<T>(this->columns_ - 1));

    // naive implementation now, look to optimize...
    for (size_t row = 1; row < this->rows_; row++) {
      for (size_t col = 0; col < this->columns_; col++) {
        if (col == column) {
          continue;
        } else if (col < column) {
          sub_data[row - 1][col] =
              this->data_[row][col];
        } else {
          sub_data[row - 1][col - 1] =
              this->data_[row][col];
        }
      }
    }

    return Matrix(sub_data);
  }

  /**
   * @brief
   * @return
   */
  T Det_Dep() const {
    // TODO: Evaluate return type (T vs double)
    // DEPCRECATE: Using Laplace Extension is O(n!)

    // Matrix must be a square
    if (this->rows_ != this->columns_) {
      throw InvalidDeterminantException();
    }

    // special case 2x2
    if (this->rows_ == 2) {
      return ((this->data_[0][0]) * (this->data_[1][1])) -
             ((this->data_[0][1]) * (this->data_[1][0]));
    } else {
      // sum of Sub(0).Det() Sub(1).Det() etc
      T det = static_cast<T>(0);
      for (size_t col = 0; col < this->columns_; col++) {
        T sub_det = this->SubSquareMatrix(col).Det();
        det += sub_det * ((col % 2 == 0 ? 1 : -1) * this->data_[0][col]);
      }
      return det;
    }
  }

  T Det() const {
    // TODO: Use LU Decomposition
  }

  template <class M>
  friend std::ostream& operator<<(std::ostream& os, const Matrix<M>& matrix);

  template <class T>
  friend Matrix<T> operator*(float x, const Matrix<T>& y);

  template <class T>
  friend Matrix<T> operator*(const Matrix<T>& x, float y);

  template <class T>
  friend Matrix<T> operator*(const Matrix<T>& x, const Matrix<T>& y);

  template <class T>
  friend Matrix<T> operator+(const Matrix<T>& x, const Matrix<T>& y);

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

template <class T>
Matrix<T> operator*(const Matrix<T>& x, const Matrix<T>& y) {
  if (x.data_[0].size() != y.data_.size()) {
    throw MatrixMultiplicationMismatchException();
  }

  size_t rows = x.data_.size();
  size_t columns = y.data_[0].size();

  std::vector<std::vector<T>> result(rows, std::vector<T>(columns));

  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < columns; j++) {
      std::vector<T> temp_column(rows);

      // Potential #if _HAS_CXX_20
      std::transform(y.data_.begin(), y.data_.end(), temp_column.begin(),
                     [j](const std::vector<T>& y_row) { return y_row[j]; });

      result[i][j] = std::inner_product(x.data_[i].begin(), x.data_[i].end(),
                                        temp_column.begin(), 0);
    }
  }

  return Matrix(result);
}

template <class T>
Matrix<T> operator+(const Matrix<T>& x, const Matrix<T>& y) {
  size_t x_rows = x.data_.size();
  size_t x_cols = x.data_[0].size();

  size_t y_rows = y.data_.size();
  size_t y_cols = y.data_[0].size();

  if ((x_rows != y_rows) || (x_cols != y_cols)) {
    throw MatrixAdditionMismatchException();
  }

  std::vector<std::vector<T>> result(x_rows, std::vector<int>(x_cols));

  size_t index;

  for (size_t row = 0; row < x_rows; row++) {
    index = 0;
    std::transform(x.data_[row].begin(), x.data_[row].end(),
                   result[row].begin(), [&index, &y, &row](T element) {
                     index++;
                     return element + y.data_[row][index - 1];
                   });
  }

  return Matrix(result);
}

}  // namespace tensor_math

#endif  // LIBMACHINELEARNING_INCLUDE_MATRIX_H
