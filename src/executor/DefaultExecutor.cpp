/** \file DefaultExecutor.cpp
 *  \brief This file defines methods of DefaultExecutor class for shell to execute commands
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/executor/DefaultExecutor.h"

#include <iostream>

int DefaultExecutor::execute(const std::string &command) {
    std::cout << command << std::endl;
    return 0;
};

DefaultExecutor::DefaultExecutor(){};