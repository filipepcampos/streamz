#ifndef STREAMZ_EXCEPTIONS_H
#define STREAMZ_EXCEPTIONS_H


class UserDoesNotExist {
    string nickname;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     */
    UserDoesNotExist(string nickname);
    /**
     * Returns the nickname of the user
     * @return nickname of the user
     */
    string getNickname() const;
};


class UserAlreadyExists {
    string nickname;
public:
    /**
     * Class constructor
     * @param nickname Nickname of the user
     */
    UserAlreadyExists(string nickname);
    /**
     * Returns the nickname of the user
     * @return nickname of the user
     */
    string getNickname() const;
};

#endif //STREAMZ_EXCEPTIONS_H
