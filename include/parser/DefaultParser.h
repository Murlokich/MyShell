/** \file DefaultParser.h
 *  \brief This file declares DefaultParser class to provide default parser for shell, implements IParser
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef DEFAULT_PARSER_H
#define DEFAULT_PARSER_H

#include "IParser.h"

class DefaultParser: public IParser {
public:
    std::string parseCommands(std::string line) final;
    DefaultParser();
};

#endif // DEFAULT_PARSER_H