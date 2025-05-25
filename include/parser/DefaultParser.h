/** \file DefaultParser.h
 *  \brief Declares DefaultParser, which parses input lines into Command entities.
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef DEFAULT_PARSER_H
#define DEFAULT_PARSER_H

#include "../entities/Command.h"
#include "IParser.h"

/** \class DefaultParser
 *  \brief Parses a raw input line into one or more Command objects.
 *
 *  DefaultParser implements IParser to tokenize an input string,
 *  identify command names, arguments, separators (;) or (&),
 *  and optional redirection targets, producing a vector of Command instances.
*/
class DefaultParser: public IParser {
public:
    /** \brief Parse an input line into Command objects.
     *  \param line The raw input string containing one or more commands.
     *  \return A pair where the first element is true if parsing was successful, and the second element is the vector of parsed Command instances.
    */
    [[nodiscard]] std::pair<bool, std::vector<Command>> parseCommands(const std::string& line) const final;

private:
    static const std::unordered_map<std::string, Command::Separator> strToSeparator_;

    /** \brief Split the input line into separate command strings by separators.
     *  \param line The raw input string containing one or more commands.
     *  \return A vector of substrings, each representing an individual command segment.
    */
    [[nodiscard]] std::vector<std::string> splitLineBySeparators(const std::string& line) const;
    
    /** \brief Split a command segment by the redirection symbol.
     *  \param command_line The raw command string potentially containing a '>' redirection.
     *  \return A vector of substrings, where the first element is the command portion and optionally '>' element and file portion
    */
    [[nodiscard]] std::vector<std::string> splitCommandLineByRedirectionSymbol(const std::string& command_line) const;

    /** \brief Split each token segment by space characters.
     *  \param redirection_tokens A vector of strings to be further split by spaces.
     *  \return A vector of individual tokens resulting from splitting each input string by whitespace.
    */
    [[nodiscard]] std::vector<std::string> splitTokensBySpaces(const std::vector<std::string>& redirection_tokens) const;

    /** \brief Split a string by any specified symbols using a regex-based approach.
     *  \param line The input string to be split.
     *  \param splitting_symbols A string containing the symbols to split on (interpreted as a regex character class).
     *  \param keep_symbols If true, include the splitting symbols in the resulting vector; otherwise, omit them.
     *  \return A vector of substrings produced by splitting the input string on the given symbols.
    */
    [[nodiscard]] std::vector<std::string> splitBySymbols(const std::string& line, const std::string& splitting_symbols, bool keep_symbols=true) const;
    
    /** \brief Validate tokens according to redirection rules.
     *  \param tokens A vector of token strings to check for redirection syntax.
     *  \return True if redirection tokens are valid (proper ‘>’ placement and target); false otherwise.
    */
    [[nodiscard]] bool validateTokensByRedirectionRules(const std::vector<std::string>& tokens) const;

    /** \brief Determine if a token represents a command separator.
     *  \param token The string token to evaluate.
     *  \return An optional containing the corresponding Command::Separator if `token` is ";" or "&"; std::nullopt otherwise.
    */
    [[nodiscard]] std::optional<Command::Separator> getSeparatorFromString(const std::string& token) const; 
};

#endif // DEFAULT_PARSER_H