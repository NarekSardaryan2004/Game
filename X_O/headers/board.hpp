#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <ncurses.h>

#include "player.hpp"

class Board {
public:
    Board(int board_size, Player curr_player);

    void printBoard();
    void updateScreen();
    void resetScreenDifficulty();
    void initializeBoard();

    std::vector<std::vector<char>>& getBoard();
    int getSize();
    Player& getCurrPlayer();

private:
    int _size;
    std::vector<std::vector<char>> _board;
    Player& _currentPlayer;

};

#endif // BOARD_HPP