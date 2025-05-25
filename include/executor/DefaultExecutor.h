/** \file DefaultExecutor.h
 *  \brief This file declares DefaultExecutor class for shell to execute commands, implements IExecutor interface
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#ifndef DEFAULT_EXECUTOR_H
#define DEFAULT_EXECUTOR_H


#include "IExecutor.h"

#include <optional>
#include <string>
#include <vector>

class DefaultExecutor: public IExecutor {
public:
    bool executeCommands(const std::vector<Command>& commands) final;

private:
    enum class BuiltInCommandType;
    std::vector<std::string> paths_ = {"/bin"};
    static const std::unordered_map<std::string, BuiltInCommandType> strToBuiltInCommand_;

    int executePathCommand(const std::string& command_path, const Command& command) const;
    void waitChildren(std::vector<pid_t>& pids) const;
    bool isExecutableFile(const std::string& command_path) const;
    char *const * convertArgsToCStyle(std::vector<char*>& cStrVec, const Command& command) const;

    bool executeBuiltInCommand(const BuiltInCommandType& commandType, const Command& command);
    void builtInExit() const;
    void builtInPath(const std::vector<std::string>& args);
    bool builtInCD(const std::string& dir) const;
    std::optional<BuiltInCommandType> getBuiltInCommandType(const std::string& command) const;
};

#endif // DEFAULT_EXECUTOR_H