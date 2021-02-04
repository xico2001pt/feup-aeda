#include "Date.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <vector>

Date::Date(){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    day = ltm->tm_mday;
    month = 1 + ltm->tm_mon;
    year = 1900 + ltm->tm_year;
    hours = ltm->tm_hour;
    minutes = ltm->tm_min;
}

Date::Date(const Date &date){
    day = date.getDay();
    month = date.getMonth();
    year = date.getYear();
    hours = date.getHours();
    minutes = date.getMinutes();
}


Date::Date(const std::string &date){
    std::istringstream ss{date};
    unsigned dia, mes, ano, horas, minutos;
    char separator;
    std::vector<unsigned> months {31,28,31,30,31,30,31,31,30,31,30,31};
    if(date.length() > 10){
        ss >> dia >> separator >> mes >> separator >> ano >> horas >> separator >> minutos;
        if ( ( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 )
            months[1] = 29;
        if (mes > 12 || dia > months[mes - 1] || horas > 23 || minutos > 59) {
            throw InvalidDate(date);
        }
    }
    else if (date.length() <= 10 && date.length() > 7){
        ss >> dia >> separator >> mes >> separator >> ano;
        if ( ( ano % 4 == 0 && ano % 100 != 0 ) || ano % 400 == 0 )
            months[1] = 29;
        if (mes > 12 || dia > months[mes - 1])
            throw InvalidDate(date);
        horas = 0;
        minutos = 0;
    }
    else{
        throw InvalidDate(date);
    }
    ss.ignore(100, '\n');
    ss.clear();
    day = dia;
    month = mes;
    year = ano;
    hours = horas;
    minutes = minutos;
}

std::string Date::toString(bool includeHours) const {
    std::stringstream ss;
    std::string dia = std::to_string(day);
    std::string mes = std::to_string(month);
    std::string ano = std::to_string(year);
    std::string horas = std::to_string(hours);
    std::string minutos = std::to_string(minutes);
    ss << std::setfill('0') << std::setw(2) << dia << "/" << std::setw(2) << mes << "/" << std::setw(4) << ano;
    if (includeHours){
        ss << std::setfill('0') << " " << std::setw(2) << horas << ":" << std::setw(2) << minutos;
    }
    return ss.str();
}

unsigned Date::getYear() const {
    return year;
}

unsigned Date::getMonth() const {
    return month;
}

unsigned Date::getDay() const {
    return day;
}

unsigned Date::getHours() const {
    return hours;
}

unsigned Date::getMinutes() const {
    return minutes;
}

bool operator<(const Date &d1, const Date &d2) {
    if(d1.getYear() == d2.getYear()){
        if(d1.getMonth() == d2.getMonth()){
            int d1_total_minutes = d1.getDay() * 1440 + d1.getHours() * 60 + d1.getMinutes();
            int d2_total_minutes = d2.getDay() * 1440 + d2.getHours() * 60 + d2.getMinutes();
            return d1_total_minutes < d2_total_minutes;
        }
        return d1.getMonth() < d2.getMonth();
    }
    return d1.getYear() < d2.getYear();
}

bool checkDateIntersection(const Date &d1_inicial,const Date &d1_final,const Date &d2_inicial,const Date &d2_final) {
    return (!(d2_final < d1_inicial) && !(d1_final < d2_inicial));
}