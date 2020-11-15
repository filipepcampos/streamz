#include "Viewer.h"
#include <iostream>
#include <iomanip>

Viewer::Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform &platform) : User(nickname, name, birth_date, platform) {
    if (getAge() <= MINIMUM_VIEWER_AGE)
        throw InvalidAge(getAge());
}

std::weak_ptr<Stream> Viewer::getCurrentStream() const {
    return current_stream;
}

void Viewer::joinStream(const unsigned int id) {
    if (!current_stream.expired())
        leaveStream();
    current_stream = platform.joinStreamById(id, *this);
}

void Viewer::leaveStream() {
    if (!current_stream.expired())
        current_stream.lock()->leaveStream();
    current_stream.reset();
}

void Viewer::show() const {
    std::cout << std::left << std::setw(10) << "Viewer";
    User::show();
}

std::ostream& Viewer::print(std::ostream & os) const {
    os << "(viewer) "; User::print(os);
    return os;
}

bool Viewer::operator==(const Viewer &other) const {
    return this->getNickname() == other.getNickname();
}