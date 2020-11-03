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
     * @param date Date in the format dd/mm/yyyy hh:mm
     */
    Date(const string &date);
    /**
     *
     * @param d1_inicial
     * @param d1_final
     * @param d2_inicial
     * @param d2_final
     * @return
     */
    friend bool checkDateIntersection(Date d1_inicial, Date d1_final, Date d2_inicial, Date d2_final);
    /**
     * Turns date into a string
     * @return String in the format dd/mm/yyyy hh:mm
     */
    string toString();
};


#endif //STREAMZ_DATE_H
