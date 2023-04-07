#include "rand_story.h"

int main(int argc, char ** argv) {
  // Check argc
  if (argc != 3) {
    fprintf(stderr, "Usage: ./story-step3 filename1, filename2\n");
    exit(EXIT_FAILURE);
  }

  FILE * categories = openFile(argv[1]);
  size_t numberOfLinesInCategories;

  // Read file
  char ** linesInCategories = getLinesInFile(categories, &numberOfLinesInCategories);
  checkColons(linesInCategories, numberOfLinesInCategories);
  size_t numberOfCategories;
  catarray_t * categoryArray = createCategoryArray(
      linesInCategories, numberOfLinesInCategories, &numberOfCategories);

  FILE * storyTemplate = openFile(argv[2]);
  size_t numberOfLinesInTemplate;

  char ** linesInTemplate = getLinesInFile(storyTemplate, &numberOfLinesInTemplate);
  checkLines(linesInTemplate, numberOfLinesInTemplate);

  // Initialize usedWords
  category_t usedWords;
  usedWords.name = NULL;
  usedWords.n_words = 0;
  usedWords.words = NULL;

  // Printstory
  printNewStory(linesInTemplate, numberOfLinesInTemplate, &usedWords, categoryArray, 0);

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
