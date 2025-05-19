/** \file FileReader.cpp
 *  \brief This file defines methods for FileReader class for shells file mode
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/reader/FileReader.h"

std::optional<std::string> FileReader::readLine() {
    std::string line;
    if (!std::getline(file_, line)) {
        return std::nullopt;
    }
    if (line == EXIT_COMMAND) {
        return std::nullopt;
    }
    return line;
}

FileReader::FileReader(const std::string &filename): file_(filename) {
    if (!file_.is_open()) {
        throw std::runtime_error("FileReader: failed to open \"" + filename + "\"");
    }
}