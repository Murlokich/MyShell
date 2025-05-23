/** \file InteractiveReader.cpp
 *  \brief This file defines methods of InteractiveReader class for shells interactive mode
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/reader/InteractiveReader.h"

#include <iostream>

std::optional<std::string> InteractiveReader::readLine() {
    std::string line;
    std::cout << "wish> " << std::flush;
    if (!std::getline(std::cin, line)) {
        return std::nullopt;
    };
    return line;
}