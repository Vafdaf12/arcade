#pragma once

#include <vector>

template<class T>
class Grid {
public:
    Grid();
    Grid(std::size_t width, std::size_t height);

    void set(const T& val, std::size_t x, std::size_t y); 
    const T& get(std::size_t x, std::size_t y) const;
    bool containsItem(std::size_t x, std::size_t y) const;

    inline std::size_t width() const { return m_width; }
    inline std::size_t height() const { return m_height; }

private:
    struct GridCell {
        T value;
        bool active = false;
    };

    std::size_t index(std::size_t x, std::size_t y) const;
    std::vector<GridCell> m_grid;

    std::size_t m_width, m_height;

};
