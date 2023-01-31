#include "FileCommandLoader.h"

#include "graphics/Color.h"
#include "util/Vector2.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

void FileCommandLoader::addCommand(const Command& command) {
    m_commands.push_back(command);
}

void FileCommandLoader::loadFile(const std::string& filePath) {
    std::cout << "Loading file... " << filePath << std::endl;
    // Open the file
    std::ifstream file;
    file.open(filePath);
    if (!file.is_open())
        throw std::runtime_error("could not open file: " + filePath);

    std::string line = "";
    while (!file.eof()) {
        // Get the current line
        std::getline(file, line);

        // Parse the command it refers to
        size_t readPos;
        auto command = findCommand(line, readPos);
        if (command == m_commands.end()) continue;

        switch (command->type) {
        case CommandType::SingleLine: {
            ParseParams params;
            params.line = line;
            params.readPos = readPos;
            params.lineNum = 0;

            command->parseFunc(params);
            break;
        }

        case CommandType::Multiline: {
            int n = std::stoi(line.substr(readPos));
            int curLine = 0;
            while (curLine < n) {
                std::getline(file, line);
                if (line.empty()) continue;

                ParseParams params;
                params.line = line;
                params.readPos = 0;
                params.lineNum = curLine;

                command->parseFunc(params);
                curLine++;
            }

            break;
        }
        }
    }
}

std::vector<Command>::const_iterator FileCommandLoader::findCommand(
    const std::string& line, size_t& paramPos) const {

    size_t startPos = line.find(":");
    if (startPos == std::string::npos) return m_commands.end();
    startPos++;

    size_t endPos = line.find_first_of(" ", startPos);
    if (endPos == std::string::npos) endPos = line.length();

    paramPos = endPos + 1;

    std::string commandString = line.substr(startPos, endPos - startPos);
    return std::find_if(m_commands.begin(),
        m_commands.end(),
        [&commandString](const Command& command) {
            return command.command == commandString;
        });
}

Color FileCommandLoader::parseColor(const ParseParams& params) {
    Color col;

    uint32_t startPos = params.readPos;
    uint32_t endPos = params.line.find_first_of(" ", startPos);
    col.red = std::stoi(params.line.substr(startPos, endPos - startPos));

    startPos = endPos + 1;
    endPos = params.line.find_first_of(" ", startPos);
    col.green = std::stoi(params.line.substr(startPos, endPos - startPos));

    startPos = endPos + 1;
    endPos = params.line.find_first_of(" ", startPos);
    col.blue = std::stoi(params.line.substr(startPos, endPos - startPos));

    startPos = endPos + 1;
    endPos = params.line.find_first_of(" ", startPos);
    col.alpha = std::stoi(params.line.substr(startPos, endPos - startPos));

    return col;
}
Vector2 FileCommandLoader::parseVector2(const ParseParams& params) {
    Vector2 vec;

    uint32_t startPos = params.readPos;
    uint32_t endPos = params.line.find_first_of(" ", startPos);
    vec.x = std::stof(params.line.substr(startPos, endPos - startPos));

    startPos = endPos + 1;
    endPos = params.line.find_first_of(" ", startPos + 1);
    vec.y = std::stof(params.line.substr(startPos, endPos - startPos));

    return vec;
}
int FileCommandLoader::parseInt(const ParseParams& params) {
    return std::stoi(params.line.substr(params.readPos));
}
std::string FileCommandLoader::parseString(const ParseParams& params) {
    return params.line.substr(params.readPos);
}
char FileCommandLoader::parseChar(const ParseParams& params) {
    return params.line[0];
}
