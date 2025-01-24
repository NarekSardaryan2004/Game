#include "game.hpp"

using SteadyClock = std::chrono::steady_clock;
using TimePoint = std::chrono::time_point<SteadyClock>; 

namespace {

const std::chrono::milliseconds SECONDS_UPDATE_TIME{1000};

TimePoint secondsCountingStartTime;

}

Game::Game(Player& p1, Player& p2, Player& rand, int _size, int _time) : _playerMoveTime(_time), _randomBlock(rand), _player1(p1), _player2(p2) {
    _passedTime = 0;
    secondsCountingStartTime = std::chrono::steady_clock::now();
    Player p = p1;
    _board = new Board(_size, p);
}

bool Game::checkWin() {
    int winSymbols = (_board->getSize() <= 7) ? 3 : _board->getSize() / 2;

    for (int i = 0; i < _board->getSize(); ++i) {
        for (int j = 0; j <= _board->getSize() - winSymbols; ++j) {
            bool win = true;
            for (int k = 0; k < winSymbols; ++k) {
                if (_board->getBoard()[i][j + k] != _board->getCurrPlayer().getSymbol()) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    for (int i = 0; i < _board->getSize(); ++i) {
        for (int j = 0; j <= _board->getSize() - winSymbols; ++j) {
            bool win = true;
            for (int k = 0; k < winSymbols; ++k) {
                if (_board->getBoard()[j + k][i] != _board->getCurrPlayer().getSymbol()) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    for (int i = 0; i <= _board->getSize() - winSymbols; ++i) {
        for (int j = 0; j <= _board->getSize() - winSymbols; ++j) {
            bool win = true;
            for (int k = 0; k < winSymbols; ++k) {
                if (_board->getBoard()[i + k][j + k] != _board->getCurrPlayer().getSymbol()) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    for (int i = 0; i <= _board->getSize() - winSymbols; ++i) {
        for (int j = winSymbols - 1; j < _board->getSize(); ++j) {
            bool win = true;
            for (int k = 0; k < winSymbols; ++k) {
                if (_board->getBoard()[i + k][j - k] != _board->getCurrPlayer().getSymbol()) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    }

    return false;
}

bool Game::checkDraw() {
    if (checkWin()) return false;
    for (int i = 0; i < _board->getSize(); ++i)
        for (int j = 0; j < _board->getSize(); ++j)
            if (_board->getBoard()[i][j] == ' ') return false;
    return true;
}

void Game::switchPlayer() {
    auto& player = _board->getCurrPlayer();
    player = (player.getSymbol() == _player1.getSymbol()) ? _player2 : _player1;
}

void Game::timerManager() {
    auto currentTime = std::chrono::steady_clock::now();
    
    int timeLeft = _playerMoveTime - _passedTime;
    int colorPair;

    if (timeLeft > 5) {
        colorPair = 5;
    } else if (timeLeft > 3) {
        colorPair = 3;
    } else {
        colorPair = 4;
    }
    
    attron(COLOR_PAIR(colorPair));
    mvprintw(_board->getSize() * 2 + 3, 0, "Time left: %d seconds", timeLeft);
    attroff(COLOR_PAIR(colorPair));

    if (currentTime - secondsCountingStartTime >= SECONDS_UPDATE_TIME) {
        ++_passedTime;
        if(_passedTime >= _playerMoveTime) {
            switchPlayer();
            _board->updateScreen();
            _passedTime = 0;
        }
        secondsCountingStartTime = currentTime;
    }
}

void Game::play(EGameDifficulty difficulty) {
    noecho();
    clear();
    curs_set(1);
    nodelay(stdscr, true);
    int row = 0, col = 0, ch, numberOfSymbols = 0;

    _board->updateScreen();

    while (true) {

        ch = getch();
        if (ch != -1) {
            _board->updateScreen();
        }

        switch (ch) {
            case 'W':
            case 'w':
            case KEY_UP: 
                row = (row > 0) ? row - 1 : _board->getSize() - 1;
                break;
            case 'S':
            case 's':
            case KEY_DOWN: 
                row = (row < _board->getSize() - 1) ? row + 1 : 0; 
                break;
            case 'A':
            case 'a':
            case KEY_LEFT: 
                col = (col > 0) ? col - 1 : _board->getSize() - 1; 
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT: 
                col = (col < _board->getSize() - 1) ? col + 1 : 0; 
                break;
            case '\n':
                if (_board->getBoard()[row][col] == ' ') {
                    _board->getBoard()[row][col] = _board->getCurrPlayer().getSymbol();
                    ++numberOfSymbols;  

                    if (checkWin()) {
                        _board->resetScreenDifficulty();
                        _board->updateScreen();
                        attron(COLOR_PAIR(5));
                        mvprintw(_board->getSize() * 2 + 2, 0, "Player %s wins!\n", _board->getCurrPlayer().getName().c_str());
                        attroff(COLOR_PAIR(5));
                        int wins = 0;
                        wins++;
                        ScoreManager scoremanager;
                        scoremanager.createFile("data/scores.txt", _board->getCurrPlayer().getName(), wins);
                        getch();
                        return;
                    }
                    else if (checkDraw()) {
                        _board->resetScreenDifficulty();
                        _board->updateScreen();
                        attron(COLOR_PAIR(6));
                        mvprintw(_board->getSize() * 2 + 2, 0, "It's a draw!\n");
                        attroff(COLOR_PAIR(6));
                        getch();
                        return;
                    }
                    switchPlayer();
                    _board->updateScreen();
                    _passedTime = 0;

                } else {
                    _board->updateScreen();
                    attron(COLOR_PAIR(4));
                    mvprintw(_board->getSize() * 2 + 4, 0, "Cell already taken! Try again.");
                    attroff(COLOR_PAIR(4));
                }
            break;
        }

        if (difficulty == EGameDifficulty::MEDIUM) {
            timerManager();
        }
        else if (difficulty == EGameDifficulty::HARD) {
            timerManager();
            int rand_row, rand_col;

            if (ch != -1) {
                do {
                    rand_row = std::rand() % _board->getSize();
                    rand_col = std::rand() % _board->getSize();
                } while (_board->getBoard()[rand_row][rand_col] != ' ');
                if (numberOfSymbols == 2) {
                    if (_board->getBoard()[rand_row][rand_col] == ' ') {
                        _board->getBoard()[rand_row][rand_col] = _randomBlock.getSymbol();
                        numberOfSymbols = 0;

                        if (checkWin()) {
                            _board->resetScreenDifficulty();
                            _board->updateScreen();
                            attron(COLOR_PAIR(5));
                            mvprintw(_board->getSize() * 2 + 2, 0, "Player %s wins!\n", _board->getCurrPlayer().getName().c_str());
                            attroff(COLOR_PAIR(5));
                            int wins = 0;
                            wins++;
                            ScoreManager scoremanager;
                            scoremanager.createFile("data/scores.txt", _board->getCurrPlayer().getName(), wins);
                            getch();
                            return;
                        }
                        else if (checkDraw()) {
                            _board->resetScreenDifficulty();
                            _board->updateScreen();
                            attron(COLOR_PAIR(6));
                            mvprintw(_board->getSize() * 2 + 2, 0, "It's a draw!\n");
                            attroff(COLOR_PAIR(6));
                            getch();
                            return;
                        }
                    }
                }
            }
        }

        move(2 * row + 1, 4 * col + 2);
        refresh();
    }
}

int Game::getIntegerInput(const std::string& prompt) {
    char input[100];
    int value;
    std::regex integerRegex("^[0-9]+$");

    while (true) {
        getstr(input);

        if (std::regex_match(input, integerRegex)) {
            try {
                value = std::stoi(input);
                return value;
            }
            catch (const std::out_of_range&) {
                attron(COLOR_PAIR(4));
                printw("Input is out of range! Please enter a smaller integer. ");
                attroff(COLOR_PAIR(4));
            }
        } else {
            attron(COLOR_PAIR(4));
            printw("Invalid input! Please enter a valid integer. ");
            attroff(COLOR_PAIR(4));
        }
    }
}

char Game::getCorrectSymbolInput(const std::string& prompt) {
    char input[100];
    std::regex symbolRegex("^[XO]$", std::regex_constants::icase);

    while (true) {
        getstr(input);

        if (std::regex_match(input, symbolRegex)) {
            return toupper(input[0]);
        }
        else {
            attron(COLOR_PAIR(4));
            printw("Invalid symbol! Please enter X or O. ");
            attroff(COLOR_PAIR(4));
        }
    }
}

Game::~Game() {
    delete _board;
}