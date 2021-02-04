#include "Platform.h"
#include "Streamer.h"
#include "Viewer.h"
#include "StreamData.h"
#include "Stream.h"
#include "PrivateStream.h"
#include "Store.h"
#include <iostream>
#include <algorithm>
#include <stack>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "Donation.h"
#include <string>

Platform::Platform() : archive(files.archived_stream_file), donations(Donation("",0,0)) {
    readStreamsFromFile();
    readUsersFromFile();
    readStoresFromFile();
    readOrdersFromFile();
    readInactiveStreamersFromFile();
    readDonationsFromFile();
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

void Platform::readInactiveStreamersFromFile() {
    std::ifstream file(files.inactive_streamers_file);
    std::string nickname;
    if(file.is_open()){
        while(getline(file, nickname)) {
            streamerRecords.insert(StreamerRecord(nickname));
        }
        file.close();
    }
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
    std::string nickname, name, user_type, birth_date, bonus, str;
    bool hasBonus = false;
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
    lines[1] >> current_stream_id >> birth_date;
    if (lines[1] >> bonus) hasBonus = true;
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
        Streamer * st = nullptr;
        if(it != active_streams.end()) {
            st = new Streamer(nickname, name, birth_date, *this, history, (*it), hasBonus);
        } else{
            st = new Streamer(nickname, name, birth_date, *this, history, hasBonus);
        }
        users.emplace_back(st);
        streamerRecords.insert(StreamerRecord(st));
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
    std::ofstream inactive_streamers_file(files.inactive_streamers_file, std::ofstream::trunc);
    if(inactive_streamers_file.is_open()){
        HashTableStreamerRecord::iterator it = streamerRecords.begin();
        while (it != streamerRecords.end()) {
            if (!it->isActive())
                inactive_streamers_file << it->getNickname() << std::endl;
            ++it;
        }
        inactive_streamers_file.close();
    }
    std::ofstream streams_file(files.active_stream_file, std::ofstream::trunc);
    if(streams_file.is_open()){
        streams_file << stream_id_count << std::endl;
        for(const auto &stream : active_streams){
            streams_file << *stream;
        }
        streams_file.close();
    }
    writeOrdersToFile();
    writeStoresToFile();
    writeDonationsToFile();
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

    Streamer * st = nullptr;
    StreamerRecord aux(nickname);

    HashTableStreamerRecord::iterator it = streamerRecords.find(aux);
    if (it != streamerRecords.end()) {
        streamerRecords.erase(it);
        st = new Streamer(nickname, name, birth_date, *this, true);
    }
    else {
        st = new Streamer(nickname, name, birth_date, *this);
    }
    users.push_back(st);
    streamerRecords.insert(StreamerRecord(st));
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
                                                  const unsigned int minimum_age, unsigned bonus_likes) {
    std::shared_ptr<Stream> ptr(new Stream(title, streamer, language, stream_id_count++, minimum_age, bonus_likes, 0, Date().toString()));
    active_streams.emplace_back(ptr);
    std::weak_ptr<Stream> weak_ptr = ptr;
    return weak_ptr;
}

std::weak_ptr<Stream> Platform::startPrivateStream(const std::string &title, const std::string &streamer, const std::string &language,
                                                   const unsigned minimum_age, const unsigned max_capacity,
                                                   const std::vector<std::string> &allowed_viewers, unsigned bonus_likes){
    std::shared_ptr<Stream> ptr(new PrivateStream(title, streamer, language, stream_id_count++, minimum_age, max_capacity, allowed_viewers, bonus_likes, 0, Date().toString(), {}));
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
    if(streamer){
        if (streamer->inStream()) streamer->endStream();
        StreamerRecord aux(nickname);
        streamerRecords.erase(aux);
        streamerRecords.insert(aux);
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

void Platform::showStreamers(std::string active_filter) const {
    if (active_filter != "") {
        active_filter[0] = toupper(active_filter[0]);
        std::cout << active_filter << " ";
    }
    std::cout << "Streamers:" << std::endl;
    HashTableStreamerRecord::const_iterator it = streamerRecords.begin();
    while (it != streamerRecords.end()) {
        if (active_filter.empty() || (it->isActive() ? "Active" : "Inactive")  == active_filter) {
            if (active_filter.empty())std::cout << std::setw(9) << (it->isActive() ? "Active" : "Inactive");
            std::cout << it->getNickname() << std::endl;
        }
        ++it;
    }
}

Store *Platform::getStore(const std::string &streamer_name) {
    try{
        User * u = getUser(streamer_name);
        Streamer * s = dynamic_cast<Streamer *>(u);
        if(s != nullptr){
            return s->getStore();
        }
    }
    catch(const UserDoesNotExist &e){
        return nullptr;
    }
    return nullptr;
}

void Platform::writeOrdersToFile() {
    std::ofstream file(files.orders_file);
    if(file.is_open()){
        for(const auto &user : users){
            Viewer *v = dynamic_cast<Viewer *>(user);
            if(v != nullptr){
                for(const auto &order : v->getCompletedOrders()){
                    file << order;
                }
                for(const auto &order : v->getPendingOrders()){
                    file << order;
                }
            }
        }
        file.close();
    }
}

void Platform::readOrdersFromFile() {
    std::ifstream file(files.orders_file);
    std::string line_buffer;
    if(file.is_open()){
        while(std::getline(file, line_buffer)){
            std::string customer_name, streamer_name;
            int disp; char completed;
            std::istringstream ss(line_buffer);
            ss >> customer_name >> streamer_name >> disp >> completed;
            User *u = getUser(customer_name);
            Viewer *v = dynamic_cast<Viewer *>(u);
            u = getUser(streamer_name);
            Streamer *s = dynamic_cast<Streamer *>(u);
            Order o(v, disp, streamer_name);

            if(s == nullptr || v == nullptr){
                continue;
            }

            while(file.peek() == ' ' && std::getline(file, line_buffer)){
                std::string product_name; double price;
                std::istringstream ss2(line_buffer);
                ss2 >> product_name >> price;
                o.addProduct(Product(product_name, price));
            }

            if(completed == 'c'){
                o.completeOrder();
                v->addCompletedOrder(o);
            }
            else{
                s->getStore()->placeOrder(o);
                v->addPendingOrder(o);
            }
        }
    }
}

void Platform::writeStoresToFile() {
    std::ofstream file(files.stores_file);
    file << max_products_sold_per_store << std::endl;
    for(const auto &user : users){
        Streamer *s = dynamic_cast<Streamer *>(user);
        if(s != nullptr){
            Store * store = s->getStore();
            file << store->getStreamer() << " "  << store->getProductsSold() << std::endl;
            for(const auto &product : store->getProducts()){
                file << "    " << product.getName() << " " << product.getPrice() << std::endl;
            }
        }
    }
    file.close();
}

void Platform::readStoresFromFile() {
    std::ifstream file(files.stores_file);
    std::string line_buffer;
    if(file.is_open()){
        unsigned max_products_sold = 0;
        if(std::getline(file, line_buffer)){
            std::istringstream ss(line_buffer);
            ss >> max_products_sold;
        }
        while(std::getline(file, line_buffer)){
            std::string streamer_name;
            unsigned products_sold;
            std::istringstream ss(line_buffer);
            ss >> streamer_name >> products_sold;
            User *u = getUser(streamer_name);
            Streamer *s = dynamic_cast<Streamer *>(u);
            if(s != nullptr){
                Store *store = s->getStore();
                store->changeMaxProductsSold(max_products_sold);
                store->setProductsSold(products_sold);
                while(file.peek() == ' ' && std::getline(file, line_buffer)){
                    std::istringstream ss2(line_buffer);
                    std::string product_name; double price;
                    ss2 >> product_name >> price;
                    store->addMerchandise(Product(product_name, price));
                }
            }
        }
    }
}

void Platform::changeMaxProductsSoldPerStore(unsigned int max_products_sold){
    this->max_products_sold_per_store = max_products_sold;
    for(const auto &user : users){
        Store * store = getStore(user->getNickname());
        if(store != nullptr){
            store->changeMaxProductsSold(max_products_sold);
        }
    }
}

void Platform::resetProductsSold() {
    for(const auto &user : users){
        Store * store = getStore(user->getNickname());
        if(store != nullptr){
            store->resetProductsSold();
        }
    }
}

void Platform::addDonation(Donation &d) {
    Donation itemNotFound("", 0, 0);
    Donation d1 = donations.find(d);
    if(d1 == itemNotFound) {
        donations.insert(d);
    }
    else {
        unsigned c = d1.getCounter();
        donations.remove(d1);
        d.setCounter(c + 1);
        donations.insert(d);
    }
}

void Platform::writeDonationsToFile(){
    std::ofstream file(files.donations_file);
    if(file.is_open()){
        BSTItrIn<Donation> it(donations);
        while (!it.isAtEnd()){
            file << it.retrieve();
            it.advance();
        }
        file.close();
    }
}

void Platform::readDonationsFromFile() {
    std::ifstream file(files.donations_file);
    std::string line_buffer;
    if(file.is_open()){
        while(std::getline(file, line_buffer)){
            std::string st, eur_symbol;
            unsigned val, eval, count;
            std::istringstream ss(line_buffer);
            ss >> st >> val >> eur_symbol >> eval >> count;
            Donation d(st, val, eval);
            for(int i = 0; i < count; ++i){
                addDonation(d);
            }
        }
    }
}

void Platform::showDonations() {
    BSTItrIn<Donation> it(donations);
    std::cout << "All donations:" << std::endl;
    while (!it.isAtEnd()){
        std::cout << it.retrieve();
        it.advance();
    }
}

unsigned Platform::getMaxProductsSold() {
    return max_products_sold_per_store;
}

