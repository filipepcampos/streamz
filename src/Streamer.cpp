#include "Streamer.h"
#include "Exceptions.h"
#include <iostream>
#include <algorithm>

Streamer::Streamer(const std::string &nickname, const std::string &name, const Date &birth_date) : User(nickname, name, birth_date) {
}

Streamer::Streamer(const std::string &nickname, const std::string &name, const Date &birth_date, const std::vector<unsigned int> &streams_history) : User(nickname, name, birth_date) {
    this->streams_history = streams_history;
}

std::vector<unsigned int> Streamer::getStreamsHistory() const {
    return streams_history;
}

void Streamer::addStream(const unsigned int id) {
    streams_history.push_back(id);
}

void Streamer::removeStream(const unsigned int id) {
    unsigned int left = 0, right = streams_history.size() - 1, middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (streams_history.at(middle) < id)
            left = middle + 1;
        else if (id < streams_history.at(middle))
            right = middle - 1;
        else {
            streams_history.erase(streams_history.begin() + middle);
            return;
        }
    }
    throw StreamDoesNotExist(id);
}

void Streamer::show() const {
    /* IMPLEMENTAR MAIS TARDE */
    std::cout << "IMPLEMENTAR MAIS TARDE" << std::endl;
}

bool Streamer::operator==(const Streamer &other) const {
    return this->getNickname() == other.getNickname();
}