#include "std_lib_facilities.h"

class X
{
public:
  int x;

  X(int i)
  {
    cout << x << endl;
  }

  X() {}
};

int main()
{
  // int x = {1};
  // cout << x << endl;

  X obj(10);
  cout << obj.x << endl;
}