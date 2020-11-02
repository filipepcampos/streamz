#ifndef STREAMZ_VIEWER_H
#define STREAMZ_VIEWER_H
#include "User.h"
#include "Stream.h"
#include <memory>

#define MINIMUM_AGE_VIEWER 12

class Viewer : public User {
    /**
     * Weak pointer to the stream the viewer is currently watching
     */
    std::weak_ptr<Stream> current_stream;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     */
    Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform *platform);
    /**
     * Gets the weak pointer to the stream the viewer is currently watching
     * @return weak pointer to the stream the viewer is currently watching
     */
    std::weak_ptr<Stream> getCurrentStream() const;
    /**
     * Joins the stream given as an argument
     * @param stream Shared pointer to the stream the viewer will join
     */
    void joinStream(const unsigned int id);
    /**
     * Leaves the stream that is currently being watched
     */
    void leaveStream();
    /**
     * Displays on the screen the info about the user
     */
    void show() const;
    /**
     * Writes in the indicated ostream the information about the user
     * @param os output stream where the information will be writen
     * @return stream where the information will be writen
     */
    std::ostream& print(std::ostream & os) const;
    /**
     * Compares viewers
     * @param other Viewer to be compared with
     * @return boolean indicating if the viewers are the same
     */
    bool operator==(const Viewer &other) const;
};

#endif //STREAMZ_VIEWER_H
