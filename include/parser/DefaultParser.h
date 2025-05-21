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
    [[nodiscard]] std::vector<std::string> splitTokens(std::string line);
    [[nodiscard]] std::optional<Command::Separator> parseSeparator(const std::string& token);

    inline static const std::unordered_map<std::string, Command::Separator> strToSeparator_ {
        {"&", Command::Separator::parallel},
        {">", Command::Separator::redirection},
        {";", Command::Separator::sequential},
    };
public:
    [[nodiscard]] std::vector<Command> parseCommands(std::string line) final;
};

#endif // DEFAULT_PARSER_H