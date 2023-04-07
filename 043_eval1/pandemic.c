#include "pandemic.h"

#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function checks whether there is only one comma in the given string.
//Parameter line is a string to be checked.
//Parameter commaToEnd is a substring of line that starts where a comma fisrt occurs in line.
void checkLine1(char * line, char * commaToEnd) {
  if (commaToEnd == NULL) {
    fprintf(stderr, "Given string has no comma\n");
    exit(EXIT_FAILURE);
  }

  //Use strrchr to get the index of the last occurance of a comma in line.
  //If the condition is false, it means that there are at least 2 commas in line, which is invalid.
  if (commaToEnd != strrchr(line, ',')) {
    fprintf(stderr, "Given string has more than one comma!\n");
    exit(EXIT_FAILURE);
  }
}

//This function comes after checkline1. It checks whether the formats of name and population are correct.
//Parameter commaToEnd is a substring of line that starts where a comma first occurs in line.
//Parameter afterNumber is a substring of commaToEnd that holds all the characters after the digits.
//Parameter digits is the obtained population.
void checkLine2(char * commaToEnd,
                char * afterNumber,
                unsigned long long digits,
                size_t indexOfComma) {
  // Leaving one space for '\0' to add at the end of string name.
  if (indexOfComma > 63) {
    fprintf(stderr, "Given country name is too long to put in char name[64]");
    exit(EXIT_FAILURE);
  }

  if (commaToEnd[1] == '-') {
    fprintf(stderr,
            "Digits should come directly after the comma! You should not add - after the "
            "comma!\n");
    exit(EXIT_FAILURE);
  }

  if (afterNumber == (commaToEnd + 1)) {
    fprintf(stderr, "There is no digits after the comma!\n");
    exit(EXIT_FAILURE);
  }

  //  if (*afterNumber != '\n') {
  //  fprintf(stderr, "There should be only digits after the comma!\n");
  //  exit(EXIT_FAILURE);
  // }

  if ((digits == ULLONG_MAX) && (errno == ERANGE)) {
    fprintf(stderr, "An overflow occurs!\n");
    exit(EXIT_FAILURE);
  }
}

country_t parseLine(char * line) {
  size_t indexOfComma = 0;

  country_t ans;

  char * commaToEnd = strchr(line, ',');  // Find the first occurance of a comma.

  checkLine1(
      line,
      commaToEnd);  // Check whether there is only one comma in the given string: line.

  char * afterNumber;

  indexOfComma = commaToEnd - line;

  // Find the population after the comma.
  unsigned long long digits = strtoull(commaToEnd + 1, &afterNumber, 10);

  checkLine2(
      commaToEnd,
      afterNumber,
      digits,
      indexOfComma);  // Check whether the country name and population are in right formats.

  // Find the country name before the comma.
  for (size_t i = 0; i < indexOfComma; i++) {
    ans.name[i] = line[i];
  }

  ans.name[indexOfComma] = '\0';

  uint64_t population = digits;

  if (population > UINT64_MAX) {
    fprintf(stderr, "The population is too large to fit in uint64_t!\n");
    exit(EXIT_FAILURE);
  }

  ans.population = population;

  return ans;
}

// Calculate the arithmetic mean of seven days of daily case data in the given array.
double calcMeanOf7Data(unsigned * data) {
  unsigned sum = 0;

  for (size_t i = 0; i < 7; i++) {
    sum += data[i];
  }

  return (double)(sum / 7.0);
}

void calcRunningAvg(unsigned * data, size_t n_days, double * avg) {
  if (n_days < 7) {
    //    fprintf(stderr,
    //        "There are fewer than 7 days in the given data! Actual days is %zu\n",
    //        n_days);
    return;
  }
  // Use calcMeanOf7Data function to help calculate the mean of 7 days' data each time
  if (n_days >= 7) {
    for (size_t i = 0; i < (n_days - 6); i++) {
      avg[i] = calcMeanOf7Data(data + i);
    }
  }
}
void calcCumulative(unsigned * data, size_t n_days, uint64_t pop, double * cum) {
  if (n_days == 0) {
    return;
  }

  if (data == NULL) {
    fprintf(stderr, "There are no data in the given array!\n");
    exit(EXIT_FAILURE);
  }

  if (pop == 0) {
    fprintf(stderr,
            "The given population is 0! Can not calculate cumulative number of cases!\n");
    exit(EXIT_FAILURE);
  }

  double sum = 0;

  for (size_t i = 0; i < n_days; i++) {
    sum += data[i];

    cum[i] = sum / pop * 100000;
  }
}

//This function finds the maximum element in the given array and return its value.
//Parameter data is a string of unsigned int.
//Parameter n_days is the size of the given array.
unsigned calcMax(unsigned * data, size_t n_days) {
  unsigned max = data[0];

  for (size_t i = 1; i < n_days; i++) {
    if (data[i] > max) {
      max = data[i];
    }
  }

  return max;
}

void printCountryWithMax(country_t * countries,
                         size_t n_countries,
                         unsigned ** data,
                         size_t n_days) {
  if (n_countries == 0 || n_days == 0) {
    return;
  }

  if (countries == NULL && n_countries > 0) {
    fprintf(stderr, "There are no countries!\n");
    exit(EXIT_FAILURE);
  }

  if (data == NULL && n_days > 0) {
    fprintf(stderr, "There is no data!\n");
    exit(EXIT_FAILURE);
  }

  unsigned eachCountryMax[n_countries];
  //Use calcMax fucntion to put the maximum data of each country into the array eachCountryMax.
  for (size_t i = 0; i < n_countries; i++) {
    eachCountryMax[i] = calcMax(data[i], n_days);
  }

  unsigned max = eachCountryMax[0];
  size_t index = 0;
  //Compare each element in the array eachCountryMax, find the greatest one, and assign its value to max and get its index.
  for (size_t i = 1; i < n_countries; i++) {
    if (eachCountryMax[i] > max) {
      max = eachCountryMax[i];
      index = i;
    }
  }

  printf("%s has the most daily cases with %u\n", countries[index].name, max);
}
