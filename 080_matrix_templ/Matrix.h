#ifndef __T_MATRIX_H___
#define __T_MATRIX_H___

#include <assert.h>

#include <cstdlib>
#include <iostream>
#include <vector>

//YOUR CODE GOES HERE!
template<typename T>
class Matrix {
 private:
  int numRows;
  int numColumns;
  std::vector<T> ** rows;

 public:
  Matrix() : numRows(0), numColumns(0), rows(NULL) {}

  Matrix(int r, int c) : numRows(r), numColumns(c), rows(new std::vector<T> *[r]()) {
    for (int i = 0; i < r; i++) {
      this->rows[i] = new std::vector<T>(numColumns);
    }
  }

  Matrix(const Matrix & rhs) :
      numRows(rhs.numRows),
      numColumns(rhs.numColumns),
      rows(new std::vector<T> *[rhs.numRows]) {
    for (int i = 0; i < rhs.numRows; i++) {
      this->rows[i] = new std::vector<T>;
      *(this->rows[i]) = *(rhs.rows[i]);
      //    for (int j = 0; j < rhs.numColumns; j++) {
      //     this->rows[i][j] = rhs.rows[i][j];
      // }
    }
  }

  ~Matrix() {
    for (int i = 0; i < this->numRows; i++) {
      delete this->rows[i];
    }
    delete[] this->rows;
  }

  Matrix & operator=(const Matrix & rhs) {
    if (this != &rhs) {
      std::vector<T> ** temp = new std::vector<T> *[rhs.numRows];
      for (int i = 0; i < rhs.numRows; i++) {
        temp[i] = new std::vector<T>;
        *(temp[i]) = *(rhs.rows[i]);
        //      for (int j = 0; j < rhs.numColumns; j++) {
        //  temp[i][j] = rhs.rows[i][j];
        // }
        // delete this->rows[i];
      }

      delete[] this->rows;
      this->rows = temp;
      this->numRows = rhs.numRows;
      this->numColumns = rhs.numColumns;
    }

    return *this;
  }

  int getRows() const { return this->numRows; }

  int getColumns() const { return this->numColumns; }

  const std::vector<T> & operator[](int index) const {
    assert((index >= 0) && (index < this->numRows));
    return *(this->rows[index]);
  }

  std::vector<T> & operator[](int index) {
    assert((index >= 0) && (index < this->numRows));
    return *(this->rows[index]);
  }

  bool operator==(const Matrix & rhs) const {
    if ((this->numRows != rhs.numRows) || (this->numColumns != rhs.numColumns)) {
      return false;
    }

    for (int i = 0; i < numRows; i++) {
      if (*(this->rows[i]) != *(rhs.rows[i])) {
        //    for (int j = 0; j < numColumns; j++) {
        //  if (this->rows[i][j] != rhs.rows[i][j]) {
        return false;
      }
    }

    return true;
  }

  Matrix operator+(const Matrix & rhs) const {
    assert((this->numRows == rhs.numRows) && (this->numColumns == rhs.numColumns));
    Matrix ans = Matrix(this->numRows, this->numColumns);
    for (int i = 0; i < this->numRows; i++) {
      for (int j = 0; j < this->numColumns; j++) {
        ans[i][j] = (*this)[i][j] + rhs[i][j];
        // (*(ans->rows[i]))[j] = (*(this->rows[i]))[j] + (*(rhs.rows[i]))[j];
        //     ans->rows[i][j] = this->rows[i][j] + rhs.rows[i][j];
      }
    }

    return ans;
  }
};

template<typename T>
std::ostream & operator<<(std::ostream & s, const std::vector<T> & rhs) {
  if (rhs.size() == 0) {
    s << "{}";

    return s;
  }

  s << "{";

  for (size_t i = 0; i < rhs.size() - 1; i++) {
    s << rhs[i] << ", ";
  }

  s << rhs[rhs.size() - 1] << "}";

  return s;
}

template<
    typename T>  // when we use << to print Matrix<int> intMatrix, we do std::cout<< intMatrix
// So actually the type of intMatrix is Matrix<int>. And the compiler will know to pass int to T for
// the overloaded << operator for print Matrix<T>
std::ostream & operator<<(std::ostream & s, const Matrix<T> & rhs) {
  if (rhs.getRows() == 0) {
    s << "[  ]";

    return s;
  }

  s << "[ ";
  for (int i = 0; i < rhs.getRows() - 1; i++) {
    s << rhs[i] << ",\n";
  }

  s << rhs[rhs.getRows() - 1] << " ]";

  return s;
}

#endif
