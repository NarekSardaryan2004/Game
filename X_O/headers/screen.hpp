#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <ncurses.h>
#include <iostream>
#include <vector>

#include "player.hpp"
#include "game.hpp"
#include "enum.hpp"

class Screen {
public:
    Screen();
    void initializeNcurses();
    void showMenu();
    void cleanupNcurses();

private:
    Player _player1;
    Player _player2;
    Player _randomPlayer;
    std::string _name1, _name2;
    int _boardSize, _time;
    EGameDifficulty difficulty;

private:
    void playButton();
    void difficultyButton();
    void aboutButton();
    void easy();
    void medium();
    void hard();

};

#endif  // SCREEN_HPP