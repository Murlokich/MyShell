/** \file Wish.cpp
 *  \brief This file defines class methods of Wish
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/shell/Wish.h"
#include "../../include/executor/DefaultExecutor.h"
#include "../../include/parser/DefaultParser.h"
#include "../../include/reader/FileReader.h"
#include "../../include/reader/InteractiveReader.h"

#include <memory>

Wish::Wish(int argc, const char * argv[]):  parser_(std::make_unique<DefaultParser>()), executor_(std::make_unique<DefaultExecutor>()) {
    if (argc == static_cast<int>(Wish::Mode::FILE)) {
        reader_ = std::make_unique<FileReader>(argv[1]);
    } else if (argc == static_cast<int>(Wish::Mode::INTERACTIVE)) {
        reader_ = std::make_unique<InteractiveReader>();
    } else {
        throw std::runtime_error("More than 1 argument execution is not supported");
    }
};

int Wish::run() {
    while (auto line = reader_->readLine()) {
        auto parsedLine = parser_->parseCommands(*line);
        auto res = executor_->execute(parsedLine);
    }
    return 0;
}