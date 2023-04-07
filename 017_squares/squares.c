int computeMax(int num1, int num2) {
  if (num1 >= num2) {
    return num1;
  }

  else {
    return num2;
  }
}

int checkBetween(int num, int left, int right) {
  if ((num >= left) && (num < right)) {
    return 1;
  }
  else {
    return 0;
  }
}

int checkEqual(int num1, int num2) {
  if (num1 == num2) {
    return 1;
  }
  else {
    return 0;
  }
}

int checkLess(int num1, int num2) {
  if (num1 < num2) {
    return 1;
  }
  else {
    return 0;
  }
}

void squares(int size1, int x_offset, int y_offset, int size2) {
  int w = computeMax(size1, x_offset + size2);
  int h = computeMax(size1, y_offset + size2);

  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      if (((checkBetween(x, x_offset, x_offset + size2)) &&
           ((checkEqual(y, y_offset)) || (checkEqual(y, y_offset + size2 - 1)))) ||
          ((checkBetween(y, y_offset, y_offset + size2)) &&
           ((checkEqual(x, x_offset)) || (checkEqual(x, x_offset + size2 - 1))))) {
        printf("*");
      }
      else {
        if (((checkLess(x, size1)) &&
             ((checkEqual(y, 0)) || (checkEqual(y, size1 - 1)))) ||
            ((checkLess(y, size1)) &&
             ((checkEqual(x, 0)) || (checkEqual(x, size1 - 1))))) {
          printf("#");
        }
        else {
          printf(" ");
        }
      }
    }

    printf("\n");
  }
  //compute the max of size1 and (x_offset + size2).  Call this w

  //compute the max of size1 and (y_offset + size2).  Call this h

  //count from 0 to h. Call the number you count with y

  //count from 0 to w. Call the number you count with x

  //check if  EITHER
  //    ((x is between x_offset  and x_offset +size2) AND
  //     y is equal to either y_offset OR y_offset + size2 - 1 )
  //  OR
  //    ((y is between y_offset and y_offset + size2) AND
  //     x is equal to either x_offset OR x_offset + size2 -1)
  // if so, print a *

  //if not,
  // check if EITHER
  //    x is less than size1 AND (y is either 0 or size1-1)
  // OR
  //    y is less than size1 AND (x is either 0 or size1-1)
  //if so, print a #

  //else print a space
  //when you finish counting x from 0 to w,
  //print a newline
}
