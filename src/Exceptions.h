#ifndef STREAMZ_EXCEPTIONS_H
#define STREAMZ_EXCEPTIONS_H
#include <string>
#include <exception>


class UserDoesNotExist : public std::exception{
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


class UserAlreadyExists : public std::exception{
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


class InvalidAge : public std::exception{
    /**
     * Age of the user
     */
    unsigned int age;
public:
    /**
     * Class constructor
     * @param age Age of the user
     */
    InvalidAge(const unsigned int age);
    /**
     * Gets the age of the user
     * @return age of the user
     */
    unsigned int getAge() const;
};


class InsufficientAge : public std::exception{
    /**
     * Age of the user
     */
    unsigned int age;
public:
    /**
     * Class constructor
     * @param age Age of the user
     */
    InsufficientAge(const unsigned int age);
    /**
     * Gets the age of the user
     * @return age of the user
     */
    unsigned int getAge() const;
};

class StreamNoLongerActive : public std::exception {
    unsigned int id;
public:
    /**
     * Class constructor
     * @param id stream id
     */
    StreamNoLongerActive(const unsigned int id);
    /**
     * Gets stream id
     * @return id
     */
    unsigned int getId() const;
};

class StreamDoesNotExist : public std::exception {
    unsigned int id;
    public:
    /**
     * Class constructor
     * @param id stream id
     */
    StreamDoesNotExist(const unsigned int id);
    /**
     * Gets stream id
     * @return id
     */
    unsigned int getId() const;
};

class InvalidAction : public std::exception {
    std::string message;
public:
    /**
     * Class constructor
     * @param message Message to be displayed
     */
    InvalidAction(const std::string &message);
    /**
     * Gets exception message
     * @return id
     */
    std::string getMessage() const;
};

#endif //STREAMZ_EXCEPTIONS_H
