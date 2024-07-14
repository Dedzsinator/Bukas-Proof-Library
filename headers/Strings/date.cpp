#include <iostream>

class Date {
  private:
    int day;
    int month;
    int year;

  public:
    Date();
    Date(int day, int month, int year);
    Date(const Date& other);
    Date& operator=(const Date& other);
    void set_day(int day);
    void set_month(int month);
    void set_year(int year);
    int get_day();
    int get_month();
    int get_year();
    ~Date();
};
