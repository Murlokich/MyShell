/** \file DefaultParser.h
 *  \brief This file declares DefaultParser class to provide default parser for shell, implements IParser
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef DEFAULT_PARSER_H
#define DEFAULT_PARSER_H

#include "../entities/Command.h"
#include "IParser.h"

class DefaultParser: public IParser {
public:
    [[nodiscard]] std::pair<bool, std::vector<Command>> parseCommands(const std::string& line) const final;

private:
    static const std::unordered_map<std::string, Command::Separator> strToSeparator_;

    [[nodiscard]] std::vector<std::string> splitLineBySeparators(const std::string& line) const;
    [[nodiscard]] std::vector<std::string> splitCommandLineByRedirectionSymbol(const std::string& command_line) const;
    [[nodiscard]] std::vector<std::string> splitTokensBySpaces(const std::vector<std::string>& redirection_tokens) const;
    [[nodiscard]] std::vector<std::string> splitBySymbols(const std::string& line, const std::string& splitting_symbols, bool keep_symbols=true) const;
    
    [[nodiscard]] bool validateTokensByRedirectionRules(const std::vector<std::string>& tokens) const;
    [[nodiscard]] std::optional<Command::Separator> getSeparatorFromString(const std::string& token) const; 
};

#endif // DEFAULT_PARSER_H