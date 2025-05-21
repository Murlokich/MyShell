/** \file DefaultExecutor.cpp
 *  \brief This file defines methods of DefaultExecutor class for shell to execute commands
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/executor/DefaultExecutor.h"

#include <iostream>

int DefaultExecutor::execute(const std::vector<Command>& commands) {
    for (auto command: commands) {
        std::cout << "Command: " << command.command_ << std::endl;
        for (auto arg: command.args_) {
            std::cout << "Arg: " << arg << std::endl;
        }
        std::cout << "Sep: " << static_cast<char>(command.separator_) << std::endl << std::endl;
    }
    return 0;
};