#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void rotateMatrix(int matrix[10][10]) {
  int rotate_clockwise_90[10][10] = {0};

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      rotate_clockwise_90[i][j] = matrix[9 - j][i];
    }
  }

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      matrix[i][j] = rotate_clockwise_90[i][j];
    }
  }

  // I think there is a way to rotate the matrix with just one for loop
}

int main(int argc, char ** argv) {
  int matrix[10][10] = {{0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}, {0}};
  int c = 0;
  /*
  char row0[12];
  char row1[12];
  char row2[12];
  char row3[12];
  char row4[12];
  char row5[12];
  char row6[12];
  char row7[12];
  char row8[12];
  char row9[12];
  char * fileMatrix[10] = {row0, row1, row2, row3, row4, row5, row6, row7, row8, row9};
  */
  if (argc != 2) {
    fprintf(stderr, "Usage: rotateMatrix input.txt\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "Can not open file!\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  int j = 0;
  int count = 0;

  // Get the 10 * 10 matirx in the file
  while ((c = fgetc(f)) != EOF) {
    count++;

    if ((c != '\n') && (j < 10) && (i < 10)) {
      matrix[i][j] = c;
    }

    j++;

    if ((c == '\n') && (j != 11)) {
      fprintf(stderr, "The format of the matrix in the given file is wrong!\n");
      exit(EXIT_FAILURE);
    }

    if ((c == '\n') && (j == 11)) {
      i++;
      j = 0;
    }
  }

  if ((i != 10) || (j != 0) || count != 110) {
    fprintf(stderr, "There are more or less lines in the given file!\n");
    exit(EXIT_FAILURE);
  }

  /*
  for (int i = 0; i < 10; i++) {
    if (fgets(fileMatrix[i], 12, f) != NULL) {
      if ((fileMatrix[i][10] == '\n') && (fileMatrix[i][11] == '\0')) {
        for (int j = 0; j < 10; j++) {
          matrix[i][j] = fileMatrix[i][j];
        }
      }
      else {
        fprintf(stderr, "The format of the matirx in the file is wrong!\n");
        exit(EXIT_FAILURE);
      }
    }
    else {
      fprintf(stderr, "The format of the matrix in the file is wrong!\n");
      exit(EXIT_FAILURE);
    }
  }
  */

  // Rotate the captured martrix
  rotateMatrix(matrix);

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      fprintf(stdout, "%c", matrix[i][j]);
    }

    fprintf(stdout, "\n");
  }

  if (fclose(f) != 0) {
    fprintf(stderr, "Can not close file!\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
