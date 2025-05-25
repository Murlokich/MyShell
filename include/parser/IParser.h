/** \file IParser.h
 *  \brief This file declares IParser interface for shell to parse commands
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef IPARSER_H
#define IPARSER_H

#include "../entities/Command.h"

#include <string>

/** \class IParser
 *  \brief Interface for command parsers used by the shell.
 *
 *  IParser defines the method to convert a raw input line
 *  into a sequence of Command objects along with a success flag.
*/
class IParser {
public:
    /** \brief Parse a raw input line into commands.
     *  \param line The raw input string containing one or more commands.
     *  \return A pair where the first element is true if parsing succeeded,
     *          and the second element is the vector of parsed Command instances.
    */
    virtual std::pair<bool, std::vector<Command>> parseCommands(const std::string& line) const = 0;

    virtual ~IParser() = default;
};

#endif // IPARSER_H