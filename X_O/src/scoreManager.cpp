#include "scoreManager.hpp"

ScoreManager::ScoreManager() {
    _score = 0;
}

void ScoreManager::createFile(const std::string &fileName, const std::string &playerName, int victories) {
    std::map<std::string, int> scores;
    std::ifstream inputFile(fileName);
    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string name;
            std::string temp;
            int wins;

            if (iss >> temp >> name >> temp >> wins) {
                if (name.back() == ',') name.pop_back();
                scores[name] = wins;
            }
        }
        inputFile.close();
    }

    scores[playerName] += victories;

    std::ofstream outputFile(fileName, std::ios::trunc);
    if (outputFile.is_open()) {
        for (const auto& [name, wins] : scores) {
            _score = wins;
            outputFile << "Player: " << name << ", Wins: " << _score << "\n";
        }
        outputFile.close();
        
        attron(COLOR_PAIR(5));
        printw("Score saved successfully.\n");
        attroff(COLOR_PAIR(5));
    } else {
        attron(COLOR_PAIR(4));
        printw("Error: Could not open file for writing.\n");
        attroff(COLOR_PAIR(4));
    }
}

ScoreManager::~ScoreManager() {
    _score = 0;
}