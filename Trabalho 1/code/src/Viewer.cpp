#include "Viewer.h"
#include "PrivateStream.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

Viewer::Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform &platform) : User(nickname, name, birth_date, platform) {
    if (getAge() < MINIMUM_VIEWER_AGE)
        throw InvalidAge(getAge());
}

Viewer::Viewer(const std::string &nickname, const std::string &name, const Date &birth_date, Platform &platform,
               const std::vector<std::pair<unsigned int, char>> &history)
                        : User(nickname, name, birth_date, platform, history){
    if (getAge() < MINIMUM_VIEWER_AGE)
        throw InvalidAge(getAge());
}

std::weak_ptr<Stream> Viewer::getCurrentStream() const {
    return current_stream;
}

void Viewer::joinStream(unsigned int id) {
    if (!current_stream.expired())
        leaveStream();
    current_stream = platform.joinStream(id, *this);
    syncHistory();
}
void Viewer::joinStream(const std::string &streamer) {
    if(!current_stream.expired()){
        leaveStream();
    }
    current_stream = platform.joinStream(streamer, *this);
    syncHistory();
}


void Viewer::leaveStream() {
    if (!current_stream.expired())
        current_stream.lock()->leaveStream();
    current_stream.reset();
    current_stream_feedback = nullptr;
}

void Viewer::show() const {
    std::cout << std::setw(10) << "Viewer";
    User::show();
}

std::ostream& Viewer::print(std::ostream & os) const {
    os << "(viewer) "; User::print(os);
    return os;
}

bool Viewer::operator==(const Viewer &other) const {
    return this->getNickname() == other.getNickname();
}

void Viewer::comment(const std::string &str) {
    if(auto ptr = current_stream.lock()){
        std::shared_ptr<PrivateStream> private_stream = std::dynamic_pointer_cast<std::shared_ptr<PrivateStream>::element_type>(ptr);
        if(private_stream){
            private_stream->addComment(*this, str);
        }
    }
}

void Viewer::syncHistory() {
    unsigned int current_id;
    if(auto ptr = current_stream.lock()){
        current_id = ptr->getId();
    }
    auto it = std::find_if(streams_history.begin(), streams_history.end(), [current_id](const std::pair<unsigned int, char> &p){
        return p.first == current_id;
    });
    if(it == streams_history.end()){
        if(auto ptr = current_stream.lock()){
            streams_history.emplace_back(ptr->getId(), '-');
            current_stream_feedback = &(streams_history.rbegin()->second);
        }
    }
    else{
        current_stream_feedback = &(it->second);
    }
}

char Viewer::getCurrentFeedback() const{
    if(current_stream_feedback){
        return *current_stream_feedback;
    }
    return 0;
}

void Viewer::like() {
    if(current_stream_feedback != nullptr){
        if(auto ptr = current_stream.lock()){
            switch(*current_stream_feedback){
                case 'L': ptr->removeLike(); *current_stream_feedback = '-'; break;
                case '-': ptr->giveLike(); *current_stream_feedback = 'L'; break;
                case 'D': ptr->removeDislike(); ptr->giveLike(); *current_stream_feedback = 'L'; break;
            }
        }
    }
}

void Viewer::dislike() {
    if(current_stream_feedback != nullptr){
        if(auto ptr = current_stream.lock()){
            switch(*current_stream_feedback){
                case 'L': ptr->removeLike(); ptr->giveDislike(); *current_stream_feedback = 'D'; break;
                case '-': ptr->giveDislike(); *current_stream_feedback = 'D'; break;
                case 'D': ptr->removeDislike(); *current_stream_feedback = '-'; break;
            }
        }
    }
}
