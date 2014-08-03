#include "std_lib_facilities.h"

class X
{
  int x;
public:
  X(int i)
  {
    cout << x << endl;
  }
};

int main()
{
  // int x = {1};
  // cout << x << endl;

  X(10);
}