#include "Viewer.h"
#include <iostream>

Viewer::Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform *platform) : User(nickname, name, birth_date, platform) {
}

std::weak_ptr<Stream> Viewer::getCurrentStream() const {
    return current_stream;
}

void Viewer::joinStream(const unsigned int id) {
    current_stream = platform->joinStreamById(id, *this);
    current_stream.lock()->joinStream();
}

void Viewer::leaveStream() {
    current_stream.lock()->leaveStream();
    current_stream.reset();
}

void Viewer::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    std::cout << "IMPLEMENTAR MAIS TARDE" << std::endl;
}

std::ostream& Viewer::print(std::ostream & os) const {
    //os << "viewer " << getNickname() << " " << getAge() << " " << getBirthDate().toString() << " ";
    os << (current_stream.expired() ? 0 : current_stream.lock()->getId()) << " " << getName();
}

bool Viewer::operator==(const Viewer &other) const {
    return this->getNickname() == other.getNickname();
}