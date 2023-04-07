#include <cstdlib>
#include <iostream>
#include <string>

#include "function.h"

int binarySearchForZero(Function<int, int> * f, int low, int high) {
  if ((high - low) <= 1) {
    return low;
  }

  //while (high > low) {
  int mid = (high + low) / 2;
  int value = f->invoke(mid);
  if (value == 0) {
    return mid;
  }
  else if (value > 0) {
    //high = mid
    return binarySearchForZero(f, low, mid);
  }
  else {  // less than 0
    //low = mid;
    return binarySearchForZero(f, mid, high);
  }
  //}
  //if (low > 0) {
  //return low;
  //}
  //else {
  //return high - 1;
  //}
}
