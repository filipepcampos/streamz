#include "Date.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>


using namespace std;

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
    day = date.day;
    month = date.month;
    year = date.year;
    hours = date.hours;
    minutes = date.minutes;
}

Date::Date(const string &date){
    stringstream ss;
    unsigned dia, mes, ano, horas, minutos;
    char separator;
    ss << date;
    ss >> dia >> separator >> mes >> separator >> ano >> horas >> separator >> minutos;
    ss.ignore(100, '\n');
    ss.clear();
    day = dia;
    month = mes;
    year = ano;
    hours = horas;
    minutes = minutos;
}

string Date::toString(){
    stringstream ss;
    string dia = to_string(day);
    string mes = to_string(month);
    string ano = to_string(year);
    string horas = to_string(hours);
    string minutos = to_string(minutes);
    ss << setfill('0') << setw(2) << dia << "/" << setw(2) << mes << "/" << ano << " " << setw(2) << horas << ":" << setw(2) << minutos;
    return ss.str();
}

Date Date::operator-(const Date &date) {
    int months[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

    if (date.day > day) {
        day = day + months[date.month - 1];
        month = month - 1;
    }

    if (date.month > month) {
        year = year - 1;
        month = month + 12;
    }
    Date result("00/00/0000 00:00");
    result.day = day - date.day;
    result.month = month - date.month;
    result.year = year - date.year;
    return result;
}

bool operator<(const Date &d1, const Date &d2){
    if(d1.year == d2.year){
        if(d1.month == d2.month){
            int d1_total_minutes = d1.day * 1440 + d1.hours * 60 + d1.minutes;
            int d2_total_minutes = d2.day * 1440 + d2.hours * 60 + d2.minutes;
            return d1_total_minutes < d2_total_minutes;
        }
        return d1.month < d2.month;
    }
    return d1.year < d2.year;
}

bool checkDateIntersection(const Date d1_inicial,const Date d1_final,const Date d2_inicial,const Date d2_final){
    return (!(d2_final < d1_inicial) && !(d1_final < d2_inicial));
}