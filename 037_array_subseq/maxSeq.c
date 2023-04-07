#include <stdio.h>
/*
struct _sequence {

  int * startPosition;
  size_t size;

};

typedef struct _sequence sequence;

sequence setSequence(int * startPosition, size_t size) {

  sequence thisSequence;
  thisSequence.startPosition = startPosition;
  thisSequence.size = size;

  return thisSequence;

}

sequence* findSequence (int * array, size_t n) {

  sequence sequence_0 = setSequence(array, 1);
  sequence arrayOfSequence[n] = {sequence_0};

}
*/

size_t countSequence(int * array, size_t size, size_t maxSize) {
  size_t sequenceSize = 1;

  if (size <= 1) {
    return maxSize;
  }

  for (size_t i = 1; i <= (size - 1); i++) {
    if (array[i] <= array[i - 1]) {
      break;
    }
    else {
      sequenceSize++;
    }
  }

  size -= sequenceSize;

  if (size > 0) {
    if (sequenceSize > maxSize) {
      return countSequence(array + sequenceSize, size, sequenceSize);
    }
    else {
      return countSequence(array + sequenceSize, size, maxSize);
    }
  }
  else {
    if (sequenceSize > maxSize) {
      return sequenceSize;
    }

    else {
      return maxSize;
    }
  }
}

size_t maxSeq(int * array, size_t n) {
  if ((n == 0) || (array == NULL)) {
    return 0;
  }

  return countSequence(array, n, 1);
}
