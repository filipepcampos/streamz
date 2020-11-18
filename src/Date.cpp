#include "Date.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

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


Date::Date(const string &date){
    istringstream ss{date};
    unsigned dia, mes, ano, horas, minutos;
    char separator;
    struct tm  timeinfo;
    if(date.length() > 10){
        ss >> dia >> separator >> mes >> separator >> ano >> horas >> separator >> minutos;
        timeinfo.tm_year = ano - 1900;
        timeinfo.tm_mon = mes - 1;
        timeinfo.tm_mday = dia;
        timeinfo.tm_hour = horas;
        timeinfo.tm_min = minutos;
        timeinfo.tm_isdst = 0;
        timeinfo.tm_sec = 0;
        timeinfo.tm_wday = 0;
        timeinfo.tm_yday = 0;
        if (mktime(&timeinfo) == -1)
            throw InvalidDate(date);
    }
    else{
        ss >> dia >> separator >> mes >> separator >> ano;
        horas = 0;
        minutos = 0;
        timeinfo.tm_year = ano - 1900;
        timeinfo.tm_mon = mes - 1;
        timeinfo.tm_mday = dia;
        timeinfo.tm_hour = horas;
        timeinfo.tm_min = minutos;
        timeinfo.tm_isdst = 0;
        timeinfo.tm_sec = 0;
        timeinfo.tm_wday = 0;
        timeinfo.tm_yday = 0;
        if (mktime(&timeinfo) == -1)
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

string Date::toString() const {
    stringstream ss;
    string dia = to_string(day);
    string mes = to_string(month);
    string ano = to_string(year);
    string horas = to_string(hours);
    string minutos = to_string(minutes);
    ss << setfill('0') << setw(2) << dia << "/" << setw(2) << mes << "/" << setw(4) << ano << " " << setw(2) << horas << ":" << setw(2) << minutos;
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