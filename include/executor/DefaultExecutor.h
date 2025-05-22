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
#include <vector>
#include <string>

class DefaultExecutor: public IExecutor {
    const std::vector<std::string> paths = {"/bin"};

    int executeCommand(const std::string& command_path, const std::vector<std::string>& args);
    char *const * strVecToCharArr(std::vector<char*>& cStrVec, const std::vector<std::string>& strVec);
public:
    int executeCommands(const std::vector<Command>& commands) final;
};

#endif // DEFAULT_EXECUTOR_H