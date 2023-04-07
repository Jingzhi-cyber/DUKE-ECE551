#include "rand_story.h"

int main(int argc, char ** argv) {
  // Check argc
  if (argc < 3 || argc > 4) {
    fprintf(stderr, "Usage: ./story-step3 -n(optional) filename1, filename2\n");
    exit(EXIT_FAILURE);
  }

  if ((argc == 4) && (strcmp(argv[1], "-n") != 0)) {
    fprintf(stderr, "Usage: ./story-step3 -n(optional) filename1, filename2\n");
    exit(EXIT_FAILURE);
  }

  FILE * categories = NULL;
  FILE * storyTemplate = NULL;

  // Open files according to argc
  if (argc == 3) {
    categories = openFile(argv[1]);
    storyTemplate = openFile(argv[2]);
  }

  if (argc == 4) {
    categories = openFile(argv[2]);
    storyTemplate = openFile(argv[3]);
  }

  // Read files
  size_t numberOfLinesInCategories;

  char ** linesInCategories = getLinesInFile(categories, &numberOfLinesInCategories);
  checkColons(linesInCategories, numberOfLinesInCategories);
  size_t numberOfCategories;
  catarray_t * categoryArray = createCategoryArray(
      linesInCategories, numberOfLinesInCategories, &numberOfCategories);

  size_t numberOfLinesInTemplate;

  char ** linesInTemplate = getLinesInFile(storyTemplate, &numberOfLinesInTemplate);
  checkLines(linesInTemplate, numberOfLinesInTemplate);

  // Initialize usedwords
  category_t usedWords;
  usedWords.name = NULL;
  usedWords.n_words = 0;
  usedWords.words = NULL;

  // Trigger "no-reuse" fucntion or not
  if (argc == 3) {
    printNewStory(linesInTemplate, numberOfLinesInTemplate, &usedWords, categoryArray, 0);
  }

  if (argc == 4) {
    printNewStory(linesInTemplate, numberOfLinesInTemplate, &usedWords, categoryArray, 1);
  }

  // Free memory
  freeCategoryArray(categoryArray);
  freeUsedWords(usedWords);
  freeLines(linesInCategories, numberOfLinesInCategories);

  freeLines(linesInTemplate, numberOfLinesInTemplate);

  // Close file
  if (fclose(categories) != 0) {
    fprintf(stderr, "Can not close file: %s\n", argv[2]);
  }

  if (fclose(storyTemplate) != 0) {
    fprintf(stderr, "Can not close file: %s\n", argv[1]);
  }

  return EXIT_SUCCESS;
}
