#include "rand_story.h"
int main(int argc, char ** argv) {
  // Check argc
  if (argc != 2) {
    fprintf(stderr, "Usage: ./story-step2 filename\n");
    exit(EXIT_FAILURE);
  }

  // Read file
  FILE * categories = openFile(argv[1]);
  size_t numberOfLinesInCategories;

  char ** linesInCategories = getLinesInFile(categories, &numberOfLinesInCategories);
  checkColons(linesInCategories, numberOfLinesInCategories);
  size_t numberOfCategories;
  catarray_t * categoryArray = createCategoryArray(
      linesInCategories, numberOfLinesInCategories, &numberOfCategories);

  // Print catArray
  printWords(categoryArray);

  // Free memory
  freeCategoryArray(categoryArray);
  freeLines(linesInCategories, numberOfLinesInCategories);

  // Close file
  if (fclose(categories) != 0) {
    fprintf(stderr, "Can not close file: %s\n", argv[2]);
  }

  return EXIT_SUCCESS;
}
