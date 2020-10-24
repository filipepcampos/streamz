#ifndef STREAMZ_EXCEPTIONS_H
#define STREAMZ_EXCEPTIONS_H
#include <string>


class UserDoesNotExist {
    std::string nickname;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     */
    UserDoesNotExist(const std::string &nickname);
    /**
     * Returns the nickname of the user
     * @return nickname of the user
     */
    std::string getNickname() const;
};


class UserAlreadyExists {
    std::string nickname;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     */
    UserAlreadyExists(const std::string &nickname);
    /**
     * Returns the nickname of the user
     * @return nickname of the user
     */
    std::string getNickname() const;
};

#endif //STREAMZ_EXCEPTIONS_H
