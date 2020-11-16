#include "Input.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include "Date.h"

namespace input{
    std::string getRaw(){
        std::string str;
        std::cout << "> ";
        std::getline(std::cin, str);
        trimString(str);
        std::cout << std::endl;
        return str;
    }

    void trimString(std::string &str) {
        // Remove whitespace from start and end of the string
        auto front = std::find_if_not(str.begin(),str.end(),[](int c){
            return std::isspace(c);
        });
        auto back = std::find_if_not(str.rbegin(),str.rend(),[](int c){
            return std::isspace(c);
        }).base();
        str = back<=front ? std::string() : std::string(front, back);

        // Convert multiple whitespaces into a single one
        // For example "Viewer   Complete      Name" would become "Viewer Complete Name"
        auto new_end = std::unique(str.begin(), str.end(), [](char a, char b){
            return (a==b) && (a==' ');
        });
        str.erase(new_end, str.end());
    }

    bool validateNickname(const std::string &nickname) {
        if(nickname.empty()){
            std::cout << "Nickname can't be empty" << std::endl;
            return false;
        }
        if(nickname.length() > 20){
            std::cout << "Nickname can't exceed 20 characters " << std::endl;
            return false;
        }
        bool has_alpha;
        for(auto c : nickname){
            if(!isalnum(c)){
                std::cout << "Nickname can only contain alphanumeric characters, one of which must be alphabetic" << std::endl;
                return false;
            }
            if(isalpha(c)){
                has_alpha = true;
            }
        }
        return has_alpha;
    }

    bool validateName(const std::string &name) {
        if(name.empty()){
            std::cout << "Name can't be empty" << std::endl;
            return false;
        }
        for(auto c : name){
            if(!isalpha(c) && c != ' '){
                std::cout << "Name can only contain alphabetic characters and spaces" << std::endl;
                return false;
            }
        }
        return true;
    }

    bool validateBirthDate(const std::string &date){
        if(!(Date(date) < Date())){ // Users from the future are not allowed
            return false;
        }
        return true;
    }
}

