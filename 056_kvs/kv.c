#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char ** getLinesInFile(FILE * file, size_t * linesNumber) {
  char ** linesInFile = malloc(sizeof(*linesInFile));

  size_t lineIndex = 0;

  linesInFile[lineIndex] = NULL;

  size_t n = 0;  //Initial size to be allocated in function "getline"

  while (getline(&linesInFile[lineIndex], &n, file) >= 0) {
    lineIndex++;
    linesInFile = realloc(linesInFile, (lineIndex + 1) * sizeof(*linesInFile));
    linesInFile[lineIndex] = NULL;
  }

  free(linesInFile[lineIndex]);

  *linesNumber = lineIndex;

  return linesInFile;
}

kvpair_t * getKVArray(char ** linesInFile, size_t linesNumber) {
  kvpair_t * kvArray;
  if (linesNumber == 0) {
    free(linesInFile);
    return NULL;
  }
  else {
    kvArray = malloc(linesNumber * sizeof(*kvArray));
  }
  for (size_t i = 0; i < linesNumber; i++) {
    char * firstEqualToEnd = strchr(linesInFile[i], '=');
    if (firstEqualToEnd == NULL) {
      fprintf(stderr,
              "Can not find equal sign in the given string! Line:%s  Line index:%zu\n",
              linesInFile[i],
              i);

      exit(EXIT_FAILURE);
    }
    size_t indexOfEqual = firstEqualToEnd - linesInFile[i];
    char * nextLineToEnd = strchr(linesInFile[i], '\n');
    size_t indexOfNextLine = nextLineToEnd - linesInFile[i];
    char * key = malloc((indexOfEqual + 1) * sizeof(*key));
    char * value = malloc((indexOfNextLine - indexOfEqual) * sizeof(*value));
    strncpy(key, linesInFile[i], indexOfEqual);
    strncpy(value, firstEqualToEnd + 1, indexOfNextLine - indexOfEqual - 1);
    key[indexOfEqual] = '\0';
    value[indexOfNextLine - indexOfEqual - 1] = '\0';
    kvArray[i].key = key;
    kvArray[i].value = value;
    free(linesInFile[i]);
  }

  free(linesInFile);

  return kvArray;
}

kvarray_t * readKVs(const char * fname) {
  FILE * file = fopen(fname, "r");
  if (file == NULL) {
    fprintf(stderr, "Can not open file: %s!\n", fname);
    exit(EXIT_FAILURE);
  }

  size_t linesNumber = 0;

  char ** linesInFile = getLinesInFile(file, &linesNumber);

  kvarray_t * currentArray;

  if (linesNumber == 0) {
    currentArray = malloc(sizeof(*currentArray));
  }
  else {
    currentArray = malloc(linesNumber * sizeof(*currentArray));
  }
  currentArray->kvArray = getKVArray(linesInFile, linesNumber);
  currentArray->kvNumber = linesNumber;

  if (fclose(file) != 0) {
    fprintf(stderr, "Can not close file: %s!\n", fname);
    exit(EXIT_FAILURE);
  }
  return currentArray;
}

void freeKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->kvNumber; i++) {
    free(pairs->kvArray[i].key);
    free(pairs->kvArray[i].value);
  }
  free(pairs->kvArray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  for (size_t i = 0; i < pairs->kvNumber; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvArray[i].key, pairs->kvArray[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  for (size_t i = 0; i < pairs->kvNumber; i++) {
    if ((strcmp(pairs->kvArray[i].key, key)) == 0) {
      return pairs->kvArray[i].value;
    }
  }

  return NULL;
}
