#include "User.h"
#include <iostream>

User::User(const std::string &nickname, const std::string &name, const Date &birth_date, Platform * platform) : nickname(nickname), name(name), birth_date(birth_date), platform(platform) {
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
    return stoi((Date() - birth_date).toString().substr(6,4));
}

void User::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    std::cout << "IMPLEMENTAR MAIS TARDE" << std::endl;
}

std::ostream& User::print(std::ostream & os) const {
    return os;
}

bool User::operator==(const User &other) const {
    return this->nickname == other.getNickname();
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    user.print(os);
    return os;
}
