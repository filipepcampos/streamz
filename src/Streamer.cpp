#include "Streamer.h"
#include <iostream>

Streamer::Streamer(const std::string &nickname, const std::string &name, const Date &birth_date) : User(nickname, name, birth_date) {
}

Streamer::Streamer(const std::string &nickname, const std::string &name, const Date &birth_date, const std::vector<unsigned int> &streams_history) : User(nickname, name, birth_date) {
    this->streams_history = streams_history;
}

const std::vector<unsigned int> & Streamer::getStreamsHistory() const {
    return streams_history;
}

void Streamer::addStream(const unsigned int id) {
    streams_history.push_back(id);
}
void Streamer::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    std::cout << "IMPLEMENTAR MAIS TARDE" << std::endl;
}

bool Streamer::operator==(const Streamer &other) const {
    return this->getNickname() == other.getNickname();
}