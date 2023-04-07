#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  FILE * file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "Can not open file: %s\n", filename);
    exit(EXIT_FAILURE);
  }
  counts_t * counts = createCounts();

  char ** keyArray = NULL;
  char * currentKey = NULL;
  size_t keyNumber = 0;
  size_t n = 0;

  while (getline(&currentKey, &n, file) >= 0) {
    keyNumber++;
    keyArray = realloc(keyArray, keyNumber * sizeof(*keyArray));
    keyArray[keyNumber - 1] = currentKey;
    currentKey = NULL;
  }

  free(currentKey);

  for (size_t i = 0; i < keyNumber; i++) {
    int match = 0;

    for (size_t j = 0; j < kvPairs->kvNumber; j++) {
      if (strncmp(keyArray[i],
                  kvPairs->kvArray[j].key,
                  strchr(keyArray[i], '\n') - keyArray[i]) == 0) {
        match = 1;
        addCount(counts, kvPairs->kvArray[j].value);
        break;
      }
    }

    if (match == 0) {
      addCount(counts, NULL);
    }

    free(keyArray[i]);
  }

  free(keyArray);

  if (fclose(file) != 0) {
    fprintf(stderr, "Can not close file: %s\n", filename);
    exit(EXIT_FAILURE);
  }

  return counts;
}

int main(int argc, char ** argv) {
  if (argc < 3) {
    fprintf(stderr, "Usage: ./file file file...\n");
    exit(EXIT_FAILURE);
  }
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w");
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "Can not close file: %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }
    //free the memory for outName and c
    free(outName);
    freeCounts(c);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
