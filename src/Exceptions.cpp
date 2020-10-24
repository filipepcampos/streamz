#include "Exceptions.h"

UserDoesNotExist::UserDoesNotExist(string nickname) : nickname(nickname) {
}

string UserDoesNotExist::getNickname() const {
    return nickname;
}

UserAlreadyExistst::UserAlreadyExists(string nickname) : nickname(nickname) {
}

string UserAlreadyExists::getNickname() const {
    return nickname;
}
