#include <iostream>
#include <sstream>
#include <string>

class Date {
private:
    int day;
    int month;
    int year;
    int seconds;
    int minutes;
    int hours;

    static bool isLeapYear(int year) {
        return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
    }

    static int daysInMonth(int month, int year) {
        switch (month) {
            case 4: case 6: case 9: case 11: return 30;
            case 2: return isLeapYear(year) ? 29 : 28;
            default: return 31;
        }
    }

public:
    Date() : day(0), month(0), year(0), seconds(0), minutes(0), hours(0) {}
    Date(int day, int month, int year, int hours = 0, int minutes = 0, int seconds = 0)
        : day(day), month(month), year(year), seconds(seconds), minutes(minutes), hours(hours) {}

    void setDateTimeFromSeconds(long long totalSeconds) {
        // Reset date and time to epoch start (considering 1970-01-01 00:00:00 for simplicity)
        year = 1970;
        month = 1;
        day = 1;
        hours = 0;
        minutes = 0;
        seconds = 0;

        // Update date and time based on totalSeconds
        long long days = totalSeconds / (24 * 3600);
        totalSeconds %= (24 * 3600);
        hours = totalSeconds / 3600;
        totalSeconds %= 3600;
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;

        while (days > 0) {
            int daysInCurrentMonth = daysInMonth(month, year);
            if (days >= daysInCurrentMonth) {
                days -= daysInCurrentMonth;
                month++;
                if (month > 12) {
                    month = 1;
                    year++;
                }
            } else {
                day += days;
                days = 0;
            }
        }
    }

    std::string format(const std::string& formatString) {
        std::ostringstream formattedDate;
        for (size_t i = 0; i < formatString.length(); ++i) {
            if (formatString[i] == '%' && i + 1 < formatString.length()) {
                switch (formatString[i + 1]) {
                    case 'd': formattedDate << day; break;
                    case 'm': formattedDate << month; break;
                    case 'Y': formattedDate << year; break;
                    case 'H': formattedDate << hours; break;
                    case 'M': formattedDate << minutes; break;
                    case 'S': formattedDate << seconds; break;
                    default: formattedDate << formatString[i]; break;
                }
                ++i; // Skip the format specifier
            } else {
                formattedDate << formatString[i];
            }
        }
        return formattedDate.str();
    }
};