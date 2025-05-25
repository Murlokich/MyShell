/** \file IParser.h
 *  \brief This file declares IParser interface for shell to parse commands
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef IPARSER_H
#define IPARSER_H

#include <string>
#include "../entities/Command.h"

class IParser {
public:
    virtual std::pair<int, std::vector<Command>> parseCommands(const std::string& line) const = 0;

    virtual ~IParser() = default;
};

#endif // IPARSER_H