#ifndef LIBMACHINELEARNING_INCLUDE_MATRIXEXCEPTIONS_H
#define LIBMACHINELEARNING_INCLUDE_MATRIXEXCEPTIONS_H

class BadDataConstructorException : std::exception {
 public:
  const char* what() {
    return "Bad Data passed in to constructor. Ensure all rows are of same "
           "size";
  }
};

class MatrixMultiplicationMismatchException : std::exception {
 public:
  const char* what() {
    return "Malformed matrix multiplication. Make sure matrices have "
           "compatible dimensions for multiplication";
  }
};

class MatrixAdditionMismatchException : std::exception {
 public:
  const char* what() {
    return "Malformed matrix Addition. Make sure matrices have same number of "
           "rows AND columns";
  }
};

class InvalidDeterminantException : std::exception {
 public:
  const char* what() { return "Matrix must be square to take its determinant"; }
};

class InvalidInversionException : std::exception {
 public:
  const char* what() { return "Matrix must be square to take its inverse"; }
};

class BadLUException : std::exception {
 public:
  const char* what() {
    return "Matrix must be square to take its LU decomposition";
  }
};

#endif  // LIBMACHINELEARNING_INCLUDE_MATRIXEXCEPTIONS_H