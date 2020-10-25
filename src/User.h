#ifndef STREAMZ_USER_H
#define STREAMZ_USER_H
#include "Date.h"
#include <string>


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
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     */
    User(const std::string &nickname, const std::string &name, const Date &birth_date);
    /**
     * Gets the nickname of the user
     * @return nickname of the user
     */
    std::string getNickname() const;
    /**
     * Gets the name of the user
     * @return name of the user
     */
    std::string getName() const;
    /**
     * Gets the birth date of the user
     * @return birth date of the user
     */
    Date getBirthDate() const;
    /**
     * Displays on the screen the info about the user
     */
    virtual void show() const;
    /**
     * Compares users
     * @param other User to be compared with
     * @return boolean indicating if the users are the same
     */
    bool operator==(const User &other) const;
};

#endif //STREAMZ_USER_H
