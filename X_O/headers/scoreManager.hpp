#ifndef SCOREMANAGER_HPP
#define SCOREMANAGE_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <ncurses.h>
#include <map>

class ScoreManager {
public:
    ScoreManager();
    void createFile(const std::string& fileName, const std::string& playerName, int victories);

    ~ScoreManager();

private:
    int _score;
    std::map<std::string, int> _playerScores;
};

#endif // SCOREMANAGER_HPP