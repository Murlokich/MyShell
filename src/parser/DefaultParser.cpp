/** \file DefaultParser.cpp
 *  \brief This file defines DefaultParser class to provide default parser for shell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/parser/DefaultParser.h"
#include <sstream>
#include <iterator>


std::vector<std::string> DefaultParser::splitTokens(std::string line) {
    std::istringstream iss(line);
    return std::vector<std::string> {std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>{}};
}

std::optional<Command::Separator> DefaultParser::parseSeparator(const std::string& token) {
    if (auto it = strToSeparator_.find(token); it != strToSeparator_.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::vector<Command> DefaultParser::parseCommands(std::string line) {
    auto words = splitTokens(line);
    std::vector<Command> commands{};
    std::vector<std::string> args{};
    for (const auto& word: words) {
        if (const auto& sep = parseSeparator(word)) {
            commands.emplace_back(args, *sep);
            args.clear();
            continue;
        }
        args.push_back(word);
    }
    if (!args.empty()) {
        commands.emplace_back(args);
    }
    return commands;
}