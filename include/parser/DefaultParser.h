/** \file DefaultParser.h
 *  \brief This file declares DefaultParser class to provide default parser for shell, implements IParser
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef DEFAULT_PARSER_H
#define DEFAULT_PARSER_H

#include "IParser.h"
#include "../entities/Command.h"

class DefaultParser: public IParser {
    [[nodiscard]] std::vector<std::string> splitBySymbols(const std::string& line, const std::string& splitting_symbols, bool keep_symbols=true) const; 
    [[nodiscard]] std::vector<std::string> splitCommands(const std::string& line) const;
    [[nodiscard]] std::vector<std::string> parseRedirectionCommand(const std::string& command) const;
    [[nodiscard]] std::vector<std::string> splitTokens(const std::vector<std::string>& redirection_command) const;
    [[nodiscard]] std::optional<Command::Separator> parseSeparator(const std::string& token) const;
    [[nodiscard]] int validateRedirectionRules(const std::vector<std::string>& redirection_tokens) const;

    inline static const std::unordered_map<std::string, Command::Separator> strToSeparator_ {
        {"&", Command::Separator::parallel},
        {";", Command::Separator::sequential},
    };
public:
    [[nodiscard]] std::pair<int, std::vector<Command>> parseCommands(const std::string& line) const final;
};

#endif // DEFAULT_PARSER_H