#ifndef __T_CYOA_H__
#define __T_CYOA_H__

#include <fstream>
#include <list>
#include <set>
#include <stack>
#include <string>
#include <vector>
using std::list;
using std::set;
using std::stack;
using std::string;
using std::vector;
// function to checkFileStream
void checkFile(std::ifstream & fileToRead, string & fileDirectory);

// function to open file
std::ifstream * openFile(string & fileDirectory);

// function to get the text in file
vector<string> getText(string & fileDirectory);

// fucntion to get a input line from user
string getInputFromUser();

class Choice {
 private:
  size_t pageNum;
  size_t choiceNum;
  size_t jumpPageNum;
  string choiceText;

 public:
  Choice();
  Choice(size_t _pageNum, size_t _choiceNum, size_t _jumpPageNum, string _choiceText);

  size_t getDestPageNum();
  void printChoice() const;
  //friend std::ostream & operator<<(std::ostream & stream, const Choice & data);
};

class Page {
 private:
  char type;  // maybe string?
  size_t pageNum;
  string pageName;
  string pageDirectory;
  vector<string> pageText;

 public:
  Page();
  Page(char _type,
       size_t _pageNum,
       string _pageName,
       string _pageDirectory,
       vector<string> _pageText);

  Page(char _type, size_t _pageNum, string _pageName, string _pageDirectory);

  //  void addOneLineText(const string & newLine);
  virtual ~Page();  // Rule of three needed!

  char getType();
  size_t getPageNum();
  virtual void printPage() const;
  virtual vector<size_t> getDestPageNumArray() = 0;
  virtual void addOneChoice(const Choice & newChoice) = 0;
  virtual size_t getChoiceNum() = 0;
};

class NormalPage : public Page {
 private:
  vector<Choice> choiceVector;

 public:
  NormalPage();
  NormalPage(char _type,
             size_t _pageNum,
             string _pageName,
             string _pageDirectoty,
             vector<string> _pageText,
             vector<Choice> _choiceVector);
  NormalPage(char _type,
             size_t _pageNum,
             string _pageName,
             string _pageDirectory,
             vector<Choice> _choiceVevtor);

  NormalPage(char _type, size_t _pageNum, string _pageName, string _pageDirectory);

  virtual ~NormalPage();

  void addOneChoice(const Choice & newChoice);
  virtual vector<size_t> getDestPageNumArray();
  virtual size_t getChoiceNum();
  virtual void printPage() const;  // overload << operator
};

class WinPage : public Page {
 public:
  WinPage();
  WinPage(char _type, size_t _pageNum, string _pageName, string _pageDirectory);

  virtual ~WinPage();

  virtual void addOneChoice(const Choice & newChoice);
  virtual size_t getChoiceNum();
  virtual vector<size_t> getDestPageNumArray();
  virtual void printPage() const;  // overload << operator
};

class LosePage : public Page {
 public:
  LosePage();
  LosePage(char _type, size_t _pageNum, string _pageName, string _pageDirectory);

  virtual ~LosePage();

  virtual void addOneChoice(const Choice & newChoice);
  virtual size_t getChoiceNum();
  virtual vector<size_t> getDestPageNumArray();
  virtual void printPage() const;  // overload << operator
};

class Story {
 private:
  string directory;
  vector<Page *> pageVector;

  size_t getChoiceFromUser() const;  // Get user's choice

 public:
  void printPage(size_t pageNum) const;  // print one page and check Win or Lose

  Story();
  Story(string _directory,
        int pageNumCheck = 0);  // defaultly, do not perform pagenumcheck
  Story(const Story & rhs);

  Story & operator=(const Story & rhs);
  ~Story();

  void printStory() const;      // overload << operator
  void startAdventure() const;  // strat the game
  void printWinPath() const;    // print all winning pathes
};

// function to check whether a line is blank
bool isBlank(string line);

// function to add one page
void addPage(vector<Page *> & pageVector,
             char type,
             size_t pageNum,
             string pageName,
             string pageDirectory);
// function to check whether a page number is valid
bool isValidNumber(string & line, char *& afterPageNum, size_t & pageNum);

// fucntion to check whether a line is a page declaration. If it is, then add one page.
bool isPage(string line, vector<Page *> & pageVector, string directory);

// function to add one choice
void addChoice(vector<Page *> & pageVector,
               size_t pageNum,
               size_t destPageNum,
               string text);

// fucntion to check whether a line is a choice declaration. If it is, then add one choice.
bool isChoice(string line, vector<Page *> & pageVector);

// template function to check whether a type is in an array of types
template<typename T>
bool checkTypeInArray(const T & element, const vector<T> & elementArray) {
  typename vector<T>::const_iterator it = elementArray.begin();
  while (it != elementArray.end()) {
    if (*it == element) {
      return true;
    }
    ++it;
  }

  return false;
}

// function to check all the destPageNum in choices can be matched to pageNum. And make sure every page(except page 0) is referenced at least once.
bool checkDestPageNum(const vector<Page *> & pageVector);

// function to check at least one Win page and at least one Lose page
void checkWinLosePage(const vector<Page *> & pageVector);

// function to check argc
void checkArgc(const int & argc);

// function to obtain all winning pathes
void findWinPath(list<stack<size_t> > & allWinPathes, const vector<Page *> & pageVector);

// function to print a winning path
void printOneWinPath(stack<size_t> & oneWinPath, const vector<Page *> & pageVector);

#endif
