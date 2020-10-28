#ifndef STREAMZ_PLATFORM_H
#define STREAMZ_PLATFORM_H
#include "User.h"
#include "Stream.h"
#include "Streamer.h"
#include "Viewer.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <memory>

class StreamData{};

class Platform {
private:
    std::vector<User *> users;
    std::vector<std::shared_ptr<Stream>> active_streams; /** Active streams (always sorted by id) */
    std::vector<StreamData> archived_streams;
    unsigned int stream_id_count = 0;

    bool userExists(const std::string &nickname);

public:
    bool registerViewer(const std::string &nickname, const std::string &name, const Date &birth_date);
    bool registerStreamer(const std::string &nickname, const std::string &name, const Date &birth_date);

    /**
     * Get number of users registered in the platform
     * @return unsigned int
     */
    unsigned int getUserCount() const;

    /**
     * Get number of active streams in the platform
     * @return unsigned int
     */
    unsigned int getActiveStreamCount() const;

    /**
     * Get total number of streams (active + archived) in the platform
     * @return unsigned int
     */
    unsigned int getTotalStreamCount() const;

    /**
     * Get user by nickname
     * @param nickname
     * @throws UserDoesNotExist
     * @return corresponding User *
     */
    User * getUser(const std::string &nickname);

    /**
     * Return weak_ptr to stream at position 'p' (which can be seen using showStreams)
     * @param p
     * @param viewer
     * @throws std::out_of_range, InsufficientAge
     * @return
     */
    std::weak_ptr<Stream> joinStream(int p, Viewer &viewer);

    std::weak_ptr<Stream> startStream(Streamer &streamer);
    void endStream(unsigned int id);

    /*+
     * Get top 10 active streams by viewer_count and by likes
     * @return std::vector<Stream *> of all the streams
     */
    //std::vector<Stream *> topStreams();

    /**
     * Show all streams active in the platform
     */
    void showStreams();

    /**
     * Show all users in the platform
     */
    void showUsers();

    /**
     * Clear all vectors in memory
     * Does not remove anything from files
     */
    void reset();
};


#endif //STREAMZ_PLATFORM_H
