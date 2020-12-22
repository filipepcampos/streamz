#ifndef STREAMZ_STREAMERRECORD_H
#define STREAMZ_STREAMERRECORD_H
#include "Streamer.h"
#include <string>
class StreamerRecord {
    union {
        Streamer * streamer;
        std::string nickname;
    };
    bool active;
public:
    explicit StreamerRecord(Streamer * st);
    explicit StreamerRecord(std::string &nick);
    const Streamer * getStreamer() const;
    const std::string & getNickname() const;
    void setActive(Streamer * st);
    void setInactive(std::string &nick);
};

#endif //STREAMZ_STREAMERRECORD_H
