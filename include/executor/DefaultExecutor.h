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
#include <optional>

class DefaultExecutor: public IExecutor {
    const std::vector<std::string> paths = {"/bin"};

    enum class BuiltInCommandType {
        exit,
        cd,
        path,
    };

    inline static const std::unordered_map<std::string, BuiltInCommandType> strToBuiltInCommand_ {
        {"exit", BuiltInCommandType::exit},
        {"cd", BuiltInCommandType::cd},
        {"path", BuiltInCommandType::path},
    };

    void builtInExit() const;
    std::optional<BuiltInCommandType> getBuiltInCommandType(const std::string& command) const;
    int executeBuiltInCommand(BuiltInCommandType commandType, const Command& command) const;
    bool isExecutableFile(const std::string& command_path) const;
    int executeCommand(const std::string& command_path, const Command& command) const;
    char *const * buildCArrArgs(std::vector<char*>& cStrVec, const Command& command) const;
public:
    int executeCommands(const std::vector<Command>& commands) const final;
};

#endif // DEFAULT_EXECUTOR_H