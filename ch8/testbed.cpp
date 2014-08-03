#include "std_lib_facilities.h"
#include <cmath>

int helper(int x)
{
  return x*x;
}

constexpr int incr(int x)
{
  return helper(x);
}

int main()
{
  int i;
  cin >> i;
  int j = incr(i);
  constexpr int k = helper(10);
}