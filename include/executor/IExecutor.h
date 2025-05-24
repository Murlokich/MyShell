/** \file IExecutor.h
 *  \brief This file declares IExecutor interface for shell to execute commands (processes management)
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#ifndef IEXECUTOR_H
#define IEXECUTOR_H

#include <string>
#include <optional>
#include "../entities/Command.h"

class IExecutor {
public:
    virtual int executeCommands(const std::vector<Command>& commands) = 0;
    virtual ~IExecutor() = default;
};

#endif // IEXECUTOR_H