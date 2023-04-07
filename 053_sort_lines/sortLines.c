#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

FILE ** getFileList(int argc, char ** argv) {
  FILE ** fileList = NULL;

  if (argc == 1) {
    fileList = malloc(sizeof(*fileList));
    FILE * file = stdin;
    if (file == NULL) {
      fprintf(stderr, "Can not open stdin!\n");
      free(fileList);
      exit(EXIT_FAILURE);
    }

    fileList[0] = file;
  }

  if (argc > 1) {
    fileList = malloc((argc - 1) * sizeof(*fileList));
    for (int i = 1; i < argc; i++) {
      FILE * file = fopen(argv[i], "r");
      if (file == NULL) {
        fprintf(stderr, "Can not open file: %s\n", argv[i]);
        for (int j = 0; j < i - 1; j++) {
          fclose(fileList[j]);
        }
        free(fileList);
        exit(EXIT_FAILURE);
      }

      fileList[i - 1] = file;
    }
  }

  return fileList;
}

char ** getLines(FILE * file, size_t * lineNum) {
  size_t number = 0;
  size_t sizeOfLine = 0;
  char ** lines = NULL;
  char * line = NULL;

  while (getline(&line, &sizeOfLine, file) >= 0) {
    lines = realloc(lines, (number + 1) * sizeof(*lines));
    lines[number] = line;
    line = NULL;
    number++;
  }
  free(line);
  *lineNum = number;
  return lines;
}

void printLines(char ** lines, size_t lineNum) {
  for (size_t i = 0; i < lineNum; i++) {
    printf("%s", lines[i]);
  }
}

void freeLines(char ** lines, size_t lineNum) {
  for (size_t i = 0; i < lineNum; i++) {
    free(lines[i]);
  }
  if (lineNum > 0) {
    free(lines);
  }
}

int main(int argc, char ** argv) {
  FILE ** fileList = getFileList(argc, argv);

  size_t fileListSize = 1;
  if (argc > 1) {
    fileListSize = argc - 1;
  }

  for (size_t i = 0; i < fileListSize; i++) {
    size_t lineNum;
    char ** lines = getLines(fileList[i], &lineNum);
    if (lineNum > 0) {
      sortData(lines, lineNum);
      printLines(lines, lineNum);
    }
    freeLines(lines, lineNum);
  }

  for (size_t i = 0; i < fileListSize; i++) {
    fclose(fileList[i]);
  }
  free(fileList);

  return EXIT_SUCCESS;
}
