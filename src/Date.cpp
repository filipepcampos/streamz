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