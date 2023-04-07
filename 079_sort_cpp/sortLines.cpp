#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// function to checkFileStream
template<typename T>
void checkFile(const T & fileToRead) {
  if (!fileToRead.good()) {
    std::cerr << "Can not read file!\n";
    std::exit(EXIT_FAILURE);
  }
}

// function to open file

std::ifstream * openFile(const char * fileName) {
  std::ifstream * fileToRead = new std::ifstream(fileName);

  checkFile<std::ifstream>(*fileToRead);

  return fileToRead;
}

// function to read file
template<typename T>
std::vector<std::string> readFile(T & fileToRead) {
  std::vector<std::string> linesInFile;
  std::string currentLine;

  while (getline(fileToRead, currentLine)) {
    checkFile<T>(fileToRead);
    linesInFile.push_back(currentLine);
  }

  //  std::vector<std::string> * lines = new std::vector<std::string>(linesInFile);
  //std::vector<std::vector<string>>

  //  return lines;
  return linesInFile;
}

// function to sort file

void sortLines(std::vector<std::string> & linesInFile) {
  std::sort(linesInFile.begin(), linesInFile.end());
}

// function to print file

void printFile(const std::vector<std::string> & linesInFile) {
  std::vector<std::string>::const_iterator it = linesInFile.begin();
  while (it != linesInFile.end()) {
    std::cout << *it << std::endl;
    ++it;  // If you forget to increment the iterator, you would end up in infinite loop!!!
  }
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    std::vector<std::string> lineInStdin = readFile<std::istream>(std::cin);
    sortLines(lineInStdin);
    printFile(lineInStdin);
  }

  for (int i = 0; i < argc - 1; i++) {
    std::ifstream * fileToRead = openFile(argv[i + 1]);
    std::vector<std::string> linesInfile = readFile<std::ifstream>(*fileToRead);
    sortLines(linesInfile);
    printFile(linesInfile);
    fileToRead->close();
    delete fileToRead;
  }

  return EXIT_SUCCESS;
}
