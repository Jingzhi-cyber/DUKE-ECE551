#include <sstream>
#include <string>

class Expression {
 public:
  Expression() {}
  virtual ~Expression() {}
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 private:
  long number;

 public:
  NumExpression() : number(0) {}
  explicit NumExpression(long num) : number(num) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream numStringStream;
    numStringStream << this->number;

    return numStringStream.str();
  }
};

class PlusExpression : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;

 public:
  PlusExpression() : lhs(NULL), rhs(NULL) {}
  PlusExpression(Expression * newLhs, Expression * newRhs) : lhs(newLhs), rhs(newRhs) {}
  virtual ~PlusExpression() {
    delete rhs;
    delete lhs;
  }
  virtual std::string toString() const {
    std::stringstream plusStringStream;
    plusStringStream << "(" << lhs->toString() << " + " << rhs->toString() << ")";

    return plusStringStream.str();
  }
};
