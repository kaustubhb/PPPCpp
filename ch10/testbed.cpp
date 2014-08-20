#include "std_lib_facilities.h"

int main() {
  ifstream is("Makefile");
  is.close();
  is.open("std_lib_facilities.h");
  string str;
  while(is >> str)
    cout << str << endl;
}
