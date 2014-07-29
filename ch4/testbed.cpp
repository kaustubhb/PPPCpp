#include "std_lib_facilities.h"
#include <vector>

int main()
{
  // int i;
  // cin >> i;
  // const int max = i;
  // constexpr int x = max+2;
  // cout << x << endl;

  // int i{};
  // cout << i << endl;

  vector<int> v{1,2,3,4};
  for(int i:v)
    cout << i << endl;

  int arr[] = {5,6,7,8};
  for(int i:arr)
    cout << i << endl;
}