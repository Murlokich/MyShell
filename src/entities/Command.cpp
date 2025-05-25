/** \file Entities.cpp
 *  \brief This file defines methods of Command class
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 19/05/2025
*/

#include "../../include/entities/Command.h"

const std::string& Command::getCommand() const {
    // static is required to have long lifetime to avoid dangling reference
    static const std::string no_command{};
    if (args_.empty()) {
        return no_command;
    }
    // 0 argument is assigned to command name. This convention is used for execv and is normal for C args
    return args_[0];
}


const std::vector<std::string>& Command::getArgs() const {
    return args_;
}


const std::optional<std::string> Command::getRedirectionFile() const {
    return redirection_file_;
}


Command::Separator Command::getSeparator() const {
    return separator_;
}


void Command::setSeparator(Separator separator) {
    separator_ = separator;
}


Command::Command(const std::vector<std::string>& args, 
    std::optional<std::string> redirection_file): args_(args), redirection_file_(redirection_file), separator_(Separator::sequential) {}


Command::Command(){}