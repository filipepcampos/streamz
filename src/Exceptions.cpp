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
