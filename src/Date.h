#ifndef STREAMZ_DATE_H
#define STREAMZ_DATE_H
#include <string>

using namespace std;

class Date {
    unsigned day;
    unsigned month;
    unsigned year;
    unsigned hours;
    unsigned minutes;
public:
    /**
     * Class constructor
     */
    Date();
    /**
     * Copy constructor
     * @param date
     */
    Date(const Date &date);
    /**
     * Another constructor
     * @param date Date in the format dd/mm/yyyy hh:mm
     */
    Date(const string &date);
    /**
     *
     * @param d1_inicial Initial date for range 1
     * @param d1_final Final date for range 1
     * @param d2_inicial Initial date for range 2
     * @param d2_final Final date for range 2
     * @return Boolean indicating if the given two date ranges overlap
     */
    friend bool checkDateIntersection(const Date d1_inicial,const Date d1_final,const Date d2_inicial,const Date d2_final);
    /**
     * Turns date into a string
     * @return String in the format dd/mm/yyyy hh:mm
     */
    string toString();
    /**
     * Calculates the difference between two dates
     * @param date Date to be subtracted
     * @return Difference between two dates
     */
    Date operator-(const Date &date);
    /**
     * Checks if one date comes before the other
     * @param d1 Date 1
     * @param d2 Date 2
     * @return Boolean indicating if Date d1 comes before Date d2
     */
    friend bool operator<(const Date &d1, const Date &d2);
};


#endif //STREAMZ_DATE_H
