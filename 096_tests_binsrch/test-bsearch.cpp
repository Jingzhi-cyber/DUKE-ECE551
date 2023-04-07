#include <assert.h>
#include <math.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include "function.h"
using namespace std;
int binarySearchForZero(Function<int, int> * f, int low, int high);

class CountedIntFn : public Function<int, int> {
 protected:
  unsigned remaining;
  Function<int, int> * f;
  const char * mesg;

 public:
  CountedIntFn(unsigned n, Function<int, int> * fn, const char * m) :
      remaining(n), f(fn), mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr, "Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }
};

class SinFunction : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 10000000 * (sin(arg / 100000.0) - 0.5); }
};

class LinearFunc : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return arg; }
};

class ConstantFuncPos : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return 7; }
};

class ConstantFuncNeg : public Function<int, int> {
 public:
  virtual int invoke(int arg) { return -7; }
};

void check(Function<int, int> * f,
           int low,
           int high,
           int expected_ans,
           const char * mesg) {
  string lowS = to_string(low);
  string highS = to_string(high);
  string msg = "low " + lowS + " high " + highS;
  char * char_arr = &msg[0];

  int expected_count;

  if (high > low) {
    expected_count = log2(high - low) + 1;
  }
  else {
    expected_count = 1;
  }

  CountedIntFn cif(expected_count, f, char_arr);
  int ans = binarySearchForZero(&cif, low, high);
  if (ans != expected_ans) {
    std::cerr << "Incorrect " << mesg;
    exit(EXIT_FAILURE);
  }
}

void test() {
  SinFunction sf;
  string msg = "test for 0-150000";
  char * char_arr = &msg[0];
  check(&sf, 0, 150000, 52359, char_arr);
}

void test2() {
  LinearFunc sf;
  string msg = "negative to positive linear ";
  char * char_arr = &msg[0];
  check(&sf, -5, 5, 0, char_arr);
}

void test3() {
  LinearFunc sf;
  string msg = "0 range";
  char * char_arr = &msg[0];
  check(&sf, 0, 1, 0, char_arr);
}

void test4() {
  LinearFunc sf;
  string msg = "only pos";
  char * char_arr = &msg[0];
  check(&sf, 4, 150000, 4, char_arr);
}

void test5() {
  LinearFunc sf;
  string msg = "only neg";
  char * char_arr = &msg[0];
  check(&sf, -100, -1, -2, char_arr);
}

void test6() {
  LinearFunc sf;
  string msg = "neg pos uneven";
  char * char_arr = &msg[0];
  check(&sf, -1, 10, 0, char_arr);
}

void test7() {
  LinearFunc sf;
  string msg = "linear func";
  char * char_arr = &msg[0];
  check(&sf, -4, 0, -1, char_arr);
}

void test8() {
  LinearFunc sf;
  string msg = "only pos with big numbers";
  char * char_arr = &msg[0];
  //  check(&sf, -200000000, -10000000, -10000000, char_arr);
}

void test9() {
  ConstantFuncPos sf;
  string msg = "negative to positive constfuncpos";
  char * char_arr = &msg[0];
  check(&sf, -5, 5, -5, char_arr);
}

void test10() {
  ConstantFuncPos sf;
  string msg = "0 range";
  char * char_arr = &msg[0];
  check(&sf, 0, 1, 0, char_arr);
}

void test11() {
  ConstantFuncPos sf;
  string msg = "only pos";
  char * char_arr = &msg[0];
  check(&sf, 4, 150000, 4, char_arr);
}

void test12() {
  ConstantFuncPos sf;
  string msg = "only neg";
  char * char_arr = &msg[0];
  check(&sf, -100, -1, -100, char_arr);
}

void test13() {
  ConstantFuncPos sf;
  string msg = "neg pos uneven";
  char * char_arr = &msg[0];
  check(&sf, -1, 10, -1, char_arr);
}

void test14() {
  ConstantFuncNeg sf;
  string msg = "negative to positive constfuncpos";
  char * char_arr = &msg[0];
  check(&sf, -5, 5, 4, char_arr);
}

void test15() {
  ConstantFuncNeg sf;
  string msg = "0 range";
  char * char_arr = &msg[0];
  check(&sf, 0, 1, 0, char_arr);
}

void test16() {
  ConstantFuncNeg sf;
  string msg = "only pos";
  char * char_arr = &msg[0];
  check(&sf, 4, 150000, 149999, char_arr);
}

void test17() {
  ConstantFuncNeg sf;
  string msg = "only neg";
  char * char_arr = &msg[0];
  check(&sf, -100, -1, -2, char_arr);
}

void test18() {
  ConstantFuncNeg sf;
  string msg = "neg pos uneven";
  char * char_arr = &msg[0];
  check(&sf, -1, 10, 9, char_arr);
}

int main(void) {
  test();
  test2();
  test3();
  test4();
  test5();
  test6();
  test7();
  test8();
  test9();
  test10();
  test11();
  test12();
  test13();
  test14();
  test15();
  test16();
  test17();
  test18();
  return EXIT_SUCCESS;
}
