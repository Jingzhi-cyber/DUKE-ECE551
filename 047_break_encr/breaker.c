#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
/*
// function that gets how many letters are in the given file
size_t getLetterNum(FILE * f) {
  size_t num = 0;
  int c;

  if ((c = fgetc(f)) == EOF) {
    fprintf(stderr, "The file is empty!\n");
    exit(EXIT_FAILURE);
  }

  rewind(f);

  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      num++;
    }
  }

  if (num == 0) {
    fprintf(stderr, "There is no letters\n");
    exit(EXIT_FAILURE);
  }

  rewind(f);

  return num;
}

// function that turns the letters in the given file into a string
void getLetterString(FILE * f, int * letterArray) {
  int c;
  size_t i = 0;
  while (
      (c = fgetc(f)) !=
      EOF) {  // if you continue to use (c = fgetc(f)) != EOF, your program will never go into
    // the while loop, since fgetc(f) already equals to EOF in fucntion getletternum(f).
    // If you still want to use this function, you should close the file and then re-open it.
    if (isalpha(c)) {
      c = tolower(c);
      letterArray[i] = c;
      i++;
    }
  }

  //  if (i != size) {
  //  printf("The size for letterArray is wrong! Size = %ld, i = %ld\n", size, i);
  //  exit(EXIT_FAILURE);
  // }
}

// function that calculates how many times a letter occurs in an array
unsigned int calcFrequency(int * letterArray, size_t size, int letter) {
  unsigned frequency = 0;

  if (letterArray == NULL) {
    printf("Given array is null\n");
    exit(EXIT_FAILURE);
  }

  if (size < 0) {
    printf("Size can be less than 0!\n");
    exit(EXIT_FAILURE);
  }

  for (size_t i = 0; i < size; i++) {
    if (letterArray[i] == letter) {
      frequency++;
    }
  }

  return frequency;
}

// function that counts the frequency of each letter
void countFrequency(int * letterArray, size_t size, int * letterFrequency) {
  int c = 'a';
  for (size_t i = 0; i < 26; i++) {
    letterFrequency[i] = calcFrequency(letterArray, size, c);
    c++;
  }
}

*/

void countFrequency(int * array, FILE * f) {
  int c;
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      array[c - 'a']++;
    }
  }
}

size_t findMaxIndex(int * array, size_t size) {
  int max = array[0];
  size_t index = 0;

  for (size_t i = 1; i < size; i++) {
    if (array[i] > max) {
      max = array[i];
      index = i;
    }
  }

  return index;
}

unsigned getKey(size_t index) {
  int maxLetter = 'a' + index;

  if (maxLetter >= 'e') {
    return maxLetter - 'e';
  }
  else {
    return 26 - ('e' - maxLetter);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    exit(EXIT_FAILURE);
  }

  FILE * f = fopen(argv[1], "r");

  if (f == NULL) {
    fprintf(stderr, "Could not open %s!\n", argv[1]);
    exit(EXIT_FAILURE);
  }

  //size_t letterNum = getLetterNum(f);

  //int letterArray[letterNum];

  //  if (fclose(f) != 0) {
  //  fprintf(stderr, "Failed to close the input file!\n");
  //  exit(EXIT_FAILURE);
  // }

  //  f = fopen(argv[1], "r");

  // getLetterString(f, letterArray);

  int letterFrequency[26] = {0};
  countFrequency(letterFrequency, f);

  //  countFrequency(letterArray, letterNum, letterFrequency);

  size_t index = findMaxIndex(letterFrequency, 26);

  unsigned int key = getKey(index);

  // if ((key >= 0) && (key < 26)) {
  fprintf(stdout, "%d\n", key);

  if (fclose(f) != 0) {
    fprintf(stderr, "Failed to close the input file!\n");
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
  // }
  //  else {
  //  fprintf(stderr, "The key is not in the range 0 to 26 ! Key is %d\n", key);
  //  exit(EXIT_FAILURE);
  // }

  // return EXIT_SUCCESS;
}
