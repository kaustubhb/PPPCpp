#include "std_lib_facilities.h"

class Bad_area {};

int area(int length, int width)
{
  if (length < 0 || width < 0)
    throw Bad_area();
  return length * width;
}

int main()
{
  try {
    cout << area(-10,20) << endl;  
  }
  catch(Bad_area) {
    cout << "Wrong arguments to area" << endl;
  }
}
  