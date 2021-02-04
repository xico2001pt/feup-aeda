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
#define BLUE "\u001b[36m"
#define RED "\u001b[31m"
#define GREEN "\u001b[32m"
#define RESET "\u001b[0m"

namespace screen{
    const unsigned WIDTH = 40;
    const unsigned HEIGHT = 10;
    const std::string image[10][40] = {{RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET},
                                        {RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET},
                                        {RESET, RESET, GREEN,  GREEN , GREEN , GREEN , RESET, RESET, GREEN,  GREEN,  GREEN , GREEN , GREEN , RESET, RESET, GREEN , GREEN,  GREEN , GREEN,  RESET, RESET, RESET, GREEN , GREEN , GREEN , GREEN , RESET, RESET, RESET, GREEN , GREEN , RESET, RESET, RESET, GREEN , RESET, RESET, RESET, GREEN, RESET},
                                        {RESET, RESET, GREEN,  RESET, RESET, RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, GREEN , GREEN,  RESET, GREEN , GREEN, RESET},
                                        {RESET, RESET, GREEN , RESET, RESET, RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, GREEN,  RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, GREEN, RESET, GREEN, RESET},
                                        {RESET, RESET, GREEN,  GREEN,  GREEN,  GREEN,  RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , GREEN , GREEN , RESET, RESET, RESET, RESET, GREEN , GREEN , GREEN , GREEN , RESET, RESET, GREEN , GREEN , GREEN , GREEN , RESET, RESET, GREEN , RESET, RESET, RESET, GREEN, RESET},
                                        {RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, RESET, GREEN, RESET},
                                        {RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET ,GREEN , RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, RESET, GREEN, RESET},
                                        {RESET, RESET, GREEN,  GREEN,  GREEN,  GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, RESET, GREEN , RESET, RESET, RESET, GREEN , RESET, RESET, GREEN , GREEN , GREEN , GREEN , RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, GREEN , RESET, RESET, RESET, GREEN, RESET},
                                        {RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET, RESET}};
    void showScreenLine(const std::string &code);
    void showScreen();
}

class Menu{
protected:
    Platform &platform;

    Menu * invalidOption();
public:
    explicit Menu(Platform &platform);
    virtual ~Menu() = default;
    /**
     * Show information associated with the menu
     */
    virtual void show() = 0;
    /**
     * Return a pointer to the next menu ('nullptr' and 'this' can also be returned)
     * nullptr -> Return to previous menu
     * this -> Don't change the menu
     * @return Menu * to next menu
     */
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
    Admin admin;
public:
    AdministratorMenu(Platform &platform);
    void show() override;
    Menu * getNextMenu() override;
};

class FilterStreamsMenu : public Menu{
    Admin & admin;
public:
    FilterStreamsMenu(Platform &platform, Admin & admin);
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

class SubmitCommentMenu : public Menu{
    Viewer * viewer;
public:
    SubmitCommentMenu(Platform &platform, Viewer * viewer);
    void show() override;
    Menu * getNextMenu() override;
};

#endif //STREAMZ_MENU_H
