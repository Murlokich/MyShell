/** \file Entities.h
 *  \brief This file declares entities structs that are used by parser/executor
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 19/05/2025
*/

#ifndef ENTITIES_H
#define ENTITIES_H

#include <string>
#include <vector>
#include <unordered_map>
#include <optional>


class Command {
public:
    enum class Separator {
        parallel = '&',
        redirection = '>',
        sequential = ';',
    };

    std::string getCommand();
    std::vector<std::string> getArgs();
    Separator getSeparator();
    
    std::string command_;
    std::vector<std::string> args_;
    Separator separator_ = Separator::sequential;
};


#endif // ENTITIES_H