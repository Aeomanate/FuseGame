// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <iostream>
#include <windows.h>
#include "Game/Game.hpp"

int main() {
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    try {
        Game().run();
    } catch (std::exception const& e) {
        std::cerr << "Error: \n####    " << e.what() << "    ####\nGame will be closed.";
    } catch (...) {
        std::cerr << "Happens strange unknown error.\nGame will be closed.";
    }
    
    return 0;
}