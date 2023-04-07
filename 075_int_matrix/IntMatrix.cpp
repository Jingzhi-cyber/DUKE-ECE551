#include "IntMatrix.h"

#include "IntArray.h"

IntMatrix::IntMatrix() : numRows(0), numColumns(0), rows(NULL) {
}
IntMatrix::IntMatrix(int r, int c) : numRows(r), numColumns(c), rows(new IntArray *[r]) {
  for (int i = 0; i < r; i++) {
    this->rows[i] = new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs) :
    numRows(rhs.numRows), numColumns(rhs.numColumns), rows(new IntArray *[rhs.numRows]) {
  for (int i = 0; i < rhs.numRows; i++) {
    this->rows[i] = new IntArray(rhs.numColumns);
    *(this->rows[i]) = *(rhs.rows[i]);
    //    for (int j = 0; j < rhs.numColumns; j++) {
    //     this->rows[i][j] = rhs.rows[i][j];
    // }
  }
}
IntMatrix::~IntMatrix() {
  for (int i = 0; i < this->numRows; i++) {
    delete this->rows[i];
  }
  delete[] this->rows;
}
IntMatrix & IntMatrix::operator=(const IntMatrix & rhs) {
  if (this != &rhs) {
    IntArray ** temp = new IntArray *[rhs.numRows];
    for (int i = 0; i < rhs.numRows; i++) {
      temp[i] = new IntArray(rhs.numColumns);
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
int IntMatrix::getRows() const {
  return this->numRows;
}
int IntMatrix::getColumns() const {
  return this->numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert((index >= 0) && (index < this->numRows));
  return *(this->rows[index]);
}
IntArray & IntMatrix::operator[](int index) {
  assert((index >= 0) && (index < this->numRows));
  return *(this->rows[index]);
}

bool IntMatrix::operator==(const IntMatrix & rhs) const {
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

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert((this->numRows == rhs.numRows) && (this->numColumns == rhs.numColumns));
  IntMatrix ans = IntMatrix(this->numRows, this->numColumns);
  for (int i = 0; i < this->numRows; i++) {
    for (int j = 0; j < this->numColumns; j++) {
      ans[i][j] = (*this)[i][j] + rhs[i][j];
      // (*(ans->rows[i]))[j] = (*(this->rows[i]))[j] + (*(rhs.rows[i]))[j];
      //     ans->rows[i][j] = this->rows[i][j] + rhs.rows[i][j];
    }
  }

  return ans;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
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
