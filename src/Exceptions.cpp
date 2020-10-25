#include "Exceptions.h"

UserDoesNotExist::UserDoesNotExist(const std::string &nickname) : nickname(nickname) {
}

std::string UserDoesNotExist::getNickname() const {
    return nickname;
}

UserAlreadyExists::UserAlreadyExists(const std::string &nickname) : nickname(nickname) {
}

std::string UserAlreadyExists::getNickname() const {
    return nickname;
}

InvalidAge::InvalidAge(unsigned int age) : age(age) {
}

unsigned int InvalidAge::getAge() const {
    return age;
}

InsufficientAge::InsufficientAge(unsigned int age) : age(age) {
}

unsigned int InsufficientAge::getAge() const {
    return age;
}