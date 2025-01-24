#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>

class Player {
public:
    Player(std::string playerName, char playerSymbol);

    std::string getName();
    char getSymbol();
    
private:
    std::string _playerName;
    char _symbol;
};

#endif // PLAYER_HPP