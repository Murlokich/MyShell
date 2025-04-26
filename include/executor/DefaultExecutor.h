/** \file DefaultExecutor.h
 *  \brief This file declares DefaultExecutor class for shell to execute commands, implements IExecutor interface
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#ifndef DEFAULT_EXECUTOR_H
#define DEFAULT_EXECUTOR_H

#include "IExecutor.h"

#include <string>

class DefaultExecutor: public IExecutor {
public:
    int execute(const std::string &command) final;
    DefaultExecutor();
};

#endif // DEFAULT_EXECUTOR_H