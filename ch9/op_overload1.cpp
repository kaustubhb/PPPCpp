#include "std_lib_facilities.h"

enum class Month {
  jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

Month operator++(Month &m)
{
  m = (m == Month::dec) ? Month::jan : Month(int(m)+1);
  return m;
}

int main()
{
  Month m = Month::dec;
  ++m;
  cout << int(m) << endl;
}