#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

int main() {
  int array0[] = {1, 2, 3, 4, 10, 9, 6, 0, 2, 4, 5};
  int array1[] = {-3, -3, -4, -5, 0, 0, 4, 5, 6, 6};
  int * array2 = NULL;
  int array3[] = {0, 0, 0, 0, 0, 0};
  int array4[] = {3, 4, 5, 2, 3};
  int array5[] = {'a', 'b'};
  int array6[] = {1, 2, 3, 3, 4, 5, 6, 7, 8};
  int array7[] = {-1, -2, -3, -4, -4, -5, -6, -7};
  int array8[] = {-8, -7, -6, -6, -5, -4, -3, -2, -1};
  int array9[] = {-1};
  int array10[] = {0, 1, -1};

  int * arrayTest[] = {array0,
                       array1,
                       array2,
                       array3,
                       array4,
                       array5,
                       array6,
                       array7,
                       array8,
                       array9,
                       array10};
  size_t arraySize[] = {11, 10, 0, 6, 5, 2, 9, 8, 9, 1, 3};
  size_t arrayExpected[] = {5, 4, 0, 1, 3, 2, 6, 1, 6, 1, 2};

  for (size_t i = 0; i < 11; i++) {
    size_t answer = maxSeq(arrayTest[i], arraySize[i]);

    if (answer != arrayExpected[i]) {
      printf("Your function fails to match the expected output!\n");
      printf(
          "Your result is %ld, the expected result is %ld\n ", answer, arrayExpected[i]);
      exit(EXIT_FAILURE);
    }
  }

  return EXIT_SUCCESS;
}
