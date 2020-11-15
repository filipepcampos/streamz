#ifndef STREAMZ_MENU_H
#define STREAMZ_MENU_H
#include "Platform.h"
#include "Admin.h"
#include "Streamer.h"
#include "Viewer.h"
#include <iostream>
#include <map>
#include <functional>

#define CLR_SCREEN "\033[2J\033[1;1H"

class Menu{
protected:
    Platform &platform;

    template <typename T>
    bool getInput(T &var) const;

    std::string getRawInput() const;

    void waitEnter() const;

    Menu * invalidOption();
public:
    explicit Menu(Platform &platform);
    virtual ~Menu() = default;
    virtual void show() = 0;
    virtual Menu * getNextMenu() = 0;
};

class MainMenu : public Menu {
public:
    explicit MainMenu(Platform &platform);
    void show() override;
    Menu * getNextMenu() override;
};

class RegisterUserMenu : public Menu{
public:
    explicit RegisterUserMenu(Platform &platform);
    void show() override;
    Menu * getNextMenu() override;
};

class LoginUserMenu : public Menu{
    bool logged_in = false;
public:
    explicit LoginUserMenu(Platform &platform);
    void show() override;
    Menu * getNextMenu() override;
};

class ViewerMenu : public Menu{
    Viewer * viewer;
public:
    ViewerMenu(Platform &platform, Viewer * viewer);
    void show() override;
    Menu * getNextMenu() override;
};

class StreamerMenu : public Menu{
    Streamer * streamer;
public:
    StreamerMenu(Platform &platform, Streamer * streamer);
    void show() override;
    Menu * getNextMenu() override;
};

class AdministratorMenu : public Menu{
    Admin * admin;
public:
    AdministratorMenu(Platform &platform, Admin * admin);
    void show() override;
    Menu * getNextMenu() override;
};

class FilterStreamsMenu : public Menu{
    Admin * admin;
public:
    FilterStreamsMenu(Platform &platform, Admin * admin);
    void show() override;
    Menu * getNextMenu() override;
};

class InformationMenu : public Menu{
public:
    InformationMenu(Platform &platform);
    void show() override;
    Menu * getNextMenu() override;
};

class SortMenu : public Menu {
bool stage2 = false;
public:
    SortMenu(Platform &platform);
    void show() override;
    Menu * getNextMenu() override;
};

class CreateStreamMenu : public Menu{
    Streamer * streamer;
public:
    CreateStreamMenu(Platform &platform, Streamer * streamer);
    void show() override;
    Menu * getNextMenu() override;
};

class JoinStreamMenu : public Menu{
    Viewer * viewer;
public:
    JoinStreamMenu(Platform &platform, Viewer * viewer);
    void show() override;
    Menu * getNextMenu() override;
};

#endif //STREAMZ_MENU_H
