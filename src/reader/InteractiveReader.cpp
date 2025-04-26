/** \file InteractiveReader.cpp
 *  \brief This file defines methods of InteractiveReader class for shells interactive mode
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/reader/InteractiveReader.h"

#include <iostream>

const std::string EXIT_COMMAND = "exit";

std::string InteractiveReader::readLine() {
    std::string line;
    std::getline(std::cin, line);
    if (line == EXIT_COMMAND) {
        finished = true;
    }
    return line;
}

bool InteractiveReader::isFinished() {
    return finished;
}

InteractiveReader::InteractiveReader(){}