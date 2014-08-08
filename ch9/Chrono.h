namespace chrono {
  enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
  };
  enum class Day {
    sunday, monday, tuesday, wednesday, thursday, friday, saturday
  };

  class Date {
  public:
    class Invalid {};   // to throw as exception
    Date (int y, Month m, int d);
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
    int y;
    Month m;
    int d;
  };

  bool isDate (int y, Month m, int d);
  bool leapYear (int y);
  bool operator==(const Date &d1, const Date &d2);
  bool operator!=(const Date &d1, const Date &d2);
  ostream& operator<<(ostream &os, const Date &d);
  istream& operator>>(istream &is, Date &d);
}   // chrono