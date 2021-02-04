#include "Platform.h"
#include "Streamer.h"
#include "Viewer.h"
#include "StreamData.h"
#include "Stream.h"
#include "PrivateStream.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <sstream>
#include <iomanip>

Platform::Platform() : archive(files.archived_stream_file) {
    readStreamsFromFile();
    readUsersFromFile();
}

void Platform::readStreamsFromFile() {
    std::ifstream file(files.active_stream_file);
    if(file.is_open()){
        file >> stream_id_count;
        std::string str;
        std::getline(file, str);
        while(readStreamFromFile(file)){}
        file.close();
    }
}

bool Platform::readStreamFromFile(std::ifstream &file){
    std::string str;
    std::vector<std::istringstream> lines;
    for(int i = 0; i < 5; ++i){
        if(!std::getline(file >> std::ws, str)){
            return false;
        }
        lines.emplace_back(str);
    }
    char discard;
    unsigned id, minimum_age, max_capacity, likes, dislikes;
    std::string title, streamer, stream_type, language, start_date, end_date;

    lines[0] >> discard >> id >> discard;
    std::getline(lines[0] >> std::ws, title);
    lines[1] >> str >> streamer;
    lines[2] >> stream_type >> language >> str >> str >> likes >> str >> dislikes;
    start_date = lines[3].str().substr(0,16);
    lines[4] >> str >>  minimum_age;

    if(stream_type == "public"){
        active_streams.emplace_back(new Stream(title, streamer, language, id, minimum_age,
                                               likes, dislikes, start_date));
    }
    else{
        if(!std::getline(file, str)){
            return false;
        } std::stringstream ss1{str};
        ss1 >> str >> max_capacity >> str;
        std::vector<std::string> allowed_users;
        while(ss1 >> str){
            allowed_users.push_back(str);
        }

        std::vector<Comment> comments;
        while(file.peek() != '(' && std::getline(file, str)){
            std::stringstream ss{str};
            std::string nick, date, time, comment;
            ss >> date >> time >> nick >> discard;
            std::getline(ss, comment);
            comment = comment.substr(0, comment.size()-1);
            date += " " + time;
            Comment comm{date, nick, comment};
            comments.push_back(comm);
        }
        active_streams.emplace_back(new PrivateStream(title, streamer, language, id, minimum_age,
                                                      max_capacity, allowed_users, likes, dislikes,
                                                      start_date, comments));
    }
    return true;
}

void Platform::readUsersFromFile(){
    std::ifstream file(files.user_file);
    std::string line;
    if(file.is_open()){
        while(readUserFromFile(file)){}
        file.close();
    }
}

bool Platform::readUserFromFile(std::ifstream &file) {
    std::string nickname, name, user_type, birth_date, str;
    unsigned current_stream_id;
    std::vector<std::istringstream> lines;
    for(int i = 0; i < 3; ++i){
        if(!std::getline(file, str)){
            return false;
        }
        lines.emplace_back(str);
    }
    lines[0] >> user_type >> nickname;
    std::getline(lines[0] >> std::ws, name);
    lines[1] >> current_stream_id >> std::ws;
    std::getline(lines[1], birth_date);

    unsigned int id; char feedback; std::vector<std::pair<unsigned int, char>> history;
    lines[2] >> str; // Remove 'history: '
    while(lines[2] >> id >> feedback){
        history.emplace_back(id, feedback);
    }

    if(user_type == "(viewer)"){
        Viewer * viewer = new Viewer(nickname, name, birth_date, *this, history);
        if(current_stream_id) {
            viewer->joinStream(current_stream_id);
        }
        users.push_back(viewer);
    }
    else{
        auto it = std::find_if(active_streams.begin(), active_streams.end(), [current_stream_id](const std::shared_ptr<Stream> &ptr){
            return ptr->getId() == current_stream_id;
        });
        if(it != active_streams.end()) {
            users.emplace_back(new Streamer(nickname, name, birth_date, *this, history, (*it)));
        } else{
            users.emplace_back(new Streamer(nickname, name, birth_date, *this, history));
        }
    }
    return true;
}

Platform::~Platform() {
    save();
    for(auto ptr : users){
        delete ptr;
    }
}

void Platform::save(){
    if(test){
        return;
    }
    std::ofstream users_file(files.user_file, std::ofstream::trunc);
    if(users_file.is_open()){
        for(const auto &user : users){
            users_file << *user;
        }
        users_file.close();
    }
    std::ofstream streams_file(files.active_stream_file, std::ofstream::trunc);
    if(streams_file.is_open()){
        streams_file << stream_id_count << std::endl;
        for(const auto &stream : active_streams){
            streams_file << *stream;
        }
        streams_file.close();
    }
}

template <typename F>
void Platform::sortActiveStreams(F pred) {
    std::sort(active_streams.begin(), active_streams.end(), pred);
}

void Platform::sort(sortingMode mode, sortingOrder order) {
    bool asc = (order == ascending);
    switch(mode){
        case views:
            sortActiveStreams([asc](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return asc ? ptr1->getViewers() < ptr2->getViewers() : ptr1->getViewers() > ptr2->getViewers();
            }); break;
        case likes:
            sortActiveStreams([asc](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return asc ? ptr1->getLikes() < ptr2->getLikes() : ptr1->getLikes() > ptr2->getLikes();
            }); break;
        case id:
            sortActiveStreams([asc](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return asc ? ptr1->getId() < ptr2->getId() : ptr1->getId() > ptr2->getId();
            }); break;
        case minimum_age:
            sortActiveStreams([asc](std::shared_ptr<Stream> &ptr1, std::shared_ptr<Stream> &ptr2){
                return asc ? ptr1->getMinAge() < ptr2->getMinAge() : ptr1->getMinAge() > ptr2->getMinAge();
            }); break;
    }
}

bool Platform::userExists(const std::string &nickname) const{
    auto it = std::find_if(users.begin(), users.end(), [nickname](User *user){
        return user->getNickname() == nickname;
    });
    return (it != users.end());
}

bool Platform::registerStreamer(const std::string &nickname, const std::string &name, const Date &birth_date) {
    if(userExists(nickname)){
        throw UserAlreadyExists(nickname);
    }
    users.push_back(new Streamer(nickname, name, birth_date, *this));
    return true;
}

bool Platform::registerViewer(const std::string &nickname, const std::string &name, const Date &birth_date) {
    if(userExists(nickname)){
        throw UserAlreadyExists(nickname);
    }
    users.push_back(new Viewer(nickname, name, birth_date, *this));
    return true;
}

unsigned int Platform::getUserCount() const{
    return users.size();
}
unsigned int Platform::getActiveStreamCount() const{
    return active_streams.size();
}
unsigned int Platform::getArchivedStreamCount() const {
    return archive.getStreamCount();
}

unsigned int Platform::getTotalStreamCount() const{
    return getActiveStreamCount() + getArchivedStreamCount();
}


void Platform::showStreams(const std::string &language_filter, unsigned minimum_age) const{
    std::cout << "Active streams:" << std::endl;
    showStreamsHeader();
    for(const auto & active_stream : active_streams){
        if((language_filter.empty() || active_stream->getLanguage() == language_filter) && active_stream->getMinAge() <= minimum_age){
            active_stream->show();
        }
    }
}

void Platform::showUsers() const{
    std::cout << "All Users:" << std::endl;
    for(auto user : users){
        user->show();
    }
}

void Platform::showStreamHistory(const std::vector<std::pair<unsigned int,char>> &history, char filter) const {
    std::vector<const StreamData *> h = archive.getStreamsById(history, filter);
    showStreamsHeader();
    for(const auto &data : h){
        data->show();
    }
    if(history.size() != h.size()) {
        for (const auto &p : history) {
            if (!filter || p.second == filter) {
                unsigned int id = p.first;
                auto it = std::find_if(active_streams.begin(), active_streams.end(),
                                       [id](const std::shared_ptr<Stream> &ptr) {
                                           return ptr->getId() == id;
                                       });
                if (it != active_streams.end()) {
                    (*it)->show();
                }
            }
        }
    }
}

User *Platform::getUser(const std::string &nickname) {
    auto it = std::find_if(users.begin(), users.end(), [nickname](User * user){
        return user->getNickname() == nickname;
    });
    if(it == users.end()){
        throw UserDoesNotExist(nickname);
    }
    return (*it);
}

std::weak_ptr<Stream> Platform::joinStream(const std::string &streamer, const Viewer &viewer) {
    auto it = find_if(active_streams.begin(), active_streams.end(), [streamer](const std::shared_ptr<Stream> &ptr){
        return ptr->getStreamer() == streamer;
    });
    if(it == active_streams.end()){
        throw StreamerNotStreaming(streamer);
    }
    if((*it)->canJoin(viewer)){
        (*it)->joinStream();
        std::weak_ptr<Stream> ptr = (*it);
        return ptr;
    }
    return std::weak_ptr<Stream>();
}

std::weak_ptr<Stream> Platform::joinStream(unsigned int id, const Viewer &viewer) {
    auto it = std::find_if(active_streams.begin(), active_streams.end(), [id](const std::shared_ptr<Stream> &ptr){
        return ptr->getId() == id;
    });
    if(it == active_streams.end()){
        if(id >= stream_id_count || id < 1){
            throw StreamDoesNotExist(id);
        }
        else{
            throw StreamNoLongerActive(id);
        }
    }
    if((*it)->canJoin(viewer)){
        (*it)->joinStream();
        std::weak_ptr<Stream> ptr = (*it);
        return ptr;
    }
    return std::weak_ptr<Stream>();
}

std::weak_ptr<Stream> Platform::startPublicStream(const std::string &title, const std::string &streamer, const std::string &language,
                                                  const unsigned int minimum_age) {
    std::shared_ptr<Stream> ptr(new Stream(title, streamer, language, stream_id_count++, minimum_age));
    active_streams.emplace_back(ptr);
    std::weak_ptr<Stream> weak_ptr = ptr;
    return weak_ptr;
}

std::weak_ptr<Stream> Platform::startPrivateStream(const std::string &title, const std::string &streamer, const std::string &language,
                                                   const unsigned minimum_age, const unsigned max_capacity,
                                                   const std::vector<std::string> &allowed_viewers){
    std::shared_ptr<Stream> ptr(new PrivateStream(title, streamer, language, stream_id_count++, minimum_age, max_capacity, allowed_viewers));
    active_streams.emplace_back(ptr);
    std::weak_ptr<Stream> weak_ptr = ptr;
    return weak_ptr;
}

void Platform::endStream(unsigned int id){
    auto stream_it = std::find_if(active_streams.begin(), active_streams.end(), [id](const std::shared_ptr<Stream> &ptr){
        return ptr->getId() == id;
    });
    if(stream_it == active_streams.end()){
        if(id >= stream_id_count || id < 1)
            throw StreamDoesNotExist(id);
        else
            throw StreamNoLongerActive(id);
    }
    (*stream_it)->endStream();
    StreamData data = *(*stream_it);
    archive.archiveStream(data);
    active_streams.erase(stream_it);
}

template <typename F>
std::vector<std::weak_ptr<Stream>> Platform::getTopActiveStreams(F pred) {
    std::vector<std::weak_ptr<Stream>> top10;
    int n_elements = active_streams.size() > 10 ? 10 : active_streams.size();
    top10.reserve(n_elements);
    std::stack<decltype(active_streams.begin())> s;

    // Custom insertion sort, where 10 greatest elements are inserted into the first 10 index
    for(auto it = active_streams.begin(); it != active_streams.begin() + n_elements; ++it){
        auto max_it = std::max_element(it, active_streams.end(), pred);
        s.emplace(max_it);
        std::iter_swap(it, max_it);
    }
    for(int i = 0; i < n_elements; ++i){
        top10.emplace_back(active_streams[i]);
    }
    // Unwind the changes made, restoring original vector state
    auto it = active_streams.begin() + n_elements - 1;
    for(int i = 0; i < n_elements; ++i, --it){
        std::iter_swap(s.top(), it);
        s.pop();
    }
    return top10;
}

void Platform::topActiveStreams() {
    std::vector<std::weak_ptr<Stream>> likes = getTopActiveStreams([](const std::shared_ptr<Stream> &ptr1,const std::shared_ptr<Stream> &ptr2){
        return ptr1->getLikes() < ptr2->getLikes();
    });

    std::vector<std::weak_ptr<Stream>> views = getTopActiveStreams([](const std::shared_ptr<Stream> &ptr1,const std::shared_ptr<Stream> &ptr2){
        return ptr1->getViewers() < ptr2->getViewers();
    });
    std::cout << "Top by Views" << std::endl << "    ";
    showStreamsHeader();
    for(int i = 0; i < views.size(); ++i){
        if(auto ptr = views[i].lock()){
            std::cout << std::right << std::setw(2) << i+1 << ": " << std::left;
            ptr->show();
        }
    }

    std::cout << "\nTop by Likes" << std::endl << "    ";
    showStreamsHeader();
    for(int i = 0; i < likes.size(); ++i){
        if(auto ptr = likes[i].lock()){
            std::cout << std::right << std::setw(2) << i+1 << ": " << std::left;
            ptr->show();
        }
    }
}

void Platform::topArchivedStreams() const{
    archive.showTop();
}

bool Platform::deleteUser(const std::string &nickname) {
    auto it = std::find_if(users.begin(), users.end(), [nickname](User *ptr){
        return ptr->getNickname() == nickname;
    });
    if(it == users.end()){
        return false;
    }
    Streamer * streamer = dynamic_cast<Streamer*> ((*it));
    if(streamer && streamer->inStream()){
        streamer->endStream();
    }
    delete (*it);
    users.erase(it);
    return true;
}

bool Platform::deleteStream(unsigned int id) {
    auto it = std::find_if(active_streams.begin(), active_streams.end(), [id](const std::shared_ptr<Stream> &ptr){
        return ptr->getId() == id;
    });
    if(it != active_streams.end()){
        active_streams.erase(it);
        return true;
    }
    return false;
}

void Platform::testMode() {
    test = true;
    stream_id_count = 1;
    for(auto u : users){
        delete u;
    }
    users.clear();
    active_streams.clear();
    archive.testMode();
}

std::vector<std::shared_ptr<Stream>> Platform::testGetStreams() {
    return active_streams;
}

void Platform::showArchive() {
    archive.show();
}
