#pragma once

#include <functional>
#include <string>
#include <vector>
#include <stdint.h>

class Color;
class Vector2;

enum class CommandType {
    SingleLine,
    Multiline,

};

struct ParseParams {
    std::string line;
    size_t readPos;
    uint32_t lineNum;
};
using ParseFunc = std::function<void(const ParseParams&)>;

struct Command {
    CommandType type = CommandType::SingleLine;
    std::string command = "";
    ParseFunc parseFunc = nullptr;
};

class FileCommandLoader {
public:
    void addCommand(const Command& command);
    void loadFile(const std::string& filePath);

    static Color parseColor(const ParseParams& params);
    static Vector2 parseVector2(const ParseParams& params);
    static int parseInt(const ParseParams& params);
    static std::string parseString(const ParseParams& params);
    static char parseChar(const ParseParams& params);

private:
    std::vector<Command>::const_iterator findCommand(const std::string& line, size_t& paramPos) const;
    std::vector<Command> m_commands;
};
