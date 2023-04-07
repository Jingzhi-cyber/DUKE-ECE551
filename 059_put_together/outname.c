#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  char * outputFileName = malloc((strlen(inputName) + 1 + 7) * sizeof(*outputFileName));
  char * tail = ".counts";
  strcpy(outputFileName, inputName);
  strcpy(outputFileName + strlen(inputName), tail);

  return outputFileName;
}
