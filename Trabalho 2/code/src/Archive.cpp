#include "Archive.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

Archive::Archive(const std::string &filename) : filename(filename) {
    std::ifstream file(filename);
    if(file.is_open()) {
        while(readStreamFromFile(file));
        file.close();
    }
}

Archive::~Archive(){
    if(!test){
        std::ofstream file(filename, std::ofstream::trunc);
        if(file.is_open()){
            for(const auto &data : streams){
                file << data;
            }
            file.close();
        }
    }
}

bool Archive::readStreamFromFile(std::ifstream &file) {
    std::string str;
    std::vector<std::istringstream> lines;
    for(int i = 0; i < 5; ++i){
        if(!getline(file >> std::ws, str)){
            return false;
        }
        lines.emplace_back(str);
    }
    char discard;
    unsigned id, likes, dislikes, views, minimum_age;
    std::string title, streamer, stream_type, language, start_date, end_date;

    lines[0] >> discard >> id >> discard;
    std::getline(lines[0] >> std::ws, title);
    lines[1] >> str >> streamer;
    lines[2] >> stream_type >> language >> views >> str >> likes >> str >> dislikes;
    start_date = lines[3].str().substr(0, 16); end_date = lines[3].str().substr(19, 16);
    lines[4] >> str >>  minimum_age;
    streams.emplace_back(id, title, streamer, start_date, end_date, language, views, stream_type=="public", minimum_age, likes, dislikes, true);
    updateTop(*(streams.rbegin()));
    return true;
}

unsigned int Archive::getStreamCount() const {
    return streams.size();
}

void Archive::show() const{
    std::cout << "All archived streams:" << std::endl;
    showStreamsHeader();
    for(const auto &data : streams){
        data.show();
    }
}

void Archive::showTop() const{
    std::cout << "Archive Top 10" << std::endl;
    std::cout << "Top by Views:" << std::endl << "    ";
    showStreamsHeader();
    int i = 1;
    for(auto it = top_views.rbegin(); it != top_views.rend(); ++it){
        std::cout << std::right << std::setw(2) << i++ << ": " << std::left; (*it).show();
    }
    std::cout << "\nTop by Likes:" << std::endl << "    ";
    showStreamsHeader();
    i = 1;
    for(auto it = top_likes.rbegin(); it != top_likes.rend(); ++it){
        std::cout << std::right << std::setw(2) << i++ << ": " << std::left; (*it).show();
    }
}

void Archive::showStream(unsigned int id) const{
    showStreamsHeader();
    int pos = binarySearch(id);
    if(pos != -1) {
        streams[pos].show();
    }
}

std::vector<const StreamData *> Archive::getStreamsById(const std::vector<std::pair<unsigned int, char>> &history, char filter) const{
    std::vector<const StreamData *> vec;
    for(const auto &p : history){
        if(!filter || p.second == filter){
            int pos = binarySearch(p.first);
            if(pos != -1){
                vec.push_back(&streams[pos]);
            }
        }
    }
    return vec;
}

int Archive::binarySearch(unsigned int id) const{
    int left = 0, right = streams.size()-1;
    while (left <= right) {
        int m = left + (right - left) / 2;
        unsigned int current_id = streams[m].getId();
        if (current_id == id)
            return m;
        if (current_id < id)
            left = m + 1;
        else
            right = m - 1;
    }
    return -1;
}

void Archive::archiveStream(const StreamData &data) {
    auto it = std::lower_bound(streams.begin(), streams.end(), data.getId(),
                       [](const StreamData &d, unsigned int id){
                           return d.getId() < id;
                       });
    streams.insert(it, data);
    updateTop(data);
}

void Archive::updateTop(const StreamData &data){
    auto views_it = std::lower_bound(top_views.begin(), top_views.end(), data.getViewers(),  [](const StreamData &d, unsigned int viewers){
        return d.getViewers() < viewers;
    });
    if(views_it != top_views.begin() || top_views.size() < 10){
        top_views.insert(views_it, data);
        if(top_views.size() > 10)
            top_views.pop_front();
    }
    auto likes_it = std::lower_bound(top_likes.begin(), top_likes.end(), data.getLikes(), [](const StreamData &d, unsigned int likes){
        return d.getLikes() < likes;
    });
    if(likes_it != top_likes.begin() || top_likes.size() < 10) {
        top_likes.insert(likes_it, data);
        if(top_likes.size() > 10)
            top_likes.pop_front();
    }
}

void Archive::testMode(){
    test = true;
    top_views.clear();
    top_likes.clear();
    streams.clear();
}
