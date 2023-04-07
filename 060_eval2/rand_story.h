#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "provided.h"

// Functions for step1
/* This function is uesd to open the file from the given fileName.It also checks whether this file can be successfully opend. 

Parameter fileName: A string of the name of the file to be opend.

return: A file stream points at the opened file if it can be successfully opend.
*/
FILE * openFile(char * fileName);

/* This function is uesd to get all the lines in the file stream and store the number of lines in *numberOfLines. 

Parameter file: A file stream to be read
Parameter numberOfLines: A pointer that points to a size_t value, which is used to store the number of lines in the file.

return: A pointer to all lines read from the file.
*/
char ** getLinesInFile(FILE * file, size_t * numberOfLines);

/* This function is uesd to get all indexs of character undersocre '_' in a given line and stores them in an array. 

Parameter line: The line, which is a string, to be read.
Parameter numberOfUnderscore: A pointer that points to a size_t value, which is used to store the number of underscores in the line.

return: An array of all indexs of underscore read from the line.
*/
size_t * getIndexOfUnderscore(char * line, size_t * numberOfUnderscore);

/* This function is used to check all given lines to see that whether they all have even number of underscores. 

Parameter lines: Lines to be checkd.
Parameter numberOfLines: How many lines are given, which is used to control the iteration. 

*/
void checkLines(char ** lines, size_t numberOfLines);

/* This function is used to check whether the given number of underscores are even(including 0).

Parameter numberOfUnderscore: The number of the underscores to be checked. 

*/
void checkNumberOfUnderscore(size_t numberOfUnderscore);

/* This function is used to get all the names of the categories that appear in the given line.  

Parameter line: The line, which is a string, to be read.
Parameter indexOfUnderscore: An array of all indexs of underscore in that line.
Parameter numberOfUnderscore: The number of underscores in that line. 

return: An array of all the names of the categories that appear in the given line.
*/
char ** getCategories(char * line, size_t * indexOfUnderscore, size_t numberOfUnderscore);

/* This function is used to get all the other sections (fragments except for blocks) that appear in the given line.  

Parameter line: The line, which is a string, to be read.
Parameter indexOfUnderscore: An array of all indexs of underscore in that line.
Parameter numberOfUnderscore: The number of underscores in that line. 

return: An array of all the other sections that appear in the given line.
*/
char ** getOtherSections(char * line,
                         size_t * indexOfUnderscore,
                         size_t numberOfUnderscore);

/* This function is used to get the size of the new line after replacing all blocks with "cat".
  
Parameter categories: An array of all the names of the categories that appear in the given line.
Parameter sections: An array of all the sections that appear in one line.
Parameter numberOfUnderscore: The number of underscores in that line. 

return: The size of the new line after replacing all blocks with "cat". 
*/
size_t getReplacedLineSize(char ** categories,
                           char ** sections,
                           size_t numberOfUnderscore);

/* This function is used to replace all blocks in the given line with "cat".  

Parameter line: The line to be replaced.

return: A new line, which is a string, after replacing all blocks in the given line with "cat".
*/
char * replaceBlocks(char * line);

/* This function is used to print the story, using  an array of lines and the number of lines.  

Parameter lines: An array of lines read from the file.
Parameter numberOfLines: The size of the array (aka,lines).

*/
void printStory(char ** lines, size_t numberOfLines);

/* This function is used to free the memroy allocated to an array of lines.  

Parameter lines: An array of lines read from the file.
Parameter numberOfLines: The size of the array (aka,lines).

*/
void freeLines(char ** lines, size_t numberOfLines);

// Functions for step2

/* This function is used to check whether all lines have at least one character colon ':'.   

Parameter lines: An array of lines read from the file.
Parameter numberOfLines: The size of the array (aka,lines).

*/
void checkColons(char ** lines, size_t numberOfLines);

/* This function is used to get the name for a category in the given line.   

Parameter line: The line, which is a string, to be read.

return: The name for a category in the given line.
*/
char * getCategoryName(char * line);

/* This function is used to get a word for a category in the given line.   

Parameter line: The line, which is a string, to be read.

return: A word for a category in the given line.
*/
char * getCategoryWord(char * line);

/* This function is used check whether a new line has appeared in an array of lines.   

Parameter lines: An array of lines.
Parameter numberOfLines: The size of the array (aka,lines).
Parameter newLine: The new line to be checkd.

return: Return 1 if the new line has not appeared in the array of lines. Otherwise, return 0.
*/
int checkNewLineDifference(char ** lines, size_t numberOfLines, char * newLine);

/* This function is used to get all the names for the categories for the given array of lines.   

Parameter lines: An array of lines.
Parameter numberOfLines: The size of the array (aka,lines).
Parameter numberOfNames: A pointer to a size_t value that is uesd to store the number of names appears in the given array of lines.

return: An array of names for the categories for the given array of lines.
*/
char ** getNamesForCategories(char ** lines,
                              size_t numberOfLines,
                              size_t * numberOfNames);

/* This function is used to get all the words for the given name of a category for the given array of lines.   

Parameter lines: An array of lines.
Parameter numberOfLines: The size of the array (aka,lines).
Parameter name: The name for the words.
Parameter numberOfWords: A pointer to a size_t value that is uesd to store the number of words appears in the given array of lines.

return: An array of words for the categories for the given array of lines.
*/
char ** getWordsForName(char ** lines,
                        size_t numberOfLines,
                        char * name,
                        size_t * numberOfWords);

/* This function is used to create a category_t struct for the given name.   

Parameter lines: An array of lines.
Parameter numberOfLines: The size of the array (aka,lines).
Parameter name: The name for the words.
Parameter numberOfWords: A pointer to a size_t value that is uesd to store the number of words appears in the given array of lines.

return: A pointer to the created category_t struct.
*/
category_t * createCategoryForName(char ** lines,
                                   size_t numberOfLines,
                                   char * name,
                                   size_t * numberOfWords);

/* This function is used to create a catarray_t struct for the given array of lines.   

Parameter lines: An array of lines.
Parameter numberOfLines: The size of the array (aka,lines).
Parameter numberOfCategories: A pointer to a size_t value that is uesd to store the number of categories.

return: A pointer to the created catarray_t struct.
*/
catarray_t * createCategoryArray(char ** lines,
                                 size_t numberOfLines,
                                 size_t * numberOfCategories);

/* This function is used to free the memroy allocated to a category_t struct.  

Parameter category: The category_t struct needs to be freed.

*/
void freeCategory(category_t category);

/* This function is used to free the memroy allocated to a catarray_t struct.  

Parameter categoryArray: A pointer to the catarray_t struct needs to be freed.

*/
void freeCategoryArray(catarray_t * categoryArray);

// Functions for step3

/* This function is used to check whether a name is in the categoryArray.  

Parameter name: The name to be checked.
Parameter categoryArray: A pointer to the catarray_t struct.

return: Return 1 if the name is in the categoryArray. Otherwise, return 0.
*/
int checkNameInCatArray(char * name, catarray_t * categoryArray);

/* This function is used to check whether a name is a valid integer.  

Parameter name: The name to be checked.

return: Return 1 if the name is a valid integer. Otherwise, return 0.
*/
int checkValidInteger(char * name);

/* This function is used to get a valid integer from name.  

Parameter name: The name to be coverted.

return: The corresponding valid integer.
*/
size_t getValidInteger(char * validIntegerName);

/* This function is used to check whether a name is in categoryArray or is a valid integer.  

Parameter name: The name to be checked.
Parameter categoryArray: A pointer to the catarray_t struct.

return: Return 1 if the name is in categoryArray, return 0 if the name is a valid integer. Otherwise, cause the programe to exit.
*/
int checkInArrayOrValidInt(char * name, catarray_t * categoryArray);

/* This function is used to check the order of appearance and amount of the given valid integer.  

Parameter validInt: The valid integer to be checked.
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.

*/
void checkValidIntOrderAndAmount(size_t validInt, category_t * usedWords);

/* This function is used to add a word to usedWords.  

Parameter word: The word to be added.
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.

*/
void addOneUsedWord(const char * word, category_t * usedWords);

/* This function is used to get the size of the new line after replacing all blocks.
  
Parameter names: An array of all the names of the categories that appear in the given line.
Parameter sections: An array of all the sections that appear in that line.
Parameter numberOfUnderscore: The number of underscores in that line. 
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.
Parameter categoryArray: A pointer to the catarray_t struct.
Parameter noReuse: Whether to trigger "no-reuse" fucntion or not. If noReuse is 1, then the fucntion is triggered.

return: The size of the new line after replacing all blocks. 
*/
size_t getNewLineSize(char ** names,
                      char ** sections,
                      size_t numberOfUnderscore,
                      category_t * usedWords,
                      catarray_t * categoryArray,
                      int noReuse);

/* This function is used to get a new line by replacing all blocks in the given line.  

Parameter line: The line to be replaced.
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.
Parameter categoryArray: A pointer to the catarray_t struct.
Parameter noReuse: Whether to trigger "no-reuse" fucntion or not. If noReuse is 1, then the fucntion is triggered.

return: A new line, which is a string, after replacing all blocks in the given line.
*/
char * getNewLine(char * line,
                  category_t * usedWords,
                  catarray_t * categoryArray,
                  int noReuse);

/* This function is used to print the story.  

Parameter lines: An array of lines read from the file.
Parameter numberOfLines: The size of the array (aka,lines).
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.
Parameter categoryArray: A pointer to the catarray_t struct.
Parameter noReuse: Whether to trigger "no-reuse" fucntion or not. If noReuse is 1, then the fucntion is triggered.

*/
void printNewStory(char ** lines,
                   size_t numberOfLines,
                   category_t * usedWords,
                   catarray_t * categoryArray,
                   int noReuse);

/* This function is used to free the memroy allocated to usedWords.  

Parameter usedWords: The category_t struct needs to be freed.

*/
void freeUsedWords(category_t usedWords);

// Functions for step4

/* This function is used to check whether a word has been used.  

Parameter word: The word to be checked.
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.

return: Return 1 if the word has been used. Otherwise return 0.
*/
int checkWordReuse(const char * word, category_t * usedWord);

/* This function is used to check whether there are words left that are not used.  

Parameter name: The name in the block.
Parameter usedWords: A pointer to the category_t struct that is used to track all the used words.
Parameter categoryArray: A pointer to the catarray_t struct.

*/
void checkWordsLeft(char * name, category_t * usedWords, catarray_t * categoryArray);

#endif
