#ifndef STREAMZ_PRIVATESTREAM_H
#define STREAMZ_PRIVATESTREAM_H
#include "Stream.h"
#include <vector>


class PrivateStream : public Stream {
public:
    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Identification of the stream
     * @param minimum_age Minimum age to watch the stream
     * @param max_capacity Maximum capacity of the stream
     * @param allowed_viewers Viewers allowed to watch the stream
     */
    PrivateStream(const string &title, const string &streamer, const string &language, unsigned int id, const unsigned minimum_age, const unsigned max_capacity, const vector<string> allowed_viewers);

    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Identification of the stream
     * @param minimum_age Minimum age to watch the stream
     * @param max_capacity Maximum capacity of the stream
     * @param allowed_viewers Viewers allowed to watch the stream
     * @param start_date string
     */
    PrivateStream(const string &title, const string &streamer, const string &language, unsigned int id, const unsigned minimum_age, const unsigned max_capacity, const vector<string> allowed_viewers, const std::string &start_date);

    /**
     * Displays on the screen info about the stream
     */
    void show() const;
    /**
     * Check if viewer can join the stream
     * @param viewer Viewer who wants to join the stream
     * @return Boolean indicating if he can join the stream
     */
    bool canJoin(Viewer &viewer);
    /**
     * Writes in the indicated ostream the information about the stream
     * @param os Output stream where the information will be writen
     * @return Stream where the information will be writen
     */
    ostream& print(ostream & os) const;
private:
    /**
     * Maximum capacity of the stream
     */
    unsigned max_capacity;
    /**
     * Vector with the viewers allowed to watch the stream
     */
    vector<string> allowed_viewers;

};


#endif //STREAMZ_PRIVATESTREAM_H
