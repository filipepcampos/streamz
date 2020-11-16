#include "Menu.h"
#include "Input.h"
#include <sstream>
#include <algorithm>

Menu::Menu(Platform &platform) : platform(platform) {}

void Menu::waitEnter() {
    std::cout << std::endl << "Press enter to continue..." << std::endl;
    std::string str;
    std::getline(std::cin, str);
}

Menu * Menu::invalidOption() {
    std::cout << "Invalid option" << std::endl;
    waitEnter();
    return this;
}

// --------------- Main Menu ---------------

MainMenu::MainMenu(Platform &platform) : Menu(platform) {}
void MainMenu::show() {
    unsigned int options = 0;

    std::cout << CLR_SCREEN;
    cout << "\n"
            "   _____ _                            ______\n"
            "  / ____| |                          |___  /\n"
            " | (___ | |_ _ __ ___  __ _ _ __ ___    / / \n"
            "  \\___ \\| __| '__/ _ \\/ _` | '_ ` _ \\  / /  \n"
            "  ____) | |_| | |  __/ (_| | | | | | |/ /__ \n"
            " |_____/ \\__|_|  \\___|\\__,_|_| |_| |_/_____|\n"
            "\n";

    /* MAIS TARDE AJUSTAR ESPACAMENTO COM SETW() */
    cout << "Main Menu:\n\n";
    cout << "[" << ++options << "] " << "Login User\n";
    cout << "[" << ++options << "] " << "Register User\n";
    cout << "[" << ++options << "] " << "Administrator\n";
    cout << "[" << ++options << "] " << "Show information\n";
    cout << "[" << ++options << "] " << "Manual Save\n\n"; // ?
    cout << "[0] Exit\n";
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
    waitEnter();
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
            std::cout << "User " << e.getNickname() << " does not exist" << endl;
            waitEnter();
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
        std::cout << "[" << option++ << "] Leave Stream" << std::endl;
        std::cout << "[" << option++ << "] Like" << std::endl;
        std::cout << "[" << option++ << "] Dislike" << std::endl;
        if(viewer->inPrivateStream()){
            std::cout << "[" << option++ << "] Comment" << std::endl;
        }
    }
    else{
        std::cout << "[" << option++ << "] Join Stream" << std::endl;
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
            case 2: std::cout << "Under development...\n"; return this;
            case 3: std::cout << "Under development...\n"; return this;
        }
        if(viewer->inPrivateStream()){
            switch(option){
                case 4: return new SubmitCommentMenu(platform, viewer);
                case 5: platform.deleteUser(viewer->getNickname()); return nullptr;
            }
        }
        else{
            switch(option){
                case 5: platform.deleteUser(viewer->getNickname()); return nullptr;
            }
        }
    }
    else{
        switch(option){
            case 1: return new JoinStreamMenu(platform, viewer);
            case 2: platform.deleteUser(viewer->getNickname()); return nullptr;
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
        std::cout << "[" << option++ << "] End Stream" << std::endl;
        std::cout << "[" << option++ << "] View stream info" << std::endl;
    }
    else{
        std::cout << "[" << option++ << "] Start stream" << std::endl;
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
            case 3: std::cout << CLR_SCREEN; streamer->showStreamInfo(); waitEnter(); return this;
            case 4: platform.deleteUser(streamer->getNickname()); return nullptr;
        }
    }
    else{
        switch(option){
            case 2: return new CreateStreamMenu(platform, streamer);
            case 3: platform.deleteUser(streamer->getNickname()); return nullptr;
        }
    }
    return invalidOption();
}

// --------------- Administrator Menu ---------------

AdministratorMenu::AdministratorMenu(Platform &platform) : Menu(platform), admin(platform) {}
void AdministratorMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Show average views", "Filter streams", "Show Top Language", "Show Top Stream Type", "Show Top Streamer"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << "[0] Exit" << std::endl;
}

Menu * AdministratorMenu::getNextMenu() {
    int option;
    if(!input::get(option))
        return invalidOption();
    switch(option){
        case 0: return nullptr;
        case 1: std::cout << "Average views per stream: " << admin.averageViews() << std::endl; waitEnter(); return this;
        case 2: return new FilterStreamsMenu(platform, admin);
        case 3: std::cout << "Most used language in streams: " << admin.topLanguage() << std::endl; waitEnter(); return this;
        case 4: std::cout << "Most used stream type in streams: " << admin.topTypeStream() << std::endl; waitEnter(); return this;
        case 5:
            std::cout << "Streamer with most views: ";
            Streamer * strm = admin.topStreamer();
            if(strm){
                std::cout << strm->getNickname();
            }
            else{
                std::cout << "No streamer registered";
            }
            std::cout << std::endl; waitEnter(); return this;
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
    /* MAIS TARDE VERIFICAR DATAS INVALIDAS */
    input::getRaw();
    std::cout << "Lower date\n ";lower_date = input::getRaw();
    std::cout << "Upper date\n ";upper_date = input::getRaw();
    /* MAIS TARDE VERIFICAR DATAS INVALIDAS */
    std::cout << "Number of " << type << " streams between " << lower_date << " and " << upper_date << ": ";
    std::cout << admin.streamsCounter(type == "public", Date(lower_date), Date(upper_date)) << std::endl;
    waitEnter();
    return nullptr;
}

// --------------- Information Menu ---------------

InformationMenu::InformationMenu(Platform &platform) : Menu(platform) {}
void InformationMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Show top active streams", "Show Top archived streams", "Show all active streams",
                           "Search active streams by language", "Search active streams by minimum age",
                           "Show all archived streams", "Show users", "Sort active streams"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << std::endl << "[0] Exit" << std::endl;
}
Menu * InformationMenu::getNextMenu() {
    unsigned int option;
    if(!input::get(option))
        return invalidOption();

    std::string language;
    unsigned int minimum_age;
    switch(option){
        case 0: return nullptr;
        case 1: platform.topActiveStreams(); waitEnter(); return this;
        case 2: platform.topArchivedStreams(); waitEnter(); return this;
        case 3: platform.showStreams(); waitEnter(); return this;
        case 4: std::cout << "language: ";
            if(!input::get(language)){
                return invalidOption();
            }
            std::transform(language.begin(), language.end(), language.begin(), ::toupper);
            platform.showStreams(language); waitEnter(); return this;
        case 5: std::cout << "minimum_age: ";
            if(!input::get(minimum_age)){
                return invalidOption();
            }
            platform.showStreams("", minimum_age); waitEnter(); return this;
        case 6: platform.showArchive(); waitEnter(); return this;
        case 7: platform.showUsers(); waitEnter(); return this;
        case 8: return new SortMenu(platform);
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
        if(title.empty()){
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

            vector<string> allowed;
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
        waitEnter();
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
            waitEnter();
        }
        catch(const StreamNoLongerActive &e){
            std::cout << "Stream with id " << id << " already ended" << std::endl;
            waitEnter();
        }
    }
    else { // Interpret string as an username
        try {
            viewer->joinStream(str);
        }
        catch (const StreamerNotStreaming &e) {
            std::cout << "Streamer '" << e.getName() << "' isn't currently streaming" << std::endl;
            waitEnter();
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
    waitEnter();
    return nullptr;
}