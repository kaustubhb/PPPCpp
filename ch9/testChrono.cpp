#include "std_lib_facilities.h"
#include "Chrono.h"

int main()
{
  chrono::Date date(1978, chrono::Month::jun, 25);
  cout << date;
}