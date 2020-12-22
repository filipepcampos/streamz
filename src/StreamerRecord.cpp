#include "StreamerRecord.h"


StreamerRecord::StreamerRecord(Streamer * st) : active(true) {
    streamer = st;
}

StreamerRecord::StreamerRecord(std::string &nick) : active(false) {
    nickname = nick;
}

const Streamer * StreamerRecord::getStreamer() const {
    if (active) return streamer;
    return nullptr;
}

const std::string & StreamerRecord::getNickname() const {
    if (active) return streamer->getNickname();
    return nickname;
}

void StreamerRecord::setActive(Streamer * st) {
    // TODO: CRIAR EXCEÇÃO POR JÁ ESTAR ATIVO
    active = true;
    streamer = st;
}

void StreamerRecord::setInactive(std::string &nick) {
    // TODO: CRIAR EXCEÇÃO POR JÁ ESTAR INATIVO
    active = false;
    nickname = nick;
}
