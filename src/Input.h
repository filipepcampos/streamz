#ifndef STREAMZ_INPUT_H
#define STREAMZ_INPUT_H
#include <string>
#include <iostream>
#include <sstream>

#define MAX_NAME_LENGHT 20
#define MAX_NICKNAME_LENGHT 10
#define MAX_TITLE_LENGHT 20

namespace input{
    std::string getRaw();
    void trimString(std::string &str);

    template <typename T>
    bool strToVar(const std::string &str, T &var){
        std::istringstream ss{str};
        ss >> var;
        if(ss.fail() || !ss.eof()){
            return false;
        }
        return true;
    }

    template <typename T>
    bool get(T &var){
        std::string str = getRaw();
        if(str.empty()){
            return false;
        }
        return strToVar(str, var);
    }
    void waitEnter();
    bool validateNickname(const std::string &nickname);
    bool validateName(const std::string &name);
    bool validateBirthDate(const std::string &date);
    bool validateTitle(const std::string &title);
}


#endif //STREAMZ_INPUT_H
