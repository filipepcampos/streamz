#include <iostream>
#include "Platform.h"
#include "PrivateStream.h"
#include "Viewer.h"
#include "Stream.h"
#include "Menu.h"
#include <stack>

int main(int argc, char* argv[]) {
    Platform platform;
    stack<Menu *> menus;
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
    platform.save();
    return 0;
}