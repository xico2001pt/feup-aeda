#include "Viewer.h"
#include "PrivateStream.h"
#include "Order.h"
#include "Store.h"
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
    os << "(viewer) ";
    os << getNickname() << " " << getName() << std::endl;
    os << "    " << (current_stream.expired() ? 0 : current_stream.lock()->getId()) << " " << getBirthDate().toString(false) << std::endl;
    User::print(os);
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

void Viewer::completeOrder(const Order &o) {
    auto it = std::find_if(pending_orders.begin(), pending_orders.end(), [o](const Order &o2){
        return o == o2;
    });
    if(it != pending_orders.end()){
        Order o2 = (*it);
        o2.completeOrder();
        completed_orders.emplace_back(o2);
        pending_orders.erase(it);
    }
}

void Viewer::showOrders() {
    std::cout << "Pending orders" << std::endl;
    for(int i = 0; i < pending_orders.size(); ++i){
        std::cout << i+1 << ": " << std::endl << pending_orders[i];
    }
    std::cout << std::endl << "Completed orders" << std::endl;
    for(int i = 0; i < completed_orders.size(); ++i){
        std::cout << i+1 << ": " << std::endl << completed_orders[i];
    }
}

void Viewer::addPendingOrder(const Order &o) {
    pending_orders.push_back(o);
}

std::vector<Order> &Viewer::getPendingOrders() {
    return pending_orders;
}

std::vector<Order> &Viewer::getCompletedOrders() {
    return completed_orders;
}

void Viewer::addCompletedOrder(const Order &o) {
    completed_orders.push_back(o);
}
void Viewer::removeOrderAtPos(int pos) {
    if(pos >= 0 && pos < pending_orders.size()){
        Order o = pending_orders[pos];
        pending_orders.erase(pending_orders.begin() + pos);
        Store * store = platform.getStore(o.getStreamer());
        if(store){
            store->removeOrder(o);
        }
    }
}

