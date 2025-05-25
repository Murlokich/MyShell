/** \file DefaultParser.cpp
 *  \brief This file defines DefaultParser class to provide default parser for shell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/parser/DefaultParser.h"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <regex>
#include <sstream>


const std::unordered_map<std::string, Command::Separator> DefaultParser::strToSeparator_ {
    {"&", Command::Separator::parallel},
    {";", Command::Separator::sequential},
};


std::pair<bool, std::vector<Command>> DefaultParser::parseCommands(const std::string& line) const {
    constexpr int REDIRECTION_SPLIT_PARTS = 3;
    auto str_commands = splitLineBySeparators(line);
    std::vector<Command> commands{};
    commands.reserve(commands.size());
    Command cur_command;
    for (const auto& command: str_commands) {
        if (auto separator = getSeparatorFromString(command); separator) {
            cur_command.setSeparator(*separator);
            commands.push_back(cur_command);
            cur_command = Command();
            continue;
        }
        auto redirection_tokens = splitCommandLineByRedirectionSymbol(command);

        // Syntactically correct format for redirection:
        // {command line} > {output filename}
        //       1        2         3 
        // 3 tokens after split by '>'
        auto has_redirection = redirection_tokens.size() == REDIRECTION_SPLIT_PARTS;
        auto tokens = splitTokensBySpaces(redirection_tokens);
        if (auto valid = validateTokensByRedirectionRules(tokens); !valid) {
            return {false, commands};
        }
        std::optional<std::string> redirection_file = std::nullopt;
        if (has_redirection) {
            // After parsing {command line} there might be more than 1 token:
            // E.g. ls -l 
            //       1  2
            assert((tokens.size()) >= REDIRECTION_SPLIT_PARTS);
            redirection_file = tokens.back();
            // Pop output file
            tokens.pop_back();
            // Pop redirection symbol
            tokens.pop_back();
        }
        cur_command = Command(tokens, redirection_file);
    }
    if (!cur_command.getCommand().empty()) {
        commands.push_back(cur_command);
    }
    return {true, commands};
}


std::vector<std::string> DefaultParser::splitLineBySeparators(const std::string& line) const {
    return splitBySymbols(line, "[;&]");
}


std::vector<std::string> DefaultParser::splitCommandLineByRedirectionSymbol(const std::string& command_line) const {
    return splitBySymbols(command_line, ">");
}


std::vector<std::string> DefaultParser::splitTokensBySpaces(const std::vector<std::string>& redirection_tokens) const{
    std::vector<std::string> tokens{};
    for (const auto& element: redirection_tokens) {
        auto sub_tokens = splitBySymbols(element, "\\s", false);
        tokens.reserve(tokens.size() + sub_tokens.size());
        tokens.insert(tokens.end(), sub_tokens.begin(), sub_tokens.end());
    }
    return tokens;
}


std::vector<std::string> DefaultParser::splitBySymbols(const std::string& line, const std::string& splitting_symbols, bool keep_symbols) const {
    std::vector<std::string> tokens{};
    std::regex split_commands_regex(splitting_symbols);
    // -1 captures all tokens that are outside of the regex
    //  0 captures all tokens that are inside of the regex, but as a separte element
    //  For whitespaces - want to omit them, but for separators/redirection want to keep them
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


bool DefaultParser::validateTokensByRedirectionRules(const std::vector<std::string>& tokens) const {
    auto cnt = std::count(tokens.begin(), tokens.end(), ">");
    // Command line cannot have more than one redirection
    if (cnt > 1) {
        return false;
    }
    auto it = std::find(tokens.begin(), tokens.end(), ">");
    int first_index = (it == tokens.end() ? -1 : int(std::distance(tokens.begin(), it)));

    // If there is a redirection corresponding token must precede the last element
    // To keep structure: [> filename]
    if (cnt == 1 && first_index != tokens.size() - 2) {
        return false;
    }
    return true;
}


std::optional<Command::Separator> DefaultParser::getSeparatorFromString(const std::string& token) const {
    if (auto it = strToSeparator_.find(token); it != strToSeparator_.end()) {
        return it->second;
    }
    return std::nullopt;
}