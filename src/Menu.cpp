#include "Menu.h"
#include <sstream>

Menu::Menu(Platform &platform) : platform(platform) {}

template <typename T>
T Menu::getInput() const {
    std::string str;
    std::cout << "> ";
    std::getline(std::cin, str);
    std::cout << std::endl;
    std::istringstream ss{str};
    T var; ss >> var;
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
        case 3: cout << "Under development...\nGoodbye!\n"; break;
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