#pragma once

#include <stdint.h>

class Timer {
public:
    Timer() : Timer(0) {}
    Timer(uint32_t ms) : m_duration(ms), m_elapsed(0) {}

    inline void setDuration(uint32_t duration) { m_duration = duration; }
    inline uint32_t getDuration() { return m_duration; }

    inline void reset() { m_elapsed = 0; }
    inline bool elapsed() const { return m_elapsed > m_duration; }
    inline void update(uint32_t dt) { m_elapsed += dt; }

private:
    uint32_t m_duration;
    uint32_t m_elapsed;
};
