// main function to finish step3
#include <cstdlib>
#include <iostream>

#include "cyoa.hpp"

int main(int argc, char ** argv) {
  checkArgc(argc);

  Story myStory(argv[1], 1);
  myStory.printWinPath();

  return EXIT_SUCCESS;
}
