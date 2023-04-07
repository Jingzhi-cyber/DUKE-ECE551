// Implementation of fucntions
#include "cyoa.hpp"

#include <cerrno>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <sstream>

// function to checkFileStream
void checkFile(std::ifstream & fileToRead, string & fileDirectory) {
  if (!fileToRead.good()) {
    std::cerr << "Can not read file: " << fileDirectory << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

// function to open file

std::ifstream * openFile(string & fileDirectory) {
  std::ifstream * fileToRead = new std::ifstream(fileDirectory.c_str());

  checkFile(*fileToRead, fileDirectory);
  return fileToRead;
}

// function to get the text in file
vector<string> getText(string & fileDirectoty) {
  vector<string> linesInFile;
  string currentLine;

  std::ifstream * fileToRead = openFile(fileDirectoty);
  while (getline(*fileToRead, currentLine)) {
    checkFile(*fileToRead, fileDirectoty);
    linesInFile.push_back(currentLine);
  }

  fileToRead->close();
  delete fileToRead;

  return linesInFile;
}

// fucntion to get a input line from user
string getInputFromUser() {
  string input;

  std::cin >> input;
  if (!std::cin.good()) {
    std::cerr << "Can not read anything from cin!\n";
    std::exit(EXIT_FAILURE);
  }
  return input;
}

// for class Choice

Choice::Choice() : pageNum(0), choiceNum(0), jumpPageNum(0), choiceText("") {
}

Choice::Choice(size_t _pageNum,
               size_t _choiceNum,
               size_t _jumpPageNum,
               string _choiceText) :
    pageNum(_pageNum),
    choiceNum(_choiceNum),
    jumpPageNum(_jumpPageNum),
    choiceText(_choiceText) {
}

size_t Choice::getDestPageNum() {
  return jumpPageNum;
}

void Choice::printChoice() const {
  std::cout << " " << choiceNum << ". " << choiceText << std::endl;
}

// for class Page

Page::Page() :
    type(0), pageNum(0), pageName(""), pageDirectory(""), pageText(vector<string>(0)) {
}
Page::Page(char _type,
           size_t _pageNum,
           string _pageName,
           string _pageDirectory,
           vector<string> _pageText) :
    type(_type),
    pageNum(_pageNum),
    pageName(_pageName),
    pageDirectory(_pageDirectory),
    pageText(_pageText) {
}

Page::Page(char _type, size_t _pageNum, string _pageName, string _pageDirectory) :
    type(_type), pageNum(_pageNum), pageName(_pageName), pageDirectory(_pageDirectory) {
  this->pageText = getText(this->pageDirectory);
}

Page::~Page() {
}

char Page::getType() {
  return type;
}

size_t Page::getPageNum() {
  return pageNum;
}

void Page::printPage() const {
  vector<string>::const_iterator it = pageText.begin();
  while (it != pageText.end()) {
    std::cout << *it << std::endl;
    ++it;
  }

  std::cout << std::endl;
}

// for class NormalPage
NormalPage::NormalPage() : choiceVector(vector<Choice>(0)) {
}

NormalPage::NormalPage(char _type,
                       size_t _pageNum,
                       string _pageName,
                       string _pageDirectory,
                       vector<string> _pageText,
                       vector<Choice> _choiceVector) :
    Page(_type, _pageNum, _pageName, _pageDirectory, _pageText),
    choiceVector(_choiceVector) {
}

NormalPage::NormalPage(char _type,
                       size_t _pageNum,
                       string _pageName,
                       string _pageDirectory,
                       vector<Choice> _choiceVector) :
    Page(_type, _pageNum, _pageName, _pageDirectory), choiceVector(_choiceVector) {
}

NormalPage::NormalPage(char _type,
                       size_t _pageNum,
                       string _pageName,
                       string _pageDirectory) :
    Page(_type, _pageNum, _pageName, _pageDirectory), choiceVector(vector<Choice>(0)) {
}

NormalPage::~NormalPage() {
}

void NormalPage::addOneChoice(const Choice & newChoice) {
  this->choiceVector.push_back(newChoice);
}

vector<size_t> NormalPage::getDestPageNumArray() {
  vector<size_t> destPageNumArray;
  vector<Choice>::iterator it = choiceVector.begin();
  while (it != choiceVector.end()) {
    destPageNumArray.push_back((*it).getDestPageNum());
    ++it;
  }
  return destPageNumArray;
}

size_t NormalPage::getChoiceNum() {
  return choiceVector.size();
}

void NormalPage::printPage() const {
  Page::printPage();
  std::cout << "What would you like to do?" << std::endl;
  std::cout << std::endl;
  vector<Choice>::const_iterator it = choiceVector.begin();
  while (it != choiceVector.end()) {
    (*it).printChoice();
    ++it;
  }
}

// for class WinPage
WinPage::WinPage() {
}

WinPage::WinPage(char _type, size_t _pageNum, string _pageName, string _pageDirectory) :
    Page(_type, _pageNum, _pageName, _pageDirectory) {
}

WinPage::~WinPage() {
}

void WinPage::addOneChoice(const Choice & newChoice) {
  std::cerr << "Can not add a choice to WinPage! " << std::endl;
  newChoice.printChoice();
  std::exit(EXIT_FAILURE);
}

size_t WinPage::getChoiceNum() {
  std::cerr << "There are no choices in Winpage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

vector<size_t> WinPage::getDestPageNumArray() {
  std::cerr << "There are no choices in Winpage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

void WinPage::printPage() const {
  Page::printPage();
  std::cout << "Congratulations! You have won. Hooray!" << std::endl;
}

// for class LosePage
LosePage::LosePage() {
}

LosePage::LosePage(char _type, size_t _pageNum, string _pageName, string _pageDirectory) :
    Page(_type, _pageNum, _pageName, _pageDirectory) {
}

LosePage::~LosePage() {
}

void LosePage::addOneChoice(const Choice & newChoice) {
  std::cerr << "Can not add a choice to LosePage! " << std::endl;
  newChoice.printChoice();
  std::exit(EXIT_FAILURE);
}

vector<size_t> LosePage::getDestPageNumArray() {
  std::cerr << "There are no choices in Losepage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

size_t LosePage::getChoiceNum() {
  std::cerr << "There are no choices in Losepage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

void LosePage::printPage() const {
  Page::printPage();
  std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
}

// for class Story
// private method to print one page and check Win or Lose
void Story::printPage(size_t pageNum) const {
  /*
  vector<Page *>::const_iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    if (pageNum == (*it)->getPageNum()) {
      (*it)->printPage();
      char type = (*it)->getType();
      if (type == 'W' || type == 'L') {
        vector<Page *>::const_iterator _it = pageVector.begin();

        while (_it != pageVector.end()) {
          delete *_it;
          ++_it;
        }
        std::exit(EXIT_SUCCESS);
      }
      break;
    }
    ++it;
  }
  */
  pageVector[pageNum]->printPage();
  /* 
 char type = pageVector[pageNum]->getType();

  if (type != 'N') {
    vector<Page *>::const_iterator it = pageVector.begin();

    while (it != pageVector.end()) {
      delete *it;
      ++it;
    }

        std::exit(EXIT_SUCCESS);
  }
  */
}

// private method to get the choice from user
size_t Story::getChoiceFromUser() const {
  size_t choiceNum = 0;
  char * afterChoiceNum = NULL;
  string inputLine = getInputFromUser();
  while (!isValidNumber(inputLine, afterChoiceNum, choiceNum)) {
    std::cout << "That is not a valid choice, please try again" << std::endl;
    inputLine = getInputFromUser();
  }

  return choiceNum;
}

Story::Story() : directory(""), pageVector(vector<Page *>()) {
}

Story::Story(string _directory, int pageNumCheck) :
    directory(_directory), pageVector(vector<Page *>(0)) {
  string story_file_path;
  story_file_path.append(directory);
  story_file_path.push_back('/');
  story_file_path.append("story.txt");
  vector<string> lines = getText(story_file_path);
  vector<string>::iterator it = lines.begin();
  while (it != lines.end()) {
    if (isBlank(*it)) {
      ++it;
      continue;
    }
    if (isPage(*it, pageVector, directory)) {
      ++it;
      continue;
    }
    if (isChoice(*it, pageVector)) {
      ++it;
      continue;
    }

    std::cerr << "The format of the line is wrong! Line: " << *it << std::endl;
    exit(EXIT_FAILURE);
  }

  if (pageNumCheck == 1) {
    if (!checkDestPageNum(pageVector)) {
      std::cerr << "There are non-existing destPageNum! \n";
      std::exit(EXIT_FAILURE);
    }

    checkWinLosePage(pageVector);
  }
}
/*
Story::Story(const Story & rhs): directory(rhs.directory), pageVector(vector<Page*>(rhs.pageVector.size())) {

  vector<Page *> :: iterator it = pageVector.begin();
  vector<Page*> :: const_iterator it_rhs = rhs.pageVector.begin();
  while (it != pageVector.end()){

    *it = *it_rhs; // error, shallow copy
    ++it;
    ++it_rhs;

  }


}
*/
Story::~Story() {
  vector<Page *>::iterator it = pageVector.begin();

  while (it != pageVector.end()) {
    delete *it;
    ++it;
  }
}
// public method to print the whole story
void Story::printStory() const {
  vector<Page *>::const_iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    std::cout << "Page " << (*it)->getPageNum() << std::endl;
    std::cout << "==========" << std::endl;
    (*it)->printPage();
    ++it;
  }
}

// public method to start the game
void Story::startAdventure() const {
  printPage(0);
  size_t currentPageNum = 0;
  while (pageVector[currentPageNum]->getType() == 'N') {
    size_t choice = getChoiceFromUser();
    vector<size_t> currentChoices(pageVector[currentPageNum]->getChoiceNum());
    vector<size_t>::iterator it = currentChoices.begin();
    size_t index = 1;
    while (it != currentChoices.end()) {
      *it = index;
      index++;
      ++it;
    }
    while (!checkTypeInArray<size_t>(choice, currentChoices)) {
      std::cout << "That is not a valid choice, please try again" << std::endl;
      choice = getChoiceFromUser();
    }
    size_t jumpPageNum = pageVector[currentPageNum]->getDestPageNumArray()[choice - 1];

    printPage(jumpPageNum);
    currentPageNum = jumpPageNum;
  }
}

// public method to print all winning pathes
void Story::printWinPath() const {
  list<stack<size_t> > allWinPaths;
  findWinPath(allWinPaths, pageVector);

  if (allWinPaths.empty()) {
    std::cout << "This story is unwinnable!" << std::endl;
  }

  list<stack<size_t> >::iterator it = allWinPaths.begin();
  while (it != allWinPaths.end()) {
    printOneWinPath(*it, pageVector);
    ++it;
  }
}

// fucntion to check whether a line is blank
bool isBlank(string line) {
  if (line.empty()) {
    return true;
  }
  else if (line == string(line.size(), ' ')) {
    return true;
  }

  return false;
}

// function to add one page
void addPage(vector<Page *> & pageVector,
             char type,
             size_t pageNum,
             string pageName,
             string pageDirectory) {
  if (type == 'N') {
    Page * normalPage = new NormalPage(type, pageNum, pageName, pageDirectory);
    pageVector.push_back(normalPage);
  }

  else if (type == 'W') {
    Page * winPage = new WinPage(type, pageNum, pageName, pageDirectory);
    pageVector.push_back(winPage);
  }

  else if (type == 'L') {
    Page * losePage = new LosePage(type, pageNum, pageName, pageDirectory);
    pageVector.push_back(losePage);
  }

  else {
    std::cerr << "Page type should be 'N', 'W', or 'L' !" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

// function to check whether a page number is valid
bool isValidNumber(string & line, char *& afterPageNum, size_t & pageNum) {
  afterPageNum = NULL;
  pageNum = std::strtoul(line.c_str(), &afterPageNum, 10);

  if (pageNum == 0 && afterPageNum == NULL) {
    return false;
  }

  if (pageNum == ULONG_MAX && errno == ERANGE) {
    std::cerr << "Page number out of range!" << std::endl;
    std::exit(EXIT_FAILURE);
  }

  return true;
}

// fucntion to check whether a line is a page declaration. If it is, then add one page.
bool isPage(string line, vector<Page *> & pageVector, string directory) {
  size_t indexOfChar = line.find('@');
  size_t indexOfColon = line.find(':');

  if (indexOfChar == string::npos || indexOfColon == string::npos) {
    return false;
  }

  if ((indexOfColon - indexOfChar) != 2) {
    return false;
  }

  char * afterPageNum = NULL;
  size_t pageNum = 0;

  if (!isValidNumber(line, afterPageNum, pageNum)) {
    return false;
  }

  if (pageNum == pageVector.size()) {
    char type = line[indexOfChar + 1];
    string pageName = line.substr(indexOfColon + 1);
    string pageDirectory;
    pageDirectory.append(directory);
    pageDirectory.push_back('/');
    pageDirectory.append(pageName);
    addPage(pageVector, type, pageNum, pageName, pageDirectory);

    return true;
  }

  return false;
}

// function to add one choice
void addChoice(vector<Page *> & pageVector,
               size_t pageNum,
               size_t destPageNum,
               string text) {
  bool foundPage = false;
  vector<Page *>::iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    if ((*it)->getPageNum() == pageNum) {
      size_t choiceNum = (*it)->getChoiceNum() + 1;
      (*it)->addOneChoice(Choice(pageNum, choiceNum, destPageNum, text));
      foundPage = true;
    }
    ++it;
  }

  if (!foundPage) {
    std::cerr << "There are no matching page for the given pageNum: " << pageNum
              << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

// fucntion to check whether a line is a choice declaration. If it is, then add one choice.
bool isChoice(string line, vector<Page *> & pageVector) {
  size_t indexOfFirstColon = line.find(':');

  if (indexOfFirstColon == string::npos) {
    return false;
  }

  size_t indexOfSecondColon = line.find(':', indexOfFirstColon + 1);

  if (indexOfSecondColon == string::npos) {
    return false;
  }

  size_t pageNum = 0;
  char * afterPageNum = NULL;

  if (!isValidNumber(line, afterPageNum, pageNum)) {
    return false;
  }

  size_t destPageNum = 0;
  char * afterDestPageNum = NULL;
  string afterFirstColon = line.substr(indexOfFirstColon + 1);

  if (!isValidNumber(afterFirstColon, afterDestPageNum, destPageNum)) {
    return false;
  }

  string text = line.substr(indexOfSecondColon + 1);
  addChoice(pageVector, pageNum, destPageNum, text);
  return true;
}

// function to check all the destPageNum in choices can be matched to pageNum. And make sure every page(except 0) is referenced at least once.
bool checkDestPageNum(const vector<Page *> & pageVector) {
  vector<bool> pageNumReferArray(pageVector.size(), false);
  *(pageNumReferArray.begin()) = true;
  vector<size_t> pageNumArray;
  vector<Page *>::const_iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    pageNumArray.push_back((*it)->getPageNum());
    ++it;
  }

  it = pageVector.begin();
  while (it != pageVector.end()) {
    if ((*it)->getType() == 'N') {
      vector<size_t> destPageNumArray = (*it)->getDestPageNumArray();
      vector<size_t>::iterator _it = destPageNumArray.begin();
      while (_it != destPageNumArray.end()) {
        pageNumReferArray[*_it] = true;
        if (!checkTypeInArray<size_t>(*_it, pageNumArray)) {
          return false;  // destpagenum in the choice does not match to any given page
        }
        ++_it;
      }
    }
    ++it;
  }

  vector<bool>::const_iterator it_refer = pageNumReferArray.begin();
  size_t currentPageNum = 0;
  while (it_refer != pageNumReferArray.end()) {
    if (*it_refer != true) {
      std::cout << "There is page(except page 0) that is not referenced! Page number: "
                << currentPageNum << std::endl;
      std::exit(EXIT_FAILURE);
    }
    currentPageNum++;
    ++it_refer;
  }
  return true;
}

// function to check at least one Win page and at least one Lose page
void checkWinLosePage(const vector<Page *> & pageVector) {
  vector<char> pageTypeArray;
  vector<Page *>::const_iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    pageTypeArray.push_back((*it)->getType());
    ++it;
  }

  if (!(checkTypeInArray<char>('W', pageTypeArray))) {
    std::cerr << "There are no winning page!\n";
    std::exit(EXIT_FAILURE);
  }

  if (!(checkTypeInArray<char>('L', pageTypeArray))) {
    std::cerr << "There are no losing page!\n";
    std::exit(EXIT_FAILURE);
  }
}
// function to check argc
void checkArgc(const int & argc) {
  if (argc != 2) {
    std::cerr << "Usage: ./program  directory!" << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

// function to obtain all winning pathes
void findWinPath(list<stack<size_t> > & allWinPathes, const vector<Page *> & pageVector) {
  stack<size_t> initialToSearch;
  initialToSearch.push(0);
  stack<size_t> currentPath;
  set<size_t> visitedPages;
  stack<stack<size_t> > toSearch;
  toSearch.push(initialToSearch);
  while (!toSearch.empty()) {
    currentPath = toSearch.top();
    toSearch.pop();
    size_t currentPageNum = currentPath.top();
    if (pageVector[currentPageNum]->getType() == 'W') {
      allWinPathes.push_back(currentPath);
      currentPath.pop();
      while (pageVector[currentPath.top()]->getChoiceNum() == 1) {
        visitedPages.erase(currentPath.top());
        currentPath.pop();
      }
      visitedPages.erase(currentPath.top());
    }

    if (visitedPages.find(currentPageNum) == visitedPages.end()) {
      visitedPages.insert(currentPageNum);

      if (pageVector[currentPageNum]->getType() == 'N') {
        for (size_t i = 0; i < pageVector[currentPageNum]->getChoiceNum(); i++) {
          stack<size_t> newPath = currentPath;
          newPath.push((pageVector[currentPageNum]->getDestPageNumArray())[i]);
          toSearch.push(newPath);
        }
      }
    }
  }
}

// function to print a winning path
void printOneWinPath(stack<size_t> & oneWinPath, const vector<Page *> & pageVector) {
  std::stringstream winString;
  size_t pageNum = oneWinPath.top();
  winString << pageNum << "(win)";
  oneWinPath.pop();
  string path = winString.str();

  while (!oneWinPath.empty()) {
    size_t currentPageNum = oneWinPath.top();
    size_t currentChoiceNum = 0;
    for (size_t i = 0; i < pageVector[currentPageNum]->getChoiceNum(); i++) {
      if (pageVector[currentPageNum]->getDestPageNumArray()[i] == pageNum) {
        currentChoiceNum = i + 1;
      }
    }

    std::stringstream currentString;
    currentString << currentPageNum << "(" << currentChoiceNum << "),";
    path = currentString.str() + path;
    pageNum = currentPageNum;
    oneWinPath.pop();
  }

  std::cout << path << std::endl;
}
