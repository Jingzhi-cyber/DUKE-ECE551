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
  const long number;

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

class OperationExpr : public Expression {
 private:
  Expression * lhs;
  Expression * rhs;
  char operation;

 public:
  OperationExpr() : lhs(NULL), rhs(NULL), operation(0) {}
  OperationExpr(Expression * newLhs, Expression * newRhs, char newOperation) :
      lhs(newLhs), rhs(newRhs), operation(newOperation) {}
  virtual ~OperationExpr() {
    delete rhs;
    delete lhs;
  }

  virtual std::string toString() const {
    std::stringstream operationStringStream;
    operationStringStream << "(" << lhs->toString() << " " << operation << " "
                          << rhs->toString() << ")";

    return operationStringStream.str();
  }
};

class PlusExpression : public OperationExpr {
 public:
  PlusExpression(Expression * newLhs, Expression * newRhs) :
      OperationExpr(newLhs, newRhs, '+') {}
};

class MinusExpression : public OperationExpr {
 public:
  MinusExpression(Expression * newLhs, Expression * newRhs) :
      OperationExpr(newLhs, newRhs, '-') {}
};

class TimesExpression : public OperationExpr {
 public:
  TimesExpression(Expression * newLhs, Expression * newRhs) :
      OperationExpr(newLhs, newRhs, '*') {}
};

class DivExpression : public OperationExpr {
 public:
  DivExpression(Expression * newLhs, Expression * newRhs) :
      OperationExpr(newLhs, newRhs, '/') {}
};
