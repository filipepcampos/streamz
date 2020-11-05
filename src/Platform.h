#ifndef STREAMZ_PLATFORM_H
#define STREAMZ_PLATFORM_H
#include "Exceptions.h"
#include "Archive.h"
#include <vector>
#include <string>
#include <memory>
#include <list>

#define MINIMUM_VIEWER_AGE 12
#define MINIMUM_STREAMER_AGE 15

class User;
class Viewer;
class Streamer;
class StreamData;
class Stream;

enum sortingMode{
    views,
    id,
    minimum_age,
    likes
};
enum sortingOrder{
    ascending,
    descending
};

class Platform {
private:
    friend class Admin;
    bool test = false;

    std::vector<User *> users;
    /** Active streams (sorted by id) */
    std::vector<std::shared_ptr<Stream>> active_streams;

    unsigned int stream_id_count = 1;

    struct IOFiles{
        const std::string user_file = "user.txt";
        const std::string active_stream_file = "active_streams.txt";
        const std::string archived_stream_file = "archive.txt";
    };
    IOFiles files;

    Archive archive;

    /**
     * Get the 10 highest streams in active_streams using F function as a comparator
     * The original vector active_streams is always restored to it's original state before returning
     * @tparam F
     * @param function - std::shared_ptr<Stream> comparator function
     * @return vector<weak_ptr<Stream>>
     */
    template <typename F>
    std::vector<std::weak_ptr<Stream>> getTopActiveStreams(F pred);

    template <typename F>
    void sortActiveStreams(F pred);

    /**
     * Check if a user with a given nickname already exists
     * @param nickname
     * @return true if user exists
     */
    bool userExists(const std::string &nickname) const;

    void readUsersFromFile();

    void readStreamsFromFile();

    void save();

public:
    Platform();

    ~Platform();

    void sort(sortingMode mode, sortingOrder order);

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

    /*
     * Get number of archived streams
     * @return unsigned int
     */
    unsigned int getArchivedStreamCount() const;

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
     * Delete a user from the Platform
     * @param nickname
     * @return true if user was deleted with success
     */
    bool deleteUser(const std::string &nickname);

    //TODO change to const viewer
    /**
     * Return weak_ptr to stream at position 'p' (which can be seen using showStreams)
     * @param p
     * @param viewer
     * @throws std::out_of_range
     * @return
     */
    std::weak_ptr<Stream> joinStreamByPos(int p, const Viewer &viewer);

    //TODO change to const viewer
    /**
     * Return weak_ptr to stream with id
     * @param id - unique stream id
     * @param viewer
     * @return
     */
    std::weak_ptr<Stream> joinStreamById(unsigned int id, const Viewer &viewer);

    /**
     * Start a Public Stream and return a weak_ptr to it
     * @param title - Stream title
     * @param streamer - Streamer nickname
     * @param language
     * @param minimum_age
     * @return
     */
    std::weak_ptr<Stream> startPublicStream(const string &title, const string &streamer, const string &language,
                                            unsigned minimum_age);

    /**
     * Start a Private Stream and return a weak_ptr to it
     * @param title - Stream Title
     * @param streamer - Streamer nickname
     * @param language
     * @param minimum_age
     * @param max_capacity
     * @param allowed_viewers - Vector with allowed viewers nicknames
     * @return
     */
    std::weak_ptr<Stream> startPrivateStream(const string &title, const string &streamer, const string &language,
                                             unsigned minimum_age, unsigned max_capacity,
                                             const vector<string> &allowed_viewers);

    /**
     * End stream with a given id
     * @param id
     */
    void endStream(unsigned int id);

    /*+
     * Get top 10 active streams by viewer_count and by likes
     */
    void topActiveStreams();

    /*
     * Get top 10 archived streams by viewer_count and by likes
     */
    void topArchivedStreams() const;

    /**
     * Show all streams active in the platform
     */
    void showStreams(const std::string &language_filter = "", unsigned minimum_age = 99999) const;

    void showStreamHistory(const std::vector<unsigned> &ids) const;

    /**
     * Show all users in the platform
     */
    void showUsers() const;

    /**
     * Clear all vectors in memory
     * Does not remove anything from files
     */
    void testMode();

    std::vector<std::shared_ptr<Stream>> testGetStreams();
};


#endif //STREAMZ_PLATFORM_H
