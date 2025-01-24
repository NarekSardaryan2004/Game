#ifndef GAME_HPP
#define GAME_HPP

#include <chrono>
#include <vector>
#include <regex>

#include "board.hpp"
#include "player.hpp"
#include "enum.hpp"
#include "scoreManager.hpp"

class Game {
public:
    Game(Player& p1, Player& p2, Player& rand, int _size, int _time);

    void play(EGameDifficulty difficulty);
    static int getIntegerInput(const std::string &prompt);
    static char getCorrectSymbolInput(const std::string& prompt);

    ~Game();

private:
    bool checkWin();
    bool checkDraw();
    void switchPlayer();
    void timerManager();

private:
    int _passedTime;
    int _playerMoveTime;
    Player& _randomBlock;
    Player& _player1;
    Player& _player2;

    Board* _board;
};

#endif // GAME_HPP