#include "User.h"
#include "Stream.h"
#include <iostream>
#include <iomanip>

User::User(const std::string &nickname, const std::string &name, const Date &birth_date, Platform & platform) : nickname(nickname), name(name), birth_date(birth_date), platform(platform) {
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
    Date today;
    return ((today.getYear() - birth_date.getYear()) * 10000 + (today.getMonth() - birth_date.getMonth()) * 100 + (today.getDay() - birth_date.getDay())) / 10000;
}

void User::show() const {
    std::cout << std::setw(10) << nickname << std::setw(20) << name << std::endl;
}

std::ostream& User::print(std::ostream & os) const {
    os << getNickname() << " " << getName() << std::endl;
    os << "    " << (current_stream.expired() ? 0 : current_stream.lock()->getId()) << " " << getBirthDate().toString() << std::endl;
    return os;
}

bool User::operator==(const User &other) const {
    return this->nickname == other.getNickname();
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    return user.print(os);
}

bool User::inStream() const {
    return !current_stream.expired();
}

bool User::inPrivateStream() const {
    return inStream() && !current_stream.lock()->getIsPublic();
}
