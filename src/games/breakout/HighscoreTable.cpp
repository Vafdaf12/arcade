#include "HighscoreTable.h"

#include <algorithm>
#include <exception>
#include <fstream>
#include <iostream>
#include <string>

void HighscoreTable::loadFromFile(const std::string& path) {
    std::cout << "HighscoreTable::loadFromFile(): Opening file... " << path
              << std::endl;

    // Open the file
    std::ifstream file;
    file.open(path);
    if (!file.is_open()) {
        std::cout << "HighscoreTable::loadFromFile(): could not open file: "
                  << path << std::endl;
        return;
    }

    std::string line = "";
    while (!file.eof()) {
        std::getline(file, line);
        if (line.empty()) continue;

        size_t readPos = line.find_first_of(" ");

        ScoreEntry entry;
        entry.score = std::stoi(line.substr(0, readPos));
        entry.name = line.substr(readPos + 1);

        m_scores.push_back(entry);
    }
    std::sort(m_scores.begin(), m_scores.end(), scoreComp);
}
void HighscoreTable::saveToFile(const std::string& path) {
    std::cout << "HighscoreTable::saveToFile(): Opening file... " << path
              << std::endl;

    // Open the file
    std::ofstream file;
    file.open(path, std::ofstream::out | std::ofstream::trunc);
    if (!file.is_open())
        throw std::runtime_error("could not open file: " + path);

    for (const auto& score : m_scores) {
        file << score.score << " " << score.name << "\n";
    }
}

void HighscoreTable::addScore(const std::string& name, uint32_t score) {
    ScoreEntry entry;
    entry.score = score;
    entry.name = name;

    auto it =
        std::lower_bound(m_scores.begin(), m_scores.end(), entry, scoreComp);

    m_scores.insert(it, entry);
    if (m_scores.size() > SCORE_COUNT) m_scores.pop_back();
    ;
}
bool HighscoreTable::scoreComp(const ScoreEntry& a, const ScoreEntry& b) {
    return a.score > b.score;
}
