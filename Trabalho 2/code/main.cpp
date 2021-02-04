#include "Platform.h"
#include "Menu.h"
#include <stack>
#include <iomanip>

int main(int argc, char* argv[]) {
    std::cout << std::left;
    Platform platform;
    std::stack<Menu *> menus;
    menus.push(new MainMenu(platform));

    while(!menus.empty()){
        menus.top()->show();
        Menu * ptr = menus.top()->getNextMenu();
        if(ptr){
            if(ptr != menus.top()){
                menus.push(ptr);
            }
        }
        else{
            delete menus.top();
            menus.pop();
        }
    }
    return 0;
}