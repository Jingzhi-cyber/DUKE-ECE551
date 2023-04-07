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

Choice::Choice() :
    pageNum(0),
    choiceNum(0),
    jumpPageNum(0),
    choiceText(""),
    isConditional(false),
    condition(pair<string, long int>()) {
}

Choice::Choice(size_t _pageNum,
               size_t _choiceNum,
               size_t _jumpPageNum,
               string _choiceText) :
    pageNum(_pageNum),
    choiceNum(_choiceNum),
    jumpPageNum(_jumpPageNum),
    choiceText(_choiceText),
    isConditional(false),
    condition(pair<string, long int>()) {
}

Choice::Choice(size_t _pageNum,
               size_t _choiceNum,
               size_t _jumpPageNum,
               string _choiceText,
               pair<string, long int> _condition) :
    pageNum(_pageNum),
    choiceNum(_choiceNum),
    jumpPageNum(_jumpPageNum),
    choiceText(_choiceText),
    isConditional(true),
    condition(_condition) {
}

size_t Choice::getDestPageNum() const {
  return jumpPageNum;
}

void Choice::printChoice() const {
  std::cout << " " << choiceNum << ". " << choiceText << std::endl;
}

size_t Choice::getChoiceIndex() const {
  return this->choiceNum;
}

void Choice::printUnavailable() const {
  std::cout << " " << choiceNum << ". "
            << "<UNAVAILABLE>" << std::endl;
}

bool Choice::getIsConditional() const {
  return this->isConditional;
}

pair<string, long int> Choice::getCondition() const {
  return this->condition;
}

// for class Page

Page::Page() :
    type(0),
    pageNum(0),
    pageName(""),
    pageDirectory(""),
    pageText(vector<string>(0)),
    variablesToSet(stack<pair<string, long int> >()) {
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
    pageText(_pageText),
    variablesToSet(stack<pair<string, long int> >()) {
}

Page::Page(char _type, size_t _pageNum, string _pageName, string _pageDirectory) :
    type(_type),
    pageNum(_pageNum),
    pageName(_pageName),
    pageDirectory(_pageDirectory),
    variablesToSet(stack<pair<string, long int> >()) {
  this->pageText = getText(this->pageDirectory);
}

Page::~Page() {
}

char Page::getType() const {
  return type;
}

size_t Page::getPageNum() const {
  return pageNum;
}

void Page::addOnePairToStack(const pair<string, long> & variable) {
  this->variablesToSet.push(variable);
}

void Page::assignVariables(map<string, long int> & variables) {
  stack<pair<string, long int> > currentVariablesToSet = this->variablesToSet;
  while (!currentVariablesToSet.empty()) {
    pair<string, long int> currentVariableToSet = currentVariablesToSet.top();
    variables[currentVariableToSet.first] = currentVariableToSet.second;
    currentVariablesToSet.pop();
  }
}

void Page::printPage(map<string, long int> & variables) {
  assignVariables(variables);
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

vector<size_t> NormalPage::getDestPageNumArray() const {
  vector<size_t> destPageNumArray;
  vector<Choice>::const_iterator it = choiceVector.begin();
  while (it != choiceVector.end()) {
    destPageNumArray.push_back((*it).getDestPageNum());
    ++it;
  }
  return destPageNumArray;
}

size_t NormalPage::getChoiceNum() {
  return choiceVector.size();
}

vector<size_t> NormalPage::getUnavailableChoices(
    const map<string, long int> & variables) {
  vector<size_t> unavailableChoices;
  vector<Choice>::const_iterator it = this->choiceVector.begin();
  while (it != choiceVector.end()) {
    if ((*it).getIsConditional()) {
      map<string, long int>::const_iterator it_second =
          variables.find((*it).getCondition().first);
      if (it_second == variables.end() ||
          (*it_second).second != (*it).getCondition().second) {
        unavailableChoices.push_back((*it).getChoiceIndex());
      }
    }
    ++it;
  }

  return unavailableChoices;
}

void NormalPage::printPage(map<string, long int> & variables) {
  Page::printPage(variables);
  std::cout << "What would you like to do?" << std::endl;
  std::cout << std::endl;
  vector<Choice>::const_iterator it = choiceVector.begin();
  while (it != choiceVector.end()) {
    if (!(*it).getIsConditional()) {
      (*it).printChoice();
    }
    else {
      /*  This part is to make sure that if the condition in the conditonal choice has a variable name that has not been assigned, it will not be be added to the map.
      map<string, long int>::iterator it_second =
          variables.find((*it).getCondition().first);
      if (it_second == variables.end() ||
          (*it_second).second != (*it).getCondition().second) {
        (*it).printUnavailable();
      }
      else {
        (*it).printChoice();
      }
      */
      if (variables[(*it).getCondition().first] == (*it).getCondition().second) {
        (*it).printChoice();
      }
      else {
        (*it).printUnavailable();
      }
    }
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

vector<size_t> WinPage::getDestPageNumArray() const {
  std::cerr << "There are no choices in Winpage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

vector<size_t> WinPage::getUnavailableChoices(const map<string, long int> & variables) {
  std::cerr << "There are no choices in Winpage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

void WinPage::printPage(map<string, long int> & variables) {
  Page::printPage(variables);
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

vector<size_t> LosePage::getDestPageNumArray() const {
  std::cerr << "There are no choices in Losepage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

size_t LosePage::getChoiceNum() {
  std::cerr << "There are no choices in Losepage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

vector<size_t> LosePage::getUnavailableChoices(const map<string, long int> & variables) {
  std::cerr << "There are no choices in Losepage!" << std::endl;
  std::exit(EXIT_FAILURE);
}

void LosePage::printPage(map<string, long int> & variables) {
  Page::printPage(variables);
  std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
}

// for class Story
// private method to print one page and check Win or Lose
void Story::printPage(size_t pageNum, map<string, long int> & variables) const {
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
  pageVector[pageNum]->printPage(variables);
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

Story::Story() :
    directory(""), pageVector(vector<Page *>()), variables(map<string, long int>()) {
}

Story::Story(string _directory, int pageNumCheck) :
    directory(_directory), pageVector(vector<Page *>(0)) {
  string story_file_path;
  story_file_path.append(directory);
  story_file_path.push_back('/');
  story_file_path.append("story.txt");
  vector<string> lines = getText(story_file_path);

  if (lines.empty()) {
    std::cerr << "The story.txt file in the given directroy is empty!"
              << " Directory: " << _directory << std::endl;
    std::exit(EXIT_FAILURE);
  }

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

    if (isConditionalChoice(*it, pageVector)) {
      ++it;
      continue;
    }

    if (isSetStoryVariable(*it, pageVector, this->variables)) {
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
void Story::printStory() {
  vector<Page *>::const_iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    std::cout << "Page " << (*it)->getPageNum() << std::endl;
    std::cout << "==========" << std::endl;
    (*it)->printPage(this->variables);
    ++it;
  }
}

// public method to start the game
void Story::startAdventure() {
  printPage(0, this->variables);
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

    vector<size_t> currentUnavaliableChoices =
        pageVector[currentPageNum]->getUnavailableChoices(this->variables);

    while (!(checkTypeInArray<size_t>(choice, currentChoices)) ||
           (checkTypeInArray<size_t>(choice, currentUnavaliableChoices))) {
      if (!checkTypeInArray<size_t>(choice, currentChoices)) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        choice = getChoiceFromUser();
      }
      if (checkTypeInArray<size_t>(choice, currentUnavaliableChoices)) {
        std::cout << "That choice is not available at this time, please try again"
                  << std::endl;
        choice = getChoiceFromUser();
      }
    }
    size_t jumpPageNum = pageVector[currentPageNum]->getDestPageNumArray()[choice - 1];

    printPage(jumpPageNum, this->variables);
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
  //  allWinPaths.unique();
  vector<stack<size_t> > printedPath;

  list<stack<size_t> >::iterator it = allWinPaths.begin();
  while (it != allWinPaths.end()) {
    if (!checkTypeInArray<stack<size_t> >(*it, printedPath)) {
      printOneWinPath(*it, pageVector);
      printedPath.push_back((*it));
    }
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

// function to check whether a value for a story variable is valid
bool isValidVariableValue(string & line,
                          char *& afterVariableValue,
                          long int & variableValue) {
  afterVariableValue = NULL;
  variableValue = std::strtol(line.c_str(), &afterVariableValue, 10);

  if (variableValue == 0 && afterVariableValue == NULL) {
    return false;
  }

  if (variableValue == LONG_MAX && errno == ERANGE) {
    std::cerr << "Variable value trying to set is out of range! PageNum : "
              << variableValue << std::endl;
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

  if (*afterPageNum != '@') {
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
               string text,
               pair<string, long int> condition,
               bool isConditional) {
  bool foundPage = false;
  vector<Page *>::iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    if ((*it)->getPageNum() == pageNum) {
      size_t choiceNum = (*it)->getChoiceNum() + 1;
      if (!isConditional) {
        (*it)->addOneChoice(Choice(pageNum, choiceNum, destPageNum, text));
      }
      else {
        (*it)->addOneChoice(Choice(pageNum, choiceNum, destPageNum, text, condition));
      }

      foundPage = true;
      break;
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

  if (*afterPageNum != ':') {
    return false;
  }

  size_t destPageNum = 0;
  char * afterDestPageNum = NULL;
  string afterFirstColon = line.substr(indexOfFirstColon + 1);

  if (!isValidNumber(afterFirstColon, afterDestPageNum, destPageNum)) {
    return false;
  }

  if (*afterDestPageNum != ':') {
    return false;
  }

  string text = line.substr(indexOfSecondColon + 1);
  addChoice(pageVector, pageNum, destPageNum, text, pair<string, long int>(), false);
  return true;
}

// fucntion to check whether a line is a conditional choice declaration. If it is, then add one choice and set its condition.
bool isConditionalChoice(string line, vector<Page *> & pageVector) {
  size_t indexOfLeftRef = line.find('[');
  size_t indexOfEqual = line.find('=', indexOfLeftRef + 1);
  size_t indexOfRightRef = line.find(']', indexOfEqual + 1);
  size_t indexOfFirstColon = line.find(':', indexOfRightRef + 1);
  size_t indexOfSecondColon = line.find(':', indexOfFirstColon + 1);

  if (indexOfLeftRef == string::npos || indexOfEqual == string::npos ||
      indexOfRightRef == string::npos || indexOfFirstColon == string::npos ||
      indexOfSecondColon == string::npos) {
    return false;
  }

  if ((indexOfFirstColon - indexOfRightRef) != 1) {
    return false;
  }

  size_t pageNum = 0;
  char * afterPageNum = NULL;

  if (!isValidNumber(line, afterPageNum, pageNum)) {
    return false;
  }

  if ((*afterPageNum) != '[') {
    return false;
  }

  string variableName =
      line.substr(indexOfLeftRef + 1, indexOfEqual - indexOfLeftRef - 1);

  char * afterVariableValue = NULL;
  long int variableValue = 0;
  string lineAfterEqual = line.substr(indexOfEqual + 1);

  if (lineAfterEqual.empty()) {
    return false;
  }

  if (!isValidVariableValue(lineAfterEqual, afterVariableValue, variableValue)) {
    return false;
  }

  if (*afterVariableValue != ']' || *(afterVariableValue + 1) != ':') {
    return false;
  }

  pair<string, long int> condition(variableName, variableValue);

  size_t destPageNum = 0;
  char * afterDestPageNum = NULL;
  string afterFirstColon = line.substr(indexOfFirstColon + 1);

  if (!isValidNumber(afterFirstColon, afterDestPageNum, destPageNum)) {
    return false;
  }

  if (*afterDestPageNum != ':') {
    return false;
  }

  string text = line.substr(indexOfSecondColon + 1);
  addChoice(pageVector, pageNum, destPageNum, text, condition, true);
  return true;
}

// function to add one variable with its name and value to the stack in the corresponding Page object
void addOneStoryVaribale(vector<Page *> & pageVector,
                         const pair<string, long int> & variableToSet,
                         const size_t & pageNum) {
  bool foundPage = false;
  vector<Page *>::iterator it = pageVector.begin();
  while (it != pageVector.end()) {
    if ((*it)->getPageNum() == pageNum) {
      (*it)->addOnePairToStack(variableToSet);
      foundPage = true;
      break;
    }
    ++it;
  }

  if (!foundPage) {
    std::cerr << "There are no matching page for the given pageNum: " << pageNum
              << std::endl;
    std::exit(EXIT_FAILURE);
  }
}

// fucntion to check whether a line is a declaration to set one story varibale.  If it is, then add one variable with its name and value to the stack in the corresponding Page object.
bool isSetStoryVariable(string line,
                        vector<Page *> & pageVector,
                        map<string, long int> & variables) {
  size_t indexOfChar = line.find('$');
  size_t indexOfEqual = line.find('=');

  if (indexOfChar == string::npos || indexOfEqual == string::npos) {
    return false;
  }

  if ((indexOfEqual - indexOfChar) < 1) {
    return false;
  }

  string variableName = line.substr(indexOfChar + 1, indexOfEqual - indexOfChar - 1);

  char * afterPageNum = NULL;
  size_t pageNum = 0;

  if (!isValidNumber(line, afterPageNum, pageNum)) {
    return false;
  }

  if (*afterPageNum != '$') {
    return false;
  }

  char * afterVariableValue = NULL;
  long int variableValue = 0;
  string lineAfterEqual = line.substr(indexOfEqual + 1);

  if (lineAfterEqual.empty()) {
    return false;
  }

  if (!isValidVariableValue(lineAfterEqual, afterVariableValue, variableValue)) {
    return false;
  }

  if (*afterVariableValue != 0) {
    return false;  // Check there are no things left after the variableValue  pageNum$var=value
  }

  variables[variableName] = 0;  // add one variable to story, initialize it to 0
  pair<string, long int> variableToSet(variableName, variableValue);
  addOneStoryVaribale(pageVector, variableToSet, pageNum);

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
        if ((*it)->getPageNum() != *_it) {
          pageNumReferArray[*_it] = true;
        }
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
      std::cerr << "There is page(except page 0) that is not referenced! Page number: "
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
        break;
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
