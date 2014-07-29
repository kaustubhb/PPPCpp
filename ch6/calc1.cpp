#include "std_lib_facilities.h"

int main()
{
  int lval, rval;
  char op;
  int result;

  cin >> lval;
  while (cin >> op)
  {
    cin >> rval;
    switch (op)
    {
      case '+':
        lval += rval;
        break;
      case '-':
        lval -= rval;
        break;
      case '*':
        lval *= rval;
        break;
      case '/':
        lval /= rval;
        break;
    }
  }

  cout << lval << endl;
  return 0;
}