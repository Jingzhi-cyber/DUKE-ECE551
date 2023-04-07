/*
//Head-recursion

unsigned power(unsigned x, unsigned y) {
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
    return x * power(x, y - 1);
  }
}

*/

// Tail-recursion
unsigned power_helper(unsigned x, unsigned y, unsigned answer) {
  if (x == 0) {
    if (y == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
  else if (y == 0) {
    return answer;
  }
  else {
    answer = answer * x;
    return power_helper(x, y - 1, answer);
  }
}

unsigned power(unsigned x, unsigned y) {
  return power_helper(x, y, 1);
}
