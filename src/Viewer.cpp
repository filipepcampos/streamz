#include "Viewer.h"
#include <iostream>

Viewer::Viewer(const std::string &nickname, const std::string &name, const Date &birth_date) : User(nickname, name, birth_date) {
}

void Viewer::joinStream(const std::shared_ptr<Stream> &stream) {
    current_stream = stream;
}

std::weak_ptr<Stream> Viewer::getCurrentStream() const {
    return current_stream;
}

void Viewer::leaveStream() {
    current_stream.reset();
}

void Viewer::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    std::cout << "IMPLEMENTAR MAIS TARDE" << std::endl;
}

bool Viewer::operator==(const Viewer &other) const {
    return this->getNickname() == other.getNickname();
}