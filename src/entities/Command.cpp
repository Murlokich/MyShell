/** \file Entities.cpp
 *  \brief This file defines methods entities structs that are used by parser/executor
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 19/05/2025
*/

#include "../../include/entities/Command.h"

// Command::Command(const std::string& command, const std::vector<std::string>& args, Separator separator):
//     command_(command), args_(args), separator_(separator) {}

std::string Command::getCommand() {
    return command_;
}

std::vector<std::string> Command::getArgs() {
    return args_;
}

Command::Separator Command::getSeparator() {
    return separator_;
}