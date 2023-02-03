#pragma once

#include <stdint.h>
#include <string>
#include <vector>

struct ScoreEntry {
    std::string name = "";
    int score;
};

class HighscoreTable {
public:
    HighscoreTable() = default;

    void loadFromFile(const std::string& path);
    void saveToFile(const std::string& path);

    void addScore(const std::string& name, uint32_t score);

    inline const std::vector<ScoreEntry>& getScores() const { return m_scores; }

    static constexpr size_t SCORE_COUNT = 10;

private:
    static bool scoreComp(const ScoreEntry& a, const ScoreEntry& b);
    std::vector<ScoreEntry> m_scores;
};
