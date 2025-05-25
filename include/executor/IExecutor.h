/** \file IExecutor.h
 *  \brief This file declares IExecutor interface for shell to execute commands (processes management)
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#ifndef IEXECUTOR_H
#define IEXECUTOR_H

#include "../entities/Command.h"

#include <optional>
#include <string>


/** \class IExecutor
 *  \brief Interface for executing parsed shell commands.
 *
 *  IExecutor defines the contract for running a sequence of Command objects,
 *  whether built-in or external, handling process management and I/O redirection.
*/
class IExecutor {
public:
    /** \brief Execute a sequence of commands.
     *  \param commands A vector of Command objects to execute.
     *  \return True if all commands executed successfully; false if any command failed.
    */
    virtual bool executeCommands(const std::vector<Command>& commands) = 0;

    virtual ~IExecutor() = default;
};


#endif // IEXECUTOR_H