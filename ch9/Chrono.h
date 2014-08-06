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