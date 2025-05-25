/** \file DefaultParser.cpp
 *  \brief This file defines DefaultParser class to provide default parser for shell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/parser/DefaultParser.h"
#include <sstream>
#include <iterator>
#include <regex>
#include <algorithm>
#include <cassert>
#include <iostream>

std::vector<std::string> DefaultParser::splitBySymbols(const std::string& line, const std::string& splitting_symbols, bool keep_symbols) const {
    std::vector<std::string> tokens{};
    std::regex split_commands_regex(splitting_symbols);
    std::initializer_list<int> submatches = (keep_symbols) ? std::initializer_list<int>({-1, 0}) : std::initializer_list<int>({-1});
    std::sregex_token_iterator it(line.begin(), line.end(), split_commands_regex, submatches), end;
    for (;it != end; it++) {
        if (it->str().empty()) {
            continue;
        }
        tokens.push_back(it->str());
    }   
    return tokens;
}

std::vector<std::string> DefaultParser::splitTokens(const std::vector<std::string>& redirection_command) const{
    std::vector<std::string> tokens{};
    for (const auto& element: redirection_command) {
        auto sub_tokens = splitBySymbols(element, "\\s", false);
        tokens.reserve(tokens.size() + sub_tokens.size());
        tokens.insert(tokens.end(), sub_tokens.begin(), sub_tokens.end());
    }
    return tokens;
}

std::optional<Command::Separator> DefaultParser::parseSeparator(const std::string& token) const {
    if (auto it = strToSeparator_.find(token); it != strToSeparator_.end()) {
        return it->second;
    }
    return std::nullopt;
}

std::vector<std::string> DefaultParser::splitCommands(const std::string& line) const {
    return splitBySymbols(line, "[;&]");
}

std::vector<std::string> DefaultParser::parseRedirectionCommand(const std::string& command) const {
    return splitBySymbols(command, ">");
}

int DefaultParser::validateRedirectionRules(const std::vector<std::string>& tokens) const {
    auto cnt = std::count(tokens.begin(), tokens.end(), ">");
    if (cnt != 0 && cnt != 1) {
        return -1;
    }
    auto it = std::find(tokens.begin(), tokens.end(), ">");
    int first_index = (it == tokens.end() ? -1 : int(std::distance(tokens.begin(), it)));
    if (cnt == 1 && first_index != tokens.size() - 2) {
        return -1;
    }
    return 0;
}

std::pair<int, std::vector<Command>> DefaultParser::parseCommands(const std::string& line) const {
    auto str_commands = splitCommands(line);
    std::vector<Command> commands{};
    commands.reserve(commands.size());
    Command cur_command;
    for (const auto& command: str_commands) {
        if (auto separator = parseSeparator(command); separator) {
            cur_command.setSeparator(*separator);
            commands.push_back(cur_command);
            cur_command = Command();
            continue;
        }
        auto redirection_tokens = parseRedirectionCommand(command);
        auto has_redirection = redirection_tokens.size() == 3;
        auto tokens = splitTokens(redirection_tokens);
        if (auto res = validateRedirectionRules(tokens); res != 0) {
            return {res, commands};
        }
        std::optional<std::string> redirection_file = std::nullopt;
        if (has_redirection) {
            assert((tokens.size()) >= 3);
            redirection_file = tokens.back();
            // pop output file
            tokens.pop_back();
            // pop redirection symbol
            tokens.pop_back();
        }
        cur_command = Command(tokens, redirection_file);
    }
    if (cur_command.getCommand() != "") {
        commands.push_back(cur_command);
    }
    return {0, commands};
}