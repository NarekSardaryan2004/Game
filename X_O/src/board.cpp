#include "board.hpp"

Board::Board(int board_size, Player curr_player) 
    : _size(board_size), _currentPlayer(curr_player) {
        initializeBoard();
    }

void Board::initializeBoard() {
    _board = std::vector<std::vector<char>>(_size, std::vector<char>(_size, ' '));
}

void Board::printBoard() {
    clear();
    for (int i = 0; i < _size; ++i) {
        for (int j = 0; j < _size; ++j) {
            mvprintw(2 * i + 1, 4 * j + 2, "%c", _board[i][j]);
        }
        attron(COLOR_PAIR(3));
        if (i < _size - 1) {
            for (int j = 0; j < _size; ++j) {
                mvprintw(2 * i + 2, 4 * j + 1, "----");
            }
        }
        attroff(COLOR_PAIR(3));
    }

    for (int i = 1; i < 2 * _size; ++i) {
        attron(COLOR_PAIR(3));
        for (int j = 1; j < _size; ++j) {
            mvprintw(i, 4 * j, "|");
        }
        attroff(COLOR_PAIR(3));
    }
    refresh();
}

void Board::updateScreen() {
    clear();
    printBoard();
    mvprintw(_size * 2 + 2, 0, "%s (%c), use arrow keys to move, Enter to select", 
        _currentPlayer.getName().c_str(), _currentPlayer.getSymbol());
    refresh();
}

void Board::resetScreenDifficulty() {
    nodelay(stdscr, false);
    curs_set(0);
    refresh();
    clear();
}

std::vector<std::vector<char>>& Board::getBoard() {
    return _board;
}

int Board::getSize() {
    return _size;
}

Player& Board::getCurrPlayer() {
    return _currentPlayer;
}