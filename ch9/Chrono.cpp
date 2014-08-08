#include "std_lib_facilities.h"
#include "Chrono.h"

namespace chrono {

  // member function definitions
  Date::Date(int yy, Month mm, int dd): y{yy}, m{mm}, d{dd}
  {
    if(!isDate(y,m,d))
      throw Invalid{};    // throw invalid object as exception
  }

  const Date& default_date() {
    static Date dd{2001, Month::jan, 1};
    return dd;
  }

  Date::Date(): y{default_date().y}, 
                m{default_date().m}, 
                d{default_date().d}
  { }

  void Date::add_day(int n) {
    //TODO
  }

  void Date::add_month(int n) {
    //TODO
  }

  void Date::add_year(int n) {
    if(m == Month::feb && d == 29 && !leapYear(y+n)) {
      m = Month::mar;
      d = 1;
    }
    y += n;
  }

  // helper functions
  bool isDate(int y, Month m, int d) {
    if(y < 1) return false;
    if(m < Month::jan || m > Month::dec)
      return false;
    if(d < 1 || d > 31)
      return false;

    switch(m)
    {
      case Month::feb:
        if(d > 29 && leapYear(y))
          return false;
        if(d > 28)
          return false;

      case Month::apr: case Month::jun: 
      case Month::sep: case Month::nov:
        if(d > 30)
          return false;
      default:
        return true;
    }  
  }

  bool leapYear (int y)
  {
    return y%400 == 0 || (y%4 == 0 && y%100 != 0);
  }
  bool operator==(const Date &d1, const Date &d2)
  {
    return (d1.year() == d2.year() &&
            d1.month() == d2.month() &&
            d1.day() == d2.day());
  }

  bool operator!=(const Date &d1, const Date &d2)
  {
    return !(d1 == d2);
  }

  ostream& operator<<(ostream &os, const Date &d)
  {
    return os << '(' << d.year() << ',' << int(d.month())
              << ',' << d.day() <<')';
  }

  istream& operator>>(istream &is, Date &dd)
  {
    int y,m,d;
    char c1,c2,c3,c4;
    is >> c1 >> y >> c2 >> m >> c3 >> d >> c4;
    if (!is)
      return is;
    if(c1 != '(' || c2 != ',' || c3 != ',' || c4 != ')') {
      is.clear(ios_base::failbit);
      return is;
    }
    dd = Date{y,Month(m),d};
    return is;
  }

  Day dayOfWeek(const Date& d) {
    throw;
  }

  Date nextSunday(const Date& d) {
    throw;
  }

  Date nextWeekday(const Date& d) {
    throw;
  }
}




























