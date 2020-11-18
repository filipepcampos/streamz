#ifndef STREAMZ_STREAMER_H
#define STREAMZ_STREAMER_H
#include "User.h"
#include "Stream.h"
#include <vector>
#include <memory>

class Streamer : public User {
public:
    /**
     * Class constructor used when creating a new streamer
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     * @throws InvalidAge
     */
    Streamer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform & platform);
    /**
     * Class constructor used when loading an existing streamer from a file
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     * @throws InvalidAge
     */
    Streamer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform & platform, const std::vector<std::pair<unsigned int,char>> &streams_history);
    /**
     * Class constructor used when loading an existing streamer from a file
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     * @param current_stream weak_ptr to streamer's current stream
     * @throws InvalidAge
     */
    Streamer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform & platform, const std::vector<std::pair<unsigned int,char>> &streams_history, const std::weak_ptr<Stream> &current_stream);

    /**
     * Starts a Public Stream and associate it with the streamer
     * @param title Stream title
     * @param language Stream language
     * @param minimum_age Minimum age of the allowed viewers
     * @throws InvalidAction
     */
    void startPublicStream(const string &title, const string &language, unsigned minimum_age);
    /**
     * Starts a Private Stream and associate it with the streamer
     * @param title Stream title
     * @param language Stream language
     * @param minimum_age Minimum age of the allowed viewers
     * @param max_capacity Max capacity of viewers
     * @param allowed_viewers Vector with allowed viewers nicknames
     * @throws InvalidAction
     */
    void startPrivateStream(const string &title, const string &language, unsigned minimum_age, unsigned max_capacity, const vector<string> &allowed_viewers);
    /**
     * Ends the stream the user is currently streaming
     * @throws InvalidAction
     */
    void endStream();
    /**
     * Removes a stream from the streams history
     * @param id Id of the stream
     * @throws StreamDoesNotExist
     */
    void removeStreamFromHistory(const unsigned int id);
    /**
     * Displays on the screen the info about the user
     */
    void show() const;

    /**
     * Show current stream stats, if in stream
     */
    void showStreamInfo() const;

    /**
     * Writes in the indicated ostream the information about the user
     * @param os Stream where the information will be writen
     * @return Stream where the information will be writen
     */
    std::ostream& print(std::ostream & os) const;
    /**
     * Checks if the users have the same nickname
     * @param other Streamer to be compared with
     * @return Boolean indicating if the streamers are the same
     */
    bool operator==(const Streamer &other) const;
};

#endif //STREAMZ_STREAMER_H
