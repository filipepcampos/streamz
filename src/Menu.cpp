#include "Menu.h"

void Menu::title() const {
    cout << "\n"
            "   _____ _                            ______\n"
            "  / ____| |                          |___  /\n"
            " | (___ | |_ _ __ ___  __ _ _ __ ___    / / \n"
            "  \\___ \\| __| '__/ _ \\/ _` | '_ ` _ \\  / /  \n"
            "  ____) | |_| | |  __/ (_| | | | | | |/ /__ \n"
            " |_____/ \\__|_|  \\___|\\__,_|_| |_| |_/_____|\n"
            "\n";
}

void Menu::mainMenu() {
    unsigned int options = 0;

    /*AQUI*/   /* <---- Limpar consola */
    title();
    /* MAIS TARDE AJUSTAR ESPACAMENTO COM SETW() */
    cout << "Main Menu:\n\n";
    cout << "[" << ++options << "] " << "Show Info\n";
    cout << "[" << ++options << "] " << "Register User\n";
    cout << "[" << ++options << "] " << "Login User\n";
    cout << "[" << ++options << "] " << "Administrator\n";
    cout << "[" << ++options << "] " << "Manual Save\n"; // ?
    cout << "[0] Exit\n";

}