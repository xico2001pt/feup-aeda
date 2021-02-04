#include "Exceptions.h"

UserDoesNotExist::UserDoesNotExist(const std::string &nickname) : nickname(nickname) {}
std::string UserDoesNotExist::getNickname() const {
    return nickname;
}

UserAlreadyExists::UserAlreadyExists(const std::string &nickname) : nickname(nickname) {}
std::string UserAlreadyExists::getNickname() const {
    return nickname;
}

InvalidAge::InvalidAge(const unsigned int age) : age(age) {}
unsigned int InvalidAge::getAge() const {
    return age;
}

InsufficientAge::InsufficientAge(const unsigned int age) : age(age) {}
unsigned int InsufficientAge::getAge() const {
    return age;
}

StreamNoLongerActive::StreamNoLongerActive(const unsigned int id) : id(id){}
unsigned int StreamNoLongerActive::getId() const {
    return id;
}

StreamDoesNotExist::StreamDoesNotExist(const unsigned int id) : id(id){}
unsigned int StreamDoesNotExist::getId() const{
    return id;
}

InvalidAction::InvalidAction(const std::string &message) : message(message) {}
std::string InvalidAction::getMessage() const {
    return message;
}

StreamerNotStreaming::StreamerNotStreaming(const std::string &nickname) : streamer(nickname){}
std::string StreamerNotStreaming::getName() const {
    return streamer;
}

InvalidDate::InvalidDate(const std::string &date) : date(date) {}
std::string InvalidDate::getDate() const {
    return date;
}

