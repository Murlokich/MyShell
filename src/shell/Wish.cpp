/** \file Wish.cpp
 *  \brief This file defines class methods of Wish
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/shell/Wish.h"
#include "../../include/executor/DefaultExecutor.h"
#include "../../include/parser/DefaultParser.h"
#include "../../include/reader/InteractiveReader.h"

#include <memory>

Wish::Wish(): 
    reader_(std::make_unique<InteractiveReader>()), 
    parser_(std::make_unique<DefaultParser>()), 
    executor_(std::make_unique<DefaultExecutor>()) {};

int Wish::run() {
    while (!reader_->isFinished()) {
        auto line = reader_->readLine();
        if (reader_->isFinished()) {
            return 0;
        }
        auto parsedLine = parser_->parseCommands(line);
        auto res = executor_->execute(parsedLine);
    };
    return 0;
};