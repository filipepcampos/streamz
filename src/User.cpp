#include "User.h"
#include <iostream>

User::User(const std::string &nickname, const std::string &name, const Date &birth_date) : nickname(nickname), name(name), birth_date(birth_date) {
}

std::string User::getNickname() const {
    return nickname;
}

std::string User::getName() const {
    return name;
}

Date User::getBirthDate() const {
    return birth_date;
}

unsigned User::getAge() const {
    /* IMPLEMENTAR MAIS TARDE */
    return 0;
}

void User::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    std::cout << "IMPLEMENTAR MAIS TARDE" << std::endl;
}

bool User::operator==(const User &other) const {
    return this->nickname == other.getNickname();
}