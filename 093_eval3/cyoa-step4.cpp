// main function to finish step4
#include <cstdlib>
#include <iostream>

#include "cyoa.hpp"

int main(int argc, char ** argv) {
  checkArgc(argc);

  Story myStory(argv[1], 1);
  myStory.startAdventure();

  return EXIT_SUCCESS;
}
