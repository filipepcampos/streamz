#ifndef STREAMZ_USER_H
#define STREAMZ_USER_H
#include "Date.h"
#include "Platform.h"
#include <iostream>
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
protected:
    /**
     * Pointer to the associated platform
     */
    Platform * platform;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     * @param name Name of the user
     * @param birth_date Birth date of the user
     */
    User(const std::string &nickname, const std::string &name, const Date &birth_date, Platform * platform);
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
     * Gets the age of the user
     * @return age of the user
     */
    unsigned getAge() const;
    /**
     * Displays on the screen the info about the user
     */
    virtual void show() const;
    /**
     * Writes in the indicated ostream the information about the user
     * @param os output stream where the information will be writen
     * @return stream where the information will be writen
     */
    virtual std::ostream& print(std::ostream & os) const;
    /**
     * Compares users
     * @param other User to be compared with
     * @return boolean indicating if the users are the same
     */
    bool operator==(const User &other) const;
    /**
     * Writes in the indicated ostream the information about the user
     * @param os output stream where the information will be writen
     * @param user user containing the data
     * @return stream where the information will be writen
     */
    friend std::ostream& operator<<(std::ostream& os, const User& user);
};

#endif //STREAMZ_USER_H
