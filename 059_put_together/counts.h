#ifndef __COUNTS_H__
#define __COUNTS_H__
#include <stdio.h>
struct _one_count_t {
  char * value;
  size_t occurance;
};
typedef struct _one_count_t one_count_t;

struct _counts_t {
  one_count_t * countsArray;
  size_t countsNumber;
  size_t unknowNumber;
};
typedef struct _counts_t counts_t;

counts_t * createCounts(void);
void addCount(counts_t * c, const char * name);
void printCounts(counts_t * c, FILE * outFile);

void freeCounts(counts_t * c);

#endif
