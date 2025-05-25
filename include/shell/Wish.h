/** \file Wish.h
 *  \brief This file declares class Wish that implements IShell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef WISH_H
#define WISH_H

#include "../executor/IExecutor.h"
#include "../parser/IParser.h"
#include "../reader/IReader.h"
#include "IShell.h"

#include <memory>


class Wish: public IShell{
public:
    int run() final;
    static void printError();
    explicit Wish(int argc, const char * argv[]);

private:
    enum class Mode;
    std::unique_ptr<IReader> reader_;
    std::unique_ptr<IParser> parser_;
    std::unique_ptr<IExecutor> executor_;
};

#endif // WISH_H