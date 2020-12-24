#ifndef STREAMZ_STREAMERRECORD_H
#define STREAMZ_STREAMERRECORD_H
#include <string>

class Streamer;

class StreamerRecord {
    Streamer * streamer;
    std::string nickname;
    bool active;
public:
    explicit StreamerRecord(Streamer * st);
    explicit StreamerRecord(const std::string &nick);
    StreamerRecord(const StreamerRecord &sr);
    ~StreamerRecord();
    const Streamer * getStreamer() const;
    std::string getNickname() const;
    bool isActive() const;
    void setActive(Streamer * st);
    void setInactive(std::string &nick);
};

#endif //STREAMZ_STREAMERRECORD_H
