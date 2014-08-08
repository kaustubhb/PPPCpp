#include "std_lib_facilities.h"
#include "Chrono.h"
  
// ostream& operator<<(ostream &os, const chrono::Date &d)
// {
//   return os << '(' << d.year() << ',' << int(d.month())
//             << ',' << d.day() <<')';
// }

int main()
{
  chrono::Date date(1978, chrono::Month::jun, 25);
  cout << date << endl; 
}