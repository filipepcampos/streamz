#ifndef STREAMZ_STREAMER_H
#define STREAMZ_STREAMER_H
#include "User.h"
#include <vector>

#define MINIMUM_AGE_STREAMER 15


class Streamer : public User {
    std::vector<unsigned int> streams_history;
public:
    /**
     * Class constructor used when creating a new streamer
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     */
    Streamer(const std::string &nickname, const std::string &name, const Date &birth_date);
    /**
     * Class constructor used when loading an existing streamer from a file
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     */
    Streamer(const std::string &nickname, const std::string &name, const Date &birth_date, const std::vector<unsigned int> &streams_history);
    /**
     * Gets the streamer's previous streams
     * @return vector containing the id of the streamer's previous streams
     */
    const std::vector<unsigned int> & getStreamsHistory() const;
    /**
     * Adds the id of a stream to the streams history
     * @param id Id of the stream
     */
    void addStream(unsigned int id);
};

#endif //STREAMZ_STREAMER_H
