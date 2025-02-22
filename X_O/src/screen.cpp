#include "screen.hpp"

Screen::Screen() : _player1("Player 1", 'X'), _player2("Player 2", 'O'), _randomPlayer("RandomPlayer", '#'), _boardSize(3) {}

void Screen::initializeNcurses() {
    initscr();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_GREEN, COLOR_BLACK);
    init_color(COLOR_WHITE + 1, 500, 500, 500);
    init_pair(6, COLOR_WHITE + 1, COLOR_BLACK);
}

void Screen::playButton() {
    clear();
    refresh();
    echo();
    printw("Enter name for Player 1: ");
    char temp1[100];
    getstr(temp1);
    _name1 = std::string(temp1);

    printw("Enter symbol for Player1 (X or O): ");
    char symbol1 = Game::getCorrectSymbolInput("Enter symbol for Player 1 (X or O): ");

    printw("Enter name for Player 2: ");
    char temp2[100];
    getstr(temp2);
    _name2 = std::string(temp2);

    Player _player1(_name1, symbol1);
    Player _player2(_name2, (symbol1 == 'X' ? 'O' : 'X'));

    Game game(_player1, _player2, _randomPlayer, _boardSize, _time);
    game.play(difficulty);
}

void Screen::difficultyButton() {
    clear();
    echo();
    while (true) {
        const std::vector<std::string> difficultyOptions = {"Easy", "Medium", "Hard", "Back"};
        unsigned select = 0;
        while (true) {
            noecho();
            curs_set(0);
            for (std::size_t i = 0; i < difficultyOptions.size(); ++i) {
                int colorPair = (i == select) ? (i == 0 ? 5 : (i == 1 ? 3 : (i == 2 ? 4 : 6))) : 2;
                attron(COLOR_PAIR(colorPair));
                mvprintw(10 + i, 45, "%s", difficultyOptions[i].c_str());
                attroff(COLOR_PAIR(colorPair));
            }

            int ch = getch();
            switch (ch) {
                case KEY_UP:
                    select = (select == 0) ? difficultyOptions.size() - 1 : select - 1;
                    break;
                case KEY_DOWN:
                    select = (select == difficultyOptions.size() - 1) ? 0 : select + 1;
                    break;
                case '\n':
                    switch (select) {
                        case 0: easy(); difficulty = EGameDifficulty::EASY; break;
                        case 1: medium(); difficulty = EGameDifficulty::MEDIUM; break;
                        case 2: hard(); difficulty = EGameDifficulty::HARD; break;
                        case 3: return;
                    }
                    break;
            }
        }
    }
}

void Screen::aboutButton() {
    clear();
    printw("Tic-tac-toe, noughts and crosses, or Xs and Os is a paper-and-pencil game for two players who take turns marking the spaces in a three-by-three grid with X or O.\n");
    printw("The player who succeeds in placing three of their marks in a horizontal, vertical, or diagonal row is the winner. It is a solved game, with a forced draw assuming best play from both players.\n\n");
    printw("Press any key to continue...");
    getch();
    clear();
}

void Screen::easy() {
    clear();
    echo();
    while (true) {
        printw("Enter the board size (e.g., 3 for a 3x3 board): ");
        _boardSize = Game::getIntegerInput("Enter the board size: ");
        if (_boardSize < 3) {
            attron(COLOR_PAIR(4));
            printw("You have entered the wrong size! Please enter again.\n");
            attroff(COLOR_PAIR(4));
        } else {
            clear();
            break;
        }
    }
}

void Screen::medium() {
    clear();
    echo();
    while (true) {
        printw("Enter the board size (e.g., 3 for a 3x3 board): ");
        _boardSize = Game::getIntegerInput("Enter the board size: ");
        if (_boardSize < 3) {
            attron(COLOR_PAIR(4));
            printw("You have entered the wrong size! Please enter again.\n");
            attroff(COLOR_PAIR(4));
        } else {
            clear();
            break;
        }
    }
    while (true) {
        printw("Enter the time for each step (e.g., 3 for a 3 seconds): ");
        _time = Game::getIntegerInput("Enter the time: ");
        if (_time < 3) {
            attron(COLOR_PAIR(4));
            printw("You have entered the small time! Please enter again.\n");
            attroff(COLOR_PAIR(4));
        }
        else {
            clear();
            break;
        }
    }
}

void Screen::hard() {
    clear();
    echo();
    while (true) {
        printw("Enter the board size (e.g., 3 for a 3x3 board): ");
        _boardSize = Game::getIntegerInput("Enter the board size: ");
        if (_boardSize < 3) {
            attron(COLOR_PAIR(4));
            printw("You have entered the wrong size! Please enter again.\n");
            attroff(COLOR_PAIR(4));
        } else {
            clear();
            break;
        }
    }
    while (true) {
        printw("Enter the time for each step (e.g., 3 for a 3 seconds): ");
        _time = Game::getIntegerInput("Enter the time: ");
        if (_time < 3) {
            attron(COLOR_PAIR(4));
            printw("You have entered the small time! Please enter again.\n");
            attroff(COLOR_PAIR(4));
        }
        else {
            clear();
            break;
        }
    }
    attron(COLOR_PAIR(4));
    printw("After each step, one box will be blocked at random!!!\n\n");
    attroff(COLOR_PAIR(4));
    printw("Press any key to continue...");
    getch();
    clear();
}

void Screen::showMenu() {
    const std::vector<std::string> menuOptions = {"Play", "Difficulty", "About", "Exit"};
    unsigned select = 0;
    while (true) {
        clear();
        refresh();
        noecho();
        curs_set(0);
        for (std::size_t i = 0; i < menuOptions.size(); ++i) {
            if (i == select) {
                attron(COLOR_PAIR(1));
                mvprintw(10 + i, 45, "%s", menuOptions[i].c_str());
                attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                mvprintw(10 + i, 45, "%s", menuOptions[i].c_str());
                attroff(COLOR_PAIR(2));
            }
        }
        int ch = getch();
        switch (ch) {
            case KEY_UP:
                select = (select == 0) ? menuOptions.size() - 1 : select - 1;
                break;
            case KEY_DOWN:
                select = (select == menuOptions.size() - 1) ? 0 : select + 1;
                break;
            case '\n':
                switch (select) {
                    case 0: playButton(); break;
                    case 1: difficultyButton(); break;
                    case 2: aboutButton(); break;
                    case 3: return;
                }
                break;
        }
    }
}

void Screen::cleanupNcurses() {
    endwin();
}
