#include "readFreq.h"

#include <stdio.h>

#include <cstdlib>
#include <fstream>

void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * arr = new uint64_t[257];

  for (int i = 0; i < 257; i++) {
    arr[i] = 0;
  }

  std::ifstream myfile;
  myfile.open(fname);

  char c;
  while (myfile.get(c)) {
    //    cout << c << "\n";
    unsigned char c2 = c;
    int index = int(c2);
    //cout << index << "\n\n";
    arr[index]++;
  }

  arr[256] = 1;

  //  assert(arr[256] == 1);
  myfile.close();

  //cout << arr[65];
  // p = arr;

  return arr;
}
