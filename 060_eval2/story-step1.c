#include "rand_story.h"
int main(int argc, char ** argv) {
  // Check argc
  if (argc != 2) {
    fprintf(stderr, "Usage: ./story-step1 filename\n");
    exit(EXIT_FAILURE);
  }

  // Read file
  FILE * storyTemplate = openFile(argv[1]);
  size_t numberOfLinesInTemplate;

  char ** linesInTemplate = getLinesInFile(storyTemplate, &numberOfLinesInTemplate);
  checkLines(linesInTemplate, numberOfLinesInTemplate);

  // Print story
  printStory(linesInTemplate, numberOfLinesInTemplate);

  // Free memory
  freeLines(linesInTemplate, numberOfLinesInTemplate);

  // Close file
  if (fclose(storyTemplate) != 0) {
    fprintf(stderr, "Can not close file: %s\n", argv[1]);
  }

  return EXIT_SUCCESS;
}
