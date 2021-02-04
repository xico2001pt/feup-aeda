#include "Menu.h"
#include "Input.h"
#include "Donation.h"
#include <sstream>
#include <algorithm>


namespace screen{
    void showScreenLine(const std::string &code){
        for(int i = 0; i < WIDTH; ++i){
            std::cout << code;
        }
    }

    void showScreen(){
        std::cout << "┌"; showScreenLine("─"); std::cout << "┐" << std::endl;
        for(int i = 0; i < HEIGHT; ++i){
            std::cout << "│";
            for(int j = 0; j < WIDTH; ++j){
                std::cout << image[i][j] << "▉" << RESET;
            }
            std::cout << "│" << std::endl;
        }
        std::cout << "└"; showScreenLine("─"); std::cout << "┘" << std::endl;
    }
}

Menu::Menu(Platform &platform) : platform(platform) {}

Menu * Menu::invalidOption() {
    std::cout << "Invalid option" << std::endl;
    input::waitEnter();
    return this;
}

// --------------- Main Menu ---------------

MainMenu::MainMenu(Platform &platform) : Menu(platform) {}
void MainMenu::show() {
    unsigned int options = 0;

    std::cout << CLR_SCREEN;
    std::cout << "\n"
            "   _____ _                            ______\n"
            "  / ____| |                          |___  /\n"
            " | (___ | |_ _ __ ___  __ _ _ __ ___    / / \n"
            "  \\___ \\| __| '__/ _ \\/ _` | '_ ` _ \\  / /  \n"
            "  ____) | |_| | |  __/ (_| | | | | | |/ /__ \n"
            " |_____/ \\__|_|  \\___|\\__,_|_| |_| |_/_____|\n"
            "\n";

    /* MAIS TARDE AJUSTAR ESPACAMENTO COM SETW() */
    std::cout << "Main Menu:\n\n";
    std::cout << "[" << ++options << "] " << "Login User\n";
    std::cout << "[" << ++options << "] " << "Register User\n";
    std::cout << "[" << ++options << "] " << "Administrator\n";
    std::cout << "[" << ++options << "] " << "Show information\n";
    std::cout << "[" << ++options << "] " << "Manual Save\n\n"; // ?
    std::cout << "[0] Exit\n";
}
Menu * MainMenu::getNextMenu() {
    int option;
    if(!input::get(option)){
        return invalidOption();
    }
    switch(option){
        case 0: return nullptr;
        case 1: return new LoginUserMenu(platform);
        case 2: return new RegisterUserMenu(platform);
        case 3: return new AdministratorMenu(platform);
        case 4: return new InformationMenu(platform);
        case 5: platform.save(); return this;
    }
    return invalidOption();
}

// --------------- Register User Menu ---------------
RegisterUserMenu::RegisterUserMenu(Platform &platform) : Menu(platform) {}
void RegisterUserMenu::show() {
    std::cout << CLR_SCREEN;
    std::cout << "Information required: username, name, birthdate, type of user\n";
}
Menu * RegisterUserMenu::getNextMenu() {
    std::string username, birth_date, name, type;
    std::cout << "username\n ";
    if(!input::get(username) || !input::validateNickname(username)){
        return invalidOption();
    }
    std::cout << "name\n "; name = input::getRaw();
    if(!input::validateName(name)){
        return invalidOption();
    }
    std::cout << "birth date\n ";
    if(!input::get(birth_date) || !input::validateBirthDate(birth_date)){
        return invalidOption();
    }
    std::cout << "type of user (viewer or streamer)\n ";
    if(!input::get(type)){
        return invalidOption();
    }
    if(type == "viewer"){
        try{
            platform.registerViewer(username, name, birth_date);
            std::cout << "Registered with success!" << std::endl;
        }
        catch(const UserAlreadyExists &e){
            std::cout << "Username already exists" << std::endl;
        }
        catch(const InvalidAge &e){
            std::cout << "Viewer minimum age must be " << MINIMUM_VIEWER_AGE << std::endl;
        }
    }
    else if(type == "streamer"){
        try{
            platform.registerStreamer(username, name, birth_date);
            std::cout << "Registered with success!" << std::endl;
        }
        catch(const UserAlreadyExists &e){
            std::cout << "Username already exists" << std::endl;
        }
        catch(const InvalidAge &e){
            std::cout << "Streamer minimum age must be " << MINIMUM_STREAMER_AGE << std::endl;
        }
    }
    input::waitEnter();
    return nullptr;
}

// --------------- Login User Menu ---------------
LoginUserMenu::LoginUserMenu(Platform &platform) : Menu(platform) {}
void LoginUserMenu::show() {
    if(!logged_in){
        std::cout << CLR_SCREEN;
        std::cout << "Username: " << std::endl;
    }
}
Menu * LoginUserMenu::getNextMenu() {
    if(!logged_in){
        std::string username;
        if(!input::get(username)){
            return invalidOption();
        }
        try{
            User * ptr = platform.getUser(username);
            Streamer * streamer_ptr = dynamic_cast<Streamer *>(ptr);
            if(streamer_ptr){
                logged_in = true;
                return new StreamerMenu(platform, streamer_ptr);
            }
            Viewer * viewer_ptr = dynamic_cast<Viewer *>(ptr);
            if(viewer_ptr){
                logged_in = true;
                return new ViewerMenu(platform, viewer_ptr);
            }
        }
        catch(const UserDoesNotExist &e){
            std::cout << "User " << e.getNickname() << " does not exist" << std::endl;
            input::waitEnter();
        }
    }
    return nullptr;
}


// --------------- Viewer Menu ---------------

ViewerMenu::ViewerMenu(Platform &platform, Viewer *viewer) : Menu(platform), viewer(viewer) {}
void ViewerMenu::show() {
    std::cout << CLR_SCREEN;
    unsigned int option = 1;
    if(viewer->inStream()){
        char feedback = viewer->getCurrentFeedback();
        screen::showScreen(); std::cout << std::endl;
        std::cout << "[" << option++ << "] Leave Stream" << std::endl;
        std::string color = feedback == 'L' ? BLUE : RESET;
        std::cout << "[" << option++ << "] " << color << "Like" << RESET << std::endl;
        color = feedback == 'D' ? RED : RESET;
        std::cout << "[" << option++ << "] " << color << "Dislike" << RESET << std::endl;
        std::cout << "[" << option++ << "] Donate" << std::endl;
        if(viewer->inPrivateStream()){
            std::cout << "[" << option++ << "] Comment" << std::endl;
        }
    }
    else{
        std::cout << "[" << option++ << "] Join Stream" << std::endl;
        std::cout << "[" << option++ << "] View stream history" << std::endl;
        std::cout << "[" << option++ << "] View liked streams history" << std::endl;
        std::cout << "[" << option++ << "] Remove stream from history" << std::endl;
        std::cout << "[" << option++ << "] View orders" << std::endl;
        std::cout << "[" << option++ << "] Remove order" << std::endl;
        std::cout << "[" << option++ << "] Access Store" << std::endl;
    }
    std::cout << "[" << option++ << "] Delete Account" << std::endl << std::endl;
    std::cout << "[0] Exit" << std::endl;
}
Menu * ViewerMenu::getNextMenu() {
    int option;
    if(!input::get(option))
        return invalidOption();
    if(option == 0){
        return nullptr;
    }
    if(viewer->inStream()){
        switch(option){
            case 1: viewer->leaveStream(); return this;
            case 2: viewer->like(); return this;
            case 3: viewer->dislike(); return this;
            case 4:
                int val, eval;
                std::cout << "value of donation\n";
                if(!input::get(val)){
                    return invalidOption();
                }
                std::cout << "evaluation (1-5) of streamer\n";
                if(!input::get(eval) || eval < MIN_EVAL || eval > MAX_EVAL){
                    return invalidOption();
                }
                Donation d(viewer->getCurrentStream().lock()->getStreamer(), val, eval);
                platform.addDonation(d);
                std::cout << "Donation successfully made!" << std::endl;
                input::waitEnter();
                return this;
        }
        if(viewer->inPrivateStream()){
            switch(option){
                case 5: return new SubmitCommentMenu(platform, viewer);
                case 6: platform.deleteUser(viewer->getNickname()); return nullptr;
            }
        }
        else{
            switch(option){
                case 6: platform.deleteUser(viewer->getNickname()); return nullptr;
            }
        }
    }
    else{
        unsigned int id, pos;
        std::string streamer;
        Store *store;
        switch(option){
            case 1: return new JoinStreamMenu(platform, viewer);
            case 2: platform.showStreamHistory(viewer->getStreamsHistory()); input::waitEnter(); return this;
            case 3: platform.showStreamHistory(viewer->getStreamsHistory(), 'L'); input::waitEnter(); return this;
            case 4: std::cout << "Stream id: "; if(input::get(id)){viewer->removeStreamFromHistory(id);} return this;
            case 5:
                viewer->showOrders();
                input::waitEnter();
                return this;
            case 6:
                if(input::get(pos)){
                    viewer->removeOrderAtPos(pos-1);
                }
                return this;
            case 7:
                std::cout << "Streamer name:" << std::endl;
                streamer = input::getRaw();
                store = platform.getStore(streamer);
                if(store != nullptr){
                    return new ViewerStoreMenu(platform, viewer, store);
                }
                return this;
            case 8: platform.deleteUser(viewer->getNickname()); return nullptr;
        }
    }
    return invalidOption();
}

// --------------- Streamer Menu ---------------

StreamerMenu::StreamerMenu(Platform &platform, Streamer *streamer) : Menu(platform), streamer(streamer) {}
void StreamerMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    std::cout << "[" << option++ << "] Information" << std::endl;
    if(streamer->inStream()){
        screen::showScreen(); std::cout << std::endl;
        std::cout << "[" << option++ << "] End Stream" << std::endl;
        std::cout << "[" << option++ << "] View stream info" << std::endl;
    }
    else{
        std::cout << "[" << option++ << "] Start stream" << std::endl;
        std::cout << "[" << option++ << "] View stream history" << std::endl;
        std::cout << "[" << option++ << "] Remove stream from history" << std::endl;
        std::cout << "[" << option++ << "] Store" << std::endl;
    }
    std::cout << "[" << option++ << "] Delete account" << std::endl << std::endl;
    std::cout << "[0] Exit" << std::endl;
}

Menu * StreamerMenu::getNextMenu() {
    unsigned int option;
    if(!input::get(option))
        return invalidOption();
    switch(option){
        case 0: return nullptr;
        case 1: return new InformationMenu(platform);
    }
    if(streamer->inStream()){
        switch(option){
            case 2: streamer->endStream(); return this;
            case 3: std::cout << CLR_SCREEN; streamer->showStreamInfo(); input::waitEnter(); return this;
            case 4: platform.deleteUser(streamer->getNickname()); return nullptr;
        }
    }
    else{
        unsigned int id;
        switch(option){
            case 2: return new CreateStreamMenu(platform, streamer);
            case 3: platform.showStreamHistory(streamer->getStreamsHistory()); input::waitEnter(); return this;
            case 4: std::cout << "Stream id: "; if(input::get(id)){streamer->removeStreamFromHistory(id);} return this;
            case 5: return new StreamerStoreMenu(platform, streamer->getStore());
            case 6: platform.deleteUser(streamer->getNickname()); return nullptr;
        }
    }
    return invalidOption();
}

// --------------- Administrator Menu ---------------

AdministratorMenu::AdministratorMenu(Platform &platform) : Menu(platform), admin(platform) {}
void AdministratorMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Information", "Show average views", "Filter streams", "Show Top Language",
                           "Show Top Stream Type", "Show Top Streamer", "Delete user", "Delete stream", "Change Max Product Limit",
                           "Reset Products Sold for all Stores",
                           "Show all donations",
                           "Search donations between evaluation",
                           "Search donations between evaluation and a minimum value",
                           "Search donations by streamer", "Search donations by value"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << std::endl << "[0] Exit" << std::endl;
}

Menu * AdministratorMenu::getNextMenu() {
    int option;
    if(!input::get(option))
        return invalidOption();
    std::string str; unsigned int id, max_orders;
    std::string streamer;
    unsigned int eval_lower, eval_higher, val;
    vector<Donation> temp;
    switch(option){
        case 0: return nullptr;
        case 1: return new InformationMenu(platform);
        case 2: std::cout << "Average views per stream: " << admin.averageViews() << std::endl; input::waitEnter(); return this;
        case 3: return new FilterStreamsMenu(platform, admin);
        case 4: std::cout << "Most used language in streams: " << admin.topLanguage() << std::endl; input::waitEnter(); return this;
        case 5: std::cout << "Most used stream type in streams: " << admin.topTypeStream() << std::endl; input::waitEnter(); return this;
        case 6: std::cout << "Streamer with most views: " << admin.topStreamer() << std::endl; input::waitEnter(); return this;
        case 7: std::cout << "Username: "; if(input::get(str)){platform.deleteUser(str);} return this;
        case 8: std::cout << "Stream id: "; if(input::get(id)){platform.deleteStream(id);} return this;
        case 9: std::cout << "New limit: "; if(input::get(max_orders)){platform.changeMaxProductsSoldPerStore(max_orders);} return this;
        case 10: platform.resetProductsSold(); return this;
        case 11: platform.showDonations();  input::waitEnter(); return this;
        case 12:
            temp.clear();
            std::cout << "lower evaluation: \n";
            if (!input::get(eval_lower) || eval_lower < MIN_EVAL || eval_lower > MAX_EVAL){
                return invalidOption();
            }
            std::cout << "higher evaluation: \n";
            if (!input::get(eval_higher) || eval_higher < MIN_EVAL || eval_higher > MAX_EVAL){
                return invalidOption();
            }
            temp = admin.getDonationsEval(eval_lower,eval_higher);
            if (temp.empty()){
                std::cout << "No donations match your criteria!" << std::endl;
            }
            else{
                for (int i = 0; i < temp.size(); i++){
                    std::cout << temp[i];
                }
            }
            input::waitEnter();
            return this;
        case 13:
            temp.clear();
            std::cout << "lower evaluation: \n";
            if (!input::get(eval_lower) || eval_lower < MIN_EVAL || eval_lower > MAX_EVAL){
                return invalidOption();
            }
            std::cout << "higher evaluation: \n";
            if (!input::get(eval_higher) || eval_higher < MIN_EVAL || eval_higher > MAX_EVAL){
                return invalidOption();
            }
            std::cout << "minimum value: \n";
            if (!input::get(val) || val <= 0){
                return invalidOption();
            }
            temp = admin.getDonationsEval(eval_lower,eval_higher, val);
            if (temp.empty()){
                std::cout << "No donations match your criteria!" << std::endl;
            }
            else{
                for (int i = 0; i < temp.size(); i++){
                    std::cout << temp[i];
                }
            }
            input::waitEnter();
            return this;
        case 14:
            temp.clear();
            std::cout << "streamer: \n";
            if (!input::get(streamer)){
                return invalidOption();
            }
            User* us;
            try{
                us = platform.getUser(streamer);
            }
            catch (UserDoesNotExist) {
                std::cout << "Streamer does not exist!" << std::endl;
                input::waitEnter();
                return this;
            }
            if (!dynamic_cast<Streamer*> (us)){
                std::cout << "Streamer does not exist!" << std::endl;
                input::waitEnter();
                return this;
            }
            temp = admin.getDonationsStreamer(streamer);
            if (temp.empty()){
                std::cout << "No donations match your criteria!" << std::endl;
            }
            else{
                for (int i = 0; i < temp.size(); i++){
                    std::cout << temp[i];
                }
            }
            input::waitEnter();
            return this;
        case 15:
            temp.clear();
            std::cout << "value: \n";
            if (!input::get(val)){
                return invalidOption();
            }
            temp = admin.getDonationsValue(val);
            if (temp.empty()){
                std::cout << "No donations match your criteria!" << std::endl;
            }
            else{
                for (int i = 0; i < temp.size(); i++){
                    std::cout << temp[i];
                }
            }
            input::waitEnter();
            return this;
    }
    return invalidOption();
}

// --------------- Filter Streams Menu ---------------
FilterStreamsMenu::FilterStreamsMenu(Platform &platform, Admin & admin) : Menu(platform), admin(admin) {}
void FilterStreamsMenu::show() {
    std::cout << "Information required: streams type (public or private) and lower and upper time interval limit\n";
}
Menu * FilterStreamsMenu::getNextMenu() {
    std::string type, lower_date, upper_date;

    std::cout << "Stream type\n "; type = input::getRaw();
    if (type != "public" && type != "private")
        return invalidOption();
    try {
        std::cout << "Lower date\n ";lower_date = input::getRaw();
        Date l_date(lower_date);
        std::cout << "Upper date\n ";upper_date = input::getRaw();
        Date u_date(upper_date);
    }
    catch (const InvalidDate &e) {
        std::cout << "Date " << e.getDate() << " is invalid!" << std::endl;
        input::waitEnter();
        return nullptr;
    }
    std::cout << "Number of " << type << " streams between " << lower_date << " and " << upper_date << ": ";
    std::cout << admin.streamsCounter(type == "public", Date(lower_date), Date(upper_date)) << std::endl;
    input::waitEnter();
    return nullptr;
}

// --------------- Filter Streamers Menu ---------------
FilterStreamersMenu::FilterStreamersMenu(Platform &platform) : Menu(platform) {}
void FilterStreamersMenu::show() {
    std::cout << "Information required: streamer type (active, inactive or leave it empty for no filter)\n";
}
Menu * FilterStreamersMenu::getNextMenu() {
    std::string type;

    std::cout << "Streamer type\n "; type = input::getRaw();
    if (type != "active" && type != "inactive" && !type.empty())
        return invalidOption();
    platform.showStreamers(type);
    input::waitEnter();
    return nullptr;
}

// --------------- Information Menu ---------------

InformationMenu::InformationMenu(Platform &platform) : Menu(platform) {}
void InformationMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Show top active streams", "Show top archived streams", "Show all active streams",
                           "Search active streams by language", "Search active streams by minimum age",
                           "Show all archived streams", "Show users", "Show streamers", "Sort active streams"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << std::endl << "[0] Exit" << std::endl;
}
Menu * InformationMenu::getNextMenu() {
    unsigned int option;
    if(!input::get(option))
        return invalidOption();

    std::string language, streamer;
    unsigned int minimum_age;
    unsigned int eval_lower, eval_higher, val;
    vector<Donation> temp;
    switch(option){
        case 0: return nullptr;
        case 1: platform.topActiveStreams(); input::waitEnter(); return this;
        case 2: platform.topArchivedStreams(); input::waitEnter(); return this;
        case 3: platform.showStreams(); input::waitEnter(); return this;
        case 4: std::cout << "language: ";
            if(!input::get(language)){
                return invalidOption();
            }
            std::transform(language.begin(), language.end(), language.begin(), ::toupper);
            platform.showStreams(language); input::waitEnter(); return this;
        case 5: std::cout << "minimum_age: ";
            if(!input::get(minimum_age)){
                return invalidOption();
            }
            platform.showStreams("", minimum_age); input::waitEnter(); return this;
        case 6: platform.showArchive(); input::waitEnter(); return this;
        case 7: platform.showUsers(); input::waitEnter(); return this;
        case 8: return new FilterStreamersMenu(platform);
        case 9: return new SortMenu(platform);
    }
    return invalidOption();
}

// --------------- Sort Menu ---------------
SortMenu::SortMenu(Platform &platform) : Menu(platform) {}
void SortMenu::show() {
    if(!stage2){
        std::cout << CLR_SCREEN << "Sort by: " << std::endl;
        unsigned int options = 1;
        std::cout << "[" << options++ << "] Views" << std::endl;
        std::cout << "[" << options++ << "] Likes" << std::endl;
        std::cout << "[" << options++ << "] Id" << std::endl;
        std::cout << "[" << options++ << "] Minimum Age" << std::endl << std::endl;
        std::cout << "[0] Exit" << std::endl;
    }
    else{
        std::cout << CLR_SCREEN << "Sort order: " << std::endl;
        unsigned int options = 1;
        std::cout << "[" << options++ << "] Ascending" << std::endl;
        std::cout << "[" << options++ << "] Descending" << std::endl << std::endl;
        std::cout << "[" << options++ << "] Back" << std::endl;
        std::cout << "[0] Exit" << std::endl;
    }
}
Menu * SortMenu::getNextMenu() {
    static sortingMode mode;
    int option;
    if(!input::get(option))
        return invalidOption();
    if(!stage2){
        switch(option){
            case 0: return nullptr;
            case 1: mode = views; stage2 = true; return this;
            case 2: mode = likes; stage2 = true; return this;
            case 3: mode = id; stage2 = true; return this;
            case 4: mode = minimum_age; stage2 = true; return this;
        }
        return invalidOption();
    }
    else{
        switch(option){
            case 0: return nullptr;
            case 1: platform.sort(mode, ascending); return nullptr;
            case 2: platform.sort(mode, descending); return nullptr;
            case 3: stage2 = false; return this;
        }
        return invalidOption();
    }
}

// ------------- Create Stream Menu -----------------
CreateStreamMenu::CreateStreamMenu(Platform &platform, Streamer * streamer) : Menu(platform), streamer(streamer){}
void CreateStreamMenu::show() {
    std::cout << CLR_SCREEN << "Please fill the following parameters" << std::endl;
}
Menu * CreateStreamMenu::getNextMenu() {
    std::cout << "Stream type ('public' or 'private')" << std::endl;
    std::string type;
    if(!input::get(type)){
        return invalidOption();
    }
    if(type == "public" || type == "private"){
        std::cout << "Stream title" << std::endl;
        std::string title = input::getRaw();
        if(!input::validateTitle(title)){
            return invalidOption();
        }
        std::cout << "Language" << std::endl;
        std::string language;
        if(!input::get(language)){
            return invalidOption();
        }
        std::transform(language.begin(), language.end(), language.begin(), ::toupper);
        std::cout << "Minimum age" << std::endl;
        unsigned int minimum_age;
        if(!input::get(minimum_age) || minimum_age > 125){
            return invalidOption();
        }
        if(type == "public"){
            streamer->startPublicStream(title, language, minimum_age);
        }
        else{
            std::cout << "Maximum capacity" << std::endl;
            unsigned int max_capacity;
            if(!input::get(max_capacity)){
                return invalidOption();
            }

            std::vector<std::string> allowed;
            std::string user;
            std::cout << "Allowed users (Write all users you wish to allow into the stream, submit blank username to complete)" << std::endl;

            while(true){
                if(!input::get(user)){
                    break;
                }
                allowed.push_back(user);
            }
            streamer->startPrivateStream(title, language, minimum_age, max_capacity, allowed);
        }
        std::cout << "Stream created with success!" << std::endl;
        input::waitEnter();
        return nullptr;
    }
    return invalidOption();
}

// ------------- Join Stream Menu -----------------
JoinStreamMenu::JoinStreamMenu(Platform &platform, Viewer *viewer) : Menu(platform), viewer(viewer) {}
void JoinStreamMenu::show() {
    std::cout << CLR_SCREEN << "Join stream" << std::endl << "Stream id or streamer name:" << std::endl;
}
Menu * JoinStreamMenu::getNextMenu() {
    std::string str = input::getRaw();
    if(str.empty()){
        return nullptr;
    }
    unsigned int id;
    if(input::strToVar(str, id)){ // Interpret string as an id
        try{
            viewer->joinStream(id);
        }
        catch(const StreamDoesNotExist &e){
            std::cout << "Stream with id " << id << " does not exist" << std::endl;
            input::waitEnter();
        }
        catch(const StreamNoLongerActive &e){
            std::cout << "Stream with id " << id << " already ended" << std::endl;
            input::waitEnter();
        }
    }
    else { // Interpret string as an username
        try {
            viewer->joinStream(str);
        }
        catch (const StreamerNotStreaming &e) {
            std::cout << "Streamer '" << e.getName() << "' isn't currently streaming" << std::endl;
            input::waitEnter();
        }
    }
    return nullptr;
}

// ----------- Submit Comment Menu ------------

SubmitCommentMenu::SubmitCommentMenu(Platform &platform, Viewer *viewer) : Menu(platform), viewer(viewer){}
void SubmitCommentMenu::show() {
    std::cout << CLR_SCREEN << "Comment: ";
}
Menu * SubmitCommentMenu::getNextMenu() {
    std::string comment = input::getRaw();
    if(comment.empty()){
        return nullptr;
    }
    viewer->comment(comment);
    std::cout << "Comment submitted" << std::endl;
    input::waitEnter();
    return nullptr;
}

// ------------- Viewer Store Menu ----------
ViewerStoreMenu::ViewerStoreMenu(Platform &platform, Viewer *viewer, Store *store) : Menu(platform), viewer(viewer), store(store), order(viewer, 1, store->getStreamer()){}
void ViewerStoreMenu::show() {
    unsigned int options = 1;
    std::cout << CLR_SCREEN;
    std::cout << "[" << options++ << "] Add Product to Order" << std::endl;
    std::cout << "[" << options++ << "] Remove Product from Order" << std::endl;
    std::cout << "[" << options++ << "] Change Availability" << std::endl;
    std::cout << "[" << options++ << "] Submit Order" << std::endl;
    std::cout << "[0] Exit" << std::endl << std::endl;
    std::cout << "Available products:" << std::endl;
    store->showMerchandise();
    std::cout << std::endl << "Current Order:\n-----------------------" << std::endl << order << std::endl;
    std::cout << "Total price: " << order.getTotalPrice() << "€" << std::endl;
    std::cout << "-----------------------" << std::endl;
}
Menu * ViewerStoreMenu::getNextMenu() {
    unsigned int option;
    if(!input::get(option))
        return invalidOption();

    unsigned int pos;
    switch(option){
        case 1:
            if(!input::get(pos)){
                return invalidOption();
            }
            try{
                order.addProduct(store->getProductByPos(pos-1));
            }
            catch(const ProductDoesntExist &e){
                return invalidOption();
            }
            return this;
        case 2:
            if(!input::get(pos)){
                return invalidOption();
            }
            try{
                order.removeProduct(store->getProductByPos(pos-1));
            }
            catch(const ProductDoesntExist &e){
                return invalidOption();
            }
            return this;
        case 3:
            if(!input::get(pos)){
                return invalidOption();
            }
            order.setDisp(pos);
            return this;
        case 4:
            if(order.getSize() > 0) {
                store->placeOrder(order);
            }
            return nullptr;
    }
    return nullptr;
}

// ------------- Streamer Store Menu ----------
StreamerStoreMenu::StreamerStoreMenu(Platform &platform, Store *store) : Menu(platform), store(store){}
void StreamerStoreMenu::show() {
    unsigned int options = 1;
    std::cout << CLR_SCREEN;
    std::cout << "[" << options++ << "] Show Orders" << std::endl;
    std::cout << "[" << options++ << "] Process Orders" << std::endl;
    std::cout << "[" << options++ << "] Add Product" << std::endl;
    std::cout << "[" << options++ << "] Remove Product" << std::endl;
    std::cout << "[0] Exit" << std::endl << std::endl;
    std::cout << "Products sold: " << store->getProductsSold() << "/" << store->getMaxProductsSold() << std::endl;
    std::cout << "Available products:" << std::endl;
    store->showMerchandise();
}
Menu * StreamerStoreMenu::getNextMenu() {
    unsigned int option;
    if(!input::get(option))
        return invalidOption();

    std::string name;
    double price;
    switch(option){
        case 1:
            store->showOrders();
            input::waitEnter();
            return this;
        case 2:
            store->processOrders();
            return this;
        case 3:
            std::cout << "Product name:" << std::endl;
            name = input::getRaw();
            if(name.empty()){return nullptr;}
            std::cout << "Price: " << std::endl;
            if(!input::get(price) || price <= 0){
                return this;
            }
            store->addMerchandise(name, price);
            return this;
        case 4:
            std::cout << "Product name:" << std::endl;
            name = input::getRaw();
            if(name.empty()){return this;}
            store->removeMerchandise(name);
            return this;
    }

    return nullptr;
}