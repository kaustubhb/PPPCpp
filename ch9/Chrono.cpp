namespace chrono {
  enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
  };

  class Date {
  public:
    class Invalid {};   // to throw as exception
    Date (int y, Month m, ind d);
    Date();

    // default copy operations are fine
    // non-modifying operations
    int day() const { return d; }
    Month month() const { return m; }
    int year() const { return y; }

    // modifying operations
    void add_day (int n);
    void add_month (int n);
    void add_year (int n);

  private:
    int d;
    Month m;
    int y;
  };

  bool isDate (int y, Month m, int y);
  bool leapYear (int y);
  bool operator==(const Date &d1, const Date &d2);
  bool operator!=(const Date &d1, const Date &d2);
  ostream& operator<<(ostream &os, const Date &d);
  istream& operator>>(istream &os, Date &d);
}   // chrono


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


}




























