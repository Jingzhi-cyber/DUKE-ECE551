// main function to finish step1

#include <cstdlib>

#include "cyoa.hpp"

int main(int argc, char ** argv) {
  checkArgc(argc);
  Story myStory(argv[1]);
  myStory.printStory();

  return EXIT_SUCCESS;
}
