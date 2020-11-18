#ifndef STREAMZ_USER_H
#define STREAMZ_USER_H
#include "Date.h"
#include "Platform.h"
#include <iostream>
#include <string>
#include <utility>

class User {
    /**
     * Nickname of the user
     */
    std::string nickname;
    /**
     * Name of the user
     */
    std::string name;
    /**
     * Birth date of the user
     */
    Date birth_date;
protected:
    /**
     * Pointer to the associated platform
     */
    Platform & platform;

    /**
     * Weak pointer to the stream the viewer is currently watching or streamer is currently hosting
     */
    std::weak_ptr<Stream> current_stream;

    /**
     * Vector containing the id's of the streams created by the user (always sorted by id)
     */
    std::vector<std::pair<unsigned int, char>> streams_history;

public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     */
    User(const std::string &nickname, const std::string &name, const Date &birth_date, Platform & platform);
    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     * @param history Watched / hosted streams history
     */
    User(const std::string &nickname, const std::string &name, const Date &birth_date, Platform & platform, const std::vector<std::pair<unsigned int, char>> &history);
    /**
     * Gets the nickname of the user
     * @return String containing the nickname of the user
     */
    std::string getNickname() const;
    /**
     * Gets the name of the user
     * @return String containing the name of the user
     */
    std::string getName() const;
    /**
     * Gets the birth date of the user
     * @return Birth date of the user
     */
    Date getBirthDate() const;
    /**
     * Gets the age of the user
     * @return Age of the user
     */
    unsigned getAge() const;

    /**
     * Gets the streamer's previous streams
     * @return Vector containing the id of the streamer's previous streams
     */
    const std::vector<std::pair<unsigned int,char>> & getStreamsHistory() const;

    /**
     * Removes a stream from the streams history
     * @param id Id of the stream
     * @throws StreamDoesNotExist
     */
    virtual void removeStreamFromHistory(const unsigned int id);

    /**
     * Check if user is in a stream
     * @return true if in stream
     */
    bool inStream() const;

    /**
     * Check if user is in a public stream
     * @return true if in public stream
     */
    bool inPrivateStream() const;

    /**
     * Displays on the screen the info about the user
     */
    virtual void show() const;
    /**
     * Writes in the indicated ostream the information about the user
     * @param os Output stream where the information will be writen
     * @return Stream where the information will be writen
     */
    virtual std::ostream& print(std::ostream & os) const;
    /**
     * Checks if the users have the same nickname
     * @param other User to be compared with
     * @return Boolean indicating if the users are the same
     */
    bool operator==(const User &other) const;
    /**
     * Writes in the indicated ostream the information about the user
     * @param os Output stream where the information will be writen
     * @param user User containing the data
     * @return Stream where the information will be writen
     */
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

#endif //STREAMZ_USER_H
