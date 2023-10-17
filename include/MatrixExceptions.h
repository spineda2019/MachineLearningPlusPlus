#ifndef LIBMACHINELEARNING_INCLUDE_MATRIXEXCEPTIONS_H
#define LIBMACHINELEARNING_INCLUDE_MATRIXEXCEPTIONS_H

class BadDataConstructorException : std::exception {
 public:
  const char* what() {
    return "Bad Data passed in to constructor. Ensure all rows are of same "
           "size";
  }
};

#endif  // LIBMACHINELEARNING_INCLUDE_MATRIXEXCEPTIONS_H