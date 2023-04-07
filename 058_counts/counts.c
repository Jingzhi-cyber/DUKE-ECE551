#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  counts_t * counts = malloc(sizeof(*counts));
  counts->countsArray = NULL;
  counts->countsNumber = 0;
  counts->unknowNumber = 0;

  return counts;
}
void addCount(counts_t * c, const char * name) {
  if (name == NULL) {
    c->unknowNumber++;
    return;
  }

  for (size_t i = 0; i < c->countsNumber; i++) {
    if (strcmp(c->countsArray[i].value, name) == 0) {
      c->countsArray[i].occurance++;
      return;
    }
  }
  c->countsNumber++;
  c->countsArray = realloc(c->countsArray, c->countsNumber * sizeof(*c->countsArray));
  c->countsArray[c->countsNumber - 1].value =
      malloc((strlen(name) + 1) * sizeof(*c->countsArray[c->countsNumber - 1].value));
  strcpy(c->countsArray[c->countsNumber - 1].value, name);
  c->countsArray[c->countsNumber - 1].occurance = 1;
}

void printCounts(counts_t * c, FILE * outFile) {
  for (size_t i = 0; i < c->countsNumber; i++) {
    fprintf(outFile, "%s: %zu\n", c->countsArray[i].value, c->countsArray[i].occurance);
  }

  if (c->unknowNumber != 0) {
    fprintf(outFile, "<unknown> : %zu\n", c->unknowNumber);
  }
}

void freeCounts(counts_t * c) {
  for (size_t i = 0; i < c->countsNumber; i++) {
    free(c->countsArray[i].value);
  }
  free(c->countsArray);
  free(c);
}
