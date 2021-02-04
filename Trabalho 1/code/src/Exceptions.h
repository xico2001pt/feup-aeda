#ifndef STREAMZ_EXCEPTIONS_H
#define STREAMZ_EXCEPTIONS_H
#include <string>
#include <exception>


class UserDoesNotExist : public std::exception{
    std::string nickname; /**< Nickname of the user */
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
    std::string nickname; /**< Nickname of the user */
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
    unsigned int age; /**< Age of the user */
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
    unsigned int age; /**< Age of the user */
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
    unsigned int id; /**< Id of the stream */
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
    unsigned int id; /**< Id of the stream */
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

class StreamerNotStreaming : public std::exception {
    std::string streamer; /**< Nickname of the streamer */
public:
    /**
     * Constructor
     * @param nickname - nickname of the streamer
     */
    StreamerNotStreaming(const std::string &nickname);
    /**
     * Get streamer nickname
     * @return streamer nickname
     */
    std::string getName() const;
};

class InvalidAction : public std::exception {
    std::string message; /**< Message to be displayed */
public:
    /**
     * Class constructor
     * @param message Message to be displayed
     */
    InvalidAction(const std::string &message);
    /**
     * Gets exception message
     * @return message
     */
    std::string getMessage() const;
};

class InvalidDate : public std::exception {
    std::string date; /**< Date which is invalid */
public:
    /**
     * Class constructor
     * @param date Date that is invalid
     */
    InvalidDate(const std::string &date);
    /**
     * Gets date
     * @return Date
     */
    std::string getDate() const;
};

#endif //STREAMZ_EXCEPTIONS_H
