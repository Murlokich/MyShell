/** \file Wish.h
 *  \brief This file declares class Wish that implements IShell
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef WISH_H
#define WISH_H

#include "IShell.h"
#include "../reader/IReader.h"
#include "../parser/IParser.h"
#include "../executor/IExecutor.h"

#include <memory>

class Wish: public IShell{
    std::unique_ptr<IReader> reader_;
    std::unique_ptr<IParser> parser_;
    std::unique_ptr<IExecutor> executor_;
public:
    Wish();
    int run() final;
};

#endif // WISH_H