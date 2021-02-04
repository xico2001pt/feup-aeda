#include "Stream.h"
#include <iostream>


Stream::Stream(const std::string &title, const std::string &streamer, const std::string &language, unsigned int id,
               const unsigned int minimum_age) :
        StreamData(id,title,streamer,Date(),Date(),language,0,true, minimum_age) {}

Stream::Stream(const std::string &title, const std::string &streamer, const std::string &language, unsigned int id,
               const unsigned int minimum_age, unsigned int likes, unsigned int dislikes,
               const std::string &start_date) :
        StreamData(id,title,streamer,Date(start_date),Date(),language,0,true,
                   minimum_age, likes, dislikes) {}

bool Stream::canJoin(const Viewer &viewer){
    return (viewer.getAge() >= minimum_age);
}

void Stream::joinStream(){
    viewers++;
}

void Stream::leaveStream(){
    viewers--;
}

void Stream::giveLike() {
    likes++;
}

void Stream::removeLike() {
    likes--;
}

void Stream::giveDislike() {
    dislikes++;
}

void Stream::removeDislike() {
    dislikes--;
}

void Stream::endStream(){
    end_date = Date();
    over = true;
}

