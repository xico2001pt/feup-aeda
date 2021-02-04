#ifndef STREAMZ_DATE_H
#define STREAMZ_DATE_H
#include <string>
#include "Exceptions.h"

class Date {
    unsigned day;
    unsigned month;
    unsigned year;
    unsigned hours;
    unsigned minutes;
public:
    /**
     * Class constructor, sets date as current date
     */
    Date();
    /**
     * Copy constructor
     * @param date
     */
    Date(const Date &date);
    /**
     * Constructor from string
     * @param date Date in the format dd/mm/yyyy hh:mm
     */
    Date(const std::string &date);
    /**
     *
     * @param d1_inicial Initial date for range 1
     * @param d1_final Final date for range 1
     * @param d2_inicial Initial date for range 2
     * @param d2_final Final date for range 2
     * @return Boolean indicating if the given two date ranges overlap
     */
    friend bool checkDateIntersection(const Date &d1_inicial,const Date &d1_final,const Date &d2_inicial,const Date &d2_final);
    /**
     * Gets year
     * @return Year of the date
     */
    unsigned getYear() const;
    /**
     * Gets month
     * @return Month of the date
     */
    unsigned getMonth() const;
    /**
     * Gets day
     * @return Day of the date
     */
    unsigned getDay() const;
    /**
     * Gets hours
     * @return Hours of the date
     */
    unsigned getHours() const;
    /**
     * Gets minutes
     * @return Minutes of the date
     */
    unsigned getMinutes() const;
    /**
     * Turns date into a string
     * @param includeHours Boolean indicating if hours and minutes should be printed
     * @return String in the format dd/mm/yyyy hh:mm
     */
    std::string toString(bool includeHours = true) const;
    /**
     * Checks if one date comes before the other
     * @param d1 Date 1
     * @param d2 Date 2
     * @return Boolean indicating if Date d1 comes before Date d2
     */
    friend bool operator<(const Date &d1, const Date &d2);
};


#endif //STREAMZ_DATE_H
