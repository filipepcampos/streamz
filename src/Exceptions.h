#ifndef STREAMZ_EXCEPTIONS_H
#define STREAMZ_EXCEPTIONS_H
#include <string>


class UserDoesNotExist {
    /**
     * Nickname of the user
     */
    std::string nickname;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     */
    UserDoesNotExist(const std::string &nickname);
    /**
     * Gets the nickname of the user
     * @return nickname of the user
     */
    std::string getNickname() const;
};


class UserAlreadyExists {
    /**
     * Nickname of the user
     */
    std::string nickname;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     */
    UserAlreadyExists(const std::string &nickname);
    /**
     * Gets the nickname of the user
     * @return nickname of the user
     */
    std::string getNickname() const;
};


class InvalidAge {
    /**
     * Age of the user
     */
    unsigned int age;
public:
    /**
     * Class constructor
     * @param age Age of the user
     */
    InvalidAge(unsigned int age);
    /**
     * Gets the age of the user
     * @return age of the user
     */
    unsigned int getAge() const;
};


class InsufficientAge {
    /**
     * Age of the user
     */
    unsigned int age;
public:
    /**
     * Class constructor
     * @param age Age of the user
     */
    InsufficientAge(unsigned int age);
    /**
     * Gets the age of the user
     * @return age of the user
     */
    unsigned int getAge() const;
};

#endif //STREAMZ_EXCEPTIONS_H
