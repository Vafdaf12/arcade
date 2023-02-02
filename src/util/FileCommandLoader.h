#pragma once

#include <functional>
#include <stdint.h>
#include <string>
#include <vector>

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

    Command() = default;
    Command(const std::string& command,
        const ParseFunc& func,
        CommandType type = CommandType::SingleLine)
        : type(type), parseFunc(func), command(command) {}
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
    std::vector<Command>::const_iterator findCommand(
        const std::string& line, size_t& paramPos) const;
    std::vector<Command> m_commands;
};
