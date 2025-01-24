#include "controller.hpp"

Controller::Controller() {}

void Controller::run() {
    gameScreen.initializeNcurses();
    gameScreen.showMenu();
    gameScreen.cleanupNcurses();
}