/** \file Wish.cpp
 *  \brief This file defines class methods of Wish
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/executor/DefaultExecutor.h"
#include "../../include/parser/DefaultParser.h"
#include "../../include/reader/FileReader.h"
#include "../../include/reader/InteractiveReader.h"
#include "../../include/shell/Wish.h"

#include <iostream>
#include <memory>

enum class Wish::Mode {
    INTERACTIVE = 1,
    FILE,
};


int Wish::run() {
    while (auto line = reader_->readLine()) {
        auto [validation_error, parsedLine] = parser_->parseCommands(*line);
        if (validation_error != 0) {
            printError();
            continue;
        }
        auto success = executor_->executeCommands(parsedLine);
        if (!success) {
            printError();
        }
    }
    return 0;
}


void Wish::printError() {
    std::cerr << "An error has occurred" << std::endl;
}


Wish::Wish(int argc, const char * argv[]):  parser_(std::make_unique<DefaultParser>()), executor_(std::make_unique<DefaultExecutor>()) {
    if (argc == static_cast<int>(Wish::Mode::FILE)) {
        reader_ = std::make_unique<FileReader>(argv[1]);
    } else if (argc == static_cast<int>(Wish::Mode::INTERACTIVE)) {
        reader_ = std::make_unique<InteractiveReader>();
    } else {
        throw std::runtime_error("More than 1 argument execution is not supported");
    }
};