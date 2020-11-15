#include "Menu.h"
#include <sstream>

Menu::Menu(Platform &platform) : platform(platform) {}

template <typename T>
T Menu::getInput() const {
    std::string str;
    std::cout << "> ";
    std::getline(std::cin, str);
    std::cout << std::endl;
    std::stringstream ss{str};
    T var; ss >> var;
    while (!ss.eof()) {
        std::cout << "Invalid type\n";
        ss.clear(); str.clear(); ss.str("");
        std::cout << "> ";
        std::getline(std::cin, str);
        std::cout << std::endl;
        ss << str;
        ss >> var;
    }
    return var;
}

void Menu::waitEnter() const {
    std::cout << std::endl << "Press enter to continue..." << std::endl;
    std::string str;
    std::getline(std::cin, str);
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
    cout << "[" << ++options << "] " << "Manual Save\n"; // ?
    cout << "[0] Exit\n";
}
Menu * MainMenu::getNextMenu() {
    int option = getInput<int>();
    switch(option){
        case 0: return nullptr;
        case 1: return new LoginUserMenu(platform);
        case 2: return new RegisterUserMenu(platform);
        case 3: {Admin admin(&platform); return new AdministratorMenu(platform, &admin);}
        case 4: return new InformationMenu(platform);
        case 5: platform.save(); return this;
    }
    return nullptr;
}

// --------------- Register User Menu ---------------
RegisterUserMenu::RegisterUserMenu(Platform &platform) : Menu(platform) {}
void RegisterUserMenu::show() {
    std::cout << "Information required: username, name, birthdate, type of user\n";
}
Menu * RegisterUserMenu::getNextMenu() {
    std::string username, birth_date, name, type;
    std::cout << "username\n "; username = getInput<string>();
    std::cout << "name\n "; name = getInput<string>();
    std::cout << "birth date\n "; birth_date = getInput<string>();
    std::cout << "type of user (viewer or streamer)\n "; type = getInput<string>();
    if(type == "viewer"){
        try{
            platform.registerViewer(username, name, birth_date);
            std::cout << "Registered with success!" << std::endl;
        }
        catch(const UserAlreadyExists &e){
            std::cout << "Username already exists" << std::endl;
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
    }
    waitEnter();
    return nullptr;
}

// --------------- Login User Menu ---------------
LoginUserMenu::LoginUserMenu(Platform &platform) : Menu(platform) {}
void LoginUserMenu::show() {
    if(!logged_in){
        std::cout << CLR_SCREEN;
        std::cout << "Username: ";
    }
}
Menu * LoginUserMenu::getNextMenu() {
    if(!logged_in){
        std::string username = getInput<string>();
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
    std::cout << "Viewer options" << std::endl;
}
Menu * ViewerMenu::getNextMenu() {
    int option = getInput<int>();
    return nullptr;
}

// --------------- Streamer Menu ---------------

StreamerMenu::StreamerMenu(Platform &platform, Streamer *streamer) : Menu(platform), streamer(streamer) {}
void StreamerMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Information", "Start Stream", "End Stream", "Delete account"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << "[0] Exit" << std::endl;
}

Menu * StreamerMenu::getNextMenu() {
    int option = getInput<int>();
    switch(option){
        case 1: return new InformationMenu(platform);
        case 2: std::cout << "Under development\n"; return this;
        case 3: std::cout << "Under development\n"; return this;
        case 4: platform.deleteUser(streamer->getNickname()); return nullptr;
    }
    return nullptr;
}

// --------------- Administrator Menu ---------------

AdministratorMenu::AdministratorMenu(Platform &platform, Admin * admin) : Menu(platform), admin(admin) {}
void AdministratorMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Show average views", "Filter streams", "Show Top Language", "Show Top Stream Type", "Show Top Streamer"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << "[0] Exit" << std::endl;
}

Menu * AdministratorMenu::getNextMenu() {
    int option = getInput<int>();
    switch(option){
        case 1: std::cout << "Average views per stream: " << admin->averageViews() << std::endl; waitEnter(); return this;
        case 2: return new FilterStreamsMenu(platform, admin);
        case 3: std::cout << "Most used language in streams: " << admin->topLanguage() << std::endl; waitEnter(); return this;
        case 4: std::cout << "Most used stream type in streams: " << admin->topTypeStream() << std::endl; waitEnter(); return this;
        case 5: std::cout << "Streamer with most views: "; admin->topStreamer()->show(); std::cout << std::endl; waitEnter(); return this;
    }
    return nullptr;
}

// --------------- Filter Streams Menu ---------------
FilterStreamsMenu::FilterStreamsMenu(Platform &platform, Admin * admin) : Menu(platform), admin(admin) {}
void FilterStreamsMenu::show() {
    std::cout << "Information required: streams type (public or private) and lower and upper time interval limit\n";
}
Menu * FilterStreamsMenu::getNextMenu() {
    std::string type, lower_date, upper_date;

    std::cout << "Stream type\n "; type = getInput<string>();
    while (type != "public" && type != "private") {
        std::cout << "Invalid type\n";
        type = getInput<string>();
    }
    /* MAIS TARDE VERIFICAR DATAS INVALIDAS */
    std::cout << "Lower date\n "; lower_date = getInput<string>();
    std::cout << "Upper date\n "; upper_date = getInput<string>();
    /* MAIS TARDE VERIFICAR DATAS INVALIDAS */
    std::cout << "Number of " << type << " streams between " << lower_date << " and " << upper_date << ": ";
    std::cout << admin->streamsCounter(type == "public", Date(lower_date), Date(upper_date)) << std::endl;
    waitEnter();
    return nullptr;
}

// --------------- Information Menu ---------------

InformationMenu::InformationMenu(Platform &platform) : Menu(platform) {}
void InformationMenu::show() {
    unsigned int option = 1;
    std::cout << CLR_SCREEN;
    for(const auto &str : {"Show Top Active Streams", "Show Top Archived Streams", "Show all active streams", "Show users"}){
        std::cout << "[" << option++ << "] " << str << std::endl;
    }
    std::cout << "[0] Exit" << std::endl;
}
Menu * InformationMenu::getNextMenu() {
    unsigned int option = getInput<int>();
    switch(option){
        case 1: platform.topActiveStreams(); waitEnter(); return this;
        case 2: platform.topArchivedStreams(); waitEnter(); return this;
        case 3: platform.showStreams(); waitEnter(); return this;
        case 4: platform.showUsers(); waitEnter(); return this;
    }
    return nullptr;
}