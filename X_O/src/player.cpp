#include "player.hpp"

Player::Player(std::string playerName, char playerSymbol) : _playerName(playerName), _symbol(playerSymbol) {}

std::string Player::getName() {
    return _playerName;
}

char Player::getSymbol() {
    return _symbol;
}