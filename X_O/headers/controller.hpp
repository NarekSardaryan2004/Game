#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include "screen.hpp"

class Controller {
public:
    Controller();
    void run();

private:
    Screen gameScreen;

};

#endif // CONTROLLER_HPP