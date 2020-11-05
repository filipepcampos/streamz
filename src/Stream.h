#ifndef STREAMZ_STREAM_H
#define STREAMZ_STREAM_H
#include "StreamData.h"
#include "Viewer.h"

using namespace std;


class Viewer;

class Stream : public StreamData{
public:
    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Identification of the stream
     * @param minimum_age Minimum age to watch the stream
     */
    Stream(const string &title, const string &streamer, const string &language, unsigned int id, const unsigned minimum_age);
    /**
     * Class constructor
     * @param title Title of the stream
     * @param streamer Streamer making the stream
     * @param language Language of the stream
     * @param id Identification of the stream
     * @param minimum_age Minimum age to watch the stream
     * @param start_date String to start_date
     */
    Stream(const string &title, const string &streamer, const string &language, unsigned int id, const unsigned minimum_age, const std::string &start_date);
    /**
     * Check if viewer can join the stream
     * @param viewer Viewer who wants to join the stream
     * @return boolean Boolean indicating if he can join the stream
     */
    bool virtual canJoin(const Viewer &viewer);
    /**
     * Adds viewer to the stream
     */
    void joinStream();
    /**
     * Removes viewer from the stream
     */
    void leaveStream();
    /**
     * Ends the stream
     */
    void endStream();
    /**
     * Get minimum viewer age
     */
    unsigned getMinimumAge() const;
    /**
     * Displays on the screen info about the stream
     */
    virtual void show() const;
    /**
     * Prints information about the stream
     * @param os Output stream where the information will be writen
     * @return Stream where the information will be writen
     */
    friend ostream& operator<<(ostream& os, const Stream& stream);
    /**
     * Writes in the indicated ostream the information about the stream
     * @param os Output stream where the information will be writen
     * @return Stream where the information will be writen
     */
    virtual ostream& print(ostream & os) const;
private:
    /**
     * Minimum age to watch the stream
     */
    unsigned minimum_age;
};


#endif //STREAMZ_STREAM_H
