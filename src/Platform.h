#ifndef STREAMZ_PLATFORM_H
#define STREAMZ_PLATFORM_H
#include "Admin.h"
#include "User.h"
#include "Stream.h"
#include "Streamer.h"
#include "Viewer.h"
#include "Exceptions.h"
#include <vector>
#include <string>
#include <memory>



class Platform {
private:
    std::vector<User *> users;
    /** Active streams (always sorted by id) */
    std::vector<std::shared_ptr<Stream>> active_streams;
    /** Archived streams (sorted by end date) */
    std::vector<StreamData> archived_streams;

    std::vector<StreamData> top10_likes;
    std::vector<StreamData> top10_views;

    unsigned int stream_id_count = 0;
    friend class Admin;

    /**
     * Get the 10 highest streams in active_streams using F function as a comparator
     * The original vector active_streams is always restored to it's original state before returning
     * @tparam F
     * @param function - std::shared_ptr<Stream> comparator function
     * @return vector<weak_ptr<Stream>>
     */
    template <typename F>
    std::vector<std::weak_ptr<Stream>> getTop(F function);

    /**
     * Check if a user with a given nickname already exists
     * @param nickname
     * @return true if user exists
     */
    bool userExists(const std::string &nickname);

public:
    /**
     * Register a new Viewer to the Platform
     * @param nickname
     * @param name
     * @param birth_date
     * @return true if registered with success
     */
    bool registerViewer(const std::string &nickname, const std::string &name, const Date &birth_date);

    /**
     * Register a new Streamer to the Platform
     * @param nickname
     * @param name
     * @param birth_date
     * @return true if registered with success
     */
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
     */
    void topActiveStreams();

    /*
     * Get top 10 archived streams by viewer_count and by likes
     */
    void topArchivedStreams();

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
