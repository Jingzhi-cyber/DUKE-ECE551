#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

unsigned calculatePower(unsigned x, unsigned y) {
  if (x == 0) {
    if (y == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else if (y == 0) {
    return 1;
  }
  else {
    unsigned answer = 1;

    for (unsigned i = 1; i <= y; i++) {
      answer = answer * x;
    }

    return answer;
  }
}

void run_check(unsigned x, unsigned y) {
  unsigned your_ans = power(x, y);
  unsigned expected_ans = calculatePower(x, y);

  if (your_ans != expected_ans) {
    printf("ENCOUNTER REEOR! Your answer is %d. THe expected answer is %d.\n",
           your_ans,
           expected_ans);
    exit(EXIT_FAILURE);
  }
}

int main() {
  run_check(2, 3);
  run_check(4249000000, 1);
  run_check(1, 0);
  run_check(1, 3);
  run_check(0, -1);
  run_check(0, 0);
  run_check(1, 1);
  run_check(0, 2);
  run_check(-1, 0);

  return EXIT_SUCCESS;
}
