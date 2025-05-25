/** \file DefaultExecutor.cpp
 *  \brief This file defines methods of DefaultExecutor class for shell to execute commands
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/executor/DefaultExecutor.h"

#include <iostream>
#include <filesystem>

#include <cassert>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void DefaultExecutor::builtInExit() const {
    exit(0);
    assert(false);
}

void DefaultExecutor::builtInPath(const std::vector<std::string>& args) {
    paths_ = args;
    // first arg is the command name.
    // It's okay as we already copy the vector for O(n)
    paths_.erase(paths_.begin());
}

int DefaultExecutor::builtInCD(const std::string& dir) const {
    return chdir(dir.c_str());
}

int DefaultExecutor::executeBuiltInCommand(BuiltInCommandType commandType, const Command& command) {
    switch (commandType) {
        case BuiltInCommandType::exit:
            if (command.getArgs().size() != 1 + 0) {
                return -1;
            }
            assert(command.getArgs().size() == 1 + 0);
            assert(command.getCommand() == "exit");
            builtInExit();
            break;
        case BuiltInCommandType::cd:
            if (command.getArgs().size() != 1 + 1) {
                return -1;
            }
            assert(command.getArgs().size() == 1 + 1);
            assert(command.getCommand() == "cd");
            if (auto res = builtInCD(command.getArgs()[1]); res != 0) {
                return res;
            }
            break;
        case BuiltInCommandType::path:
            assert(command.getCommand() == "path");
            builtInPath(command.getArgs());
            break;
        default:
            // Not expected to get here. Cases must check all possible commands
            assert(false);
    }
    return 0;
}

std::optional<DefaultExecutor::BuiltInCommandType> DefaultExecutor::getBuiltInCommandType(const std::string& command) const {
    if (auto it = strToBuiltInCommand_ .find(command); it != strToBuiltInCommand_.end()) {
        return it->second;
    }
    return std::nullopt;
}

bool DefaultExecutor::isExecutableFile(const std::string& command_path) const {
    return access(command_path.c_str(), X_OK) == 0
       && std::filesystem::is_regular_file(command_path);
}

int DefaultExecutor::executeCommands(const std::vector<Command>& commands) {
    for (const auto& command: commands) {
        if (auto type = getBuiltInCommandType(command.getCommand()); type) {
            auto res = executeBuiltInCommand(*type, command);
            if (res != 0) {
                return res;
            }
            continue;
        }
        bool haveExecuted = false;
        for (const auto& path: paths_) {
            auto command_path = path + "/" + command.getCommand();
            if (isExecutableFile(command_path)) {
                auto res = executeCommand(command_path, command);
                if (res != 0) {
                    return res;
                }
                haveExecuted = true;
                break;
            }
        }
        if (!haveExecuted) {
            return -1;
        }
    }
    return 0;
};

int DefaultExecutor::executeCommand(const std::string& command_path,const Command& command) const {
    pid_t pid = fork();
    if (pid < 0) {
        return -1;
    }
    if (pid == 0) {
        // Must initialize next to execv in order to keep lifetime of the returning ptr based on this vector.
        // Otherwise would have had to initialize array on heap. Check buildCArrArgs func
        std::vector<char*> cArgs(command.getArgs().size() + 1);
        if (auto redirection_file = command.getRedirectionFile(); redirection_file) {
            // Got this code from: https://stackoverflow.com/a/2605313
            int fd = open(redirection_file->c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            dup2(fd, 1);   // make stdout go to file
            dup2(fd, 2);   // make stderr go to file
            close(fd);     // fd no longer needed - the dup'ed handles are sufficient
        }
        execv(command_path.c_str(), buildCArrArgs(cArgs, command));
        return -1;
    } else {
        int status;
        auto wait_pid = waitpid(pid, &status, 0);
        if (wait_pid == -1) {
            return -1;
        }
        assert(wait_pid == pid);
    }
    return 0;
}

char *const * DefaultExecutor::buildCArrArgs(std::vector<char*>& cStrVec, const Command& command) const {
    const auto& cmdArgs = command.getArgs();
    // execv signature was implemented with using no const char*. const_cast is required for compatibility
    // https://stackoverflow.com/a/190208
    for (int i = 0; i < cmdArgs.size(); i++) {
        cStrVec[i] = const_cast<char*>(cmdArgs[i].c_str());
    }
    // data doesn't finish array with NULL element, so must assign it manually
    cStrVec[cStrVec.size() - 1] = nullptr;
    // https://en.cppreference.com/w/cpp/container/vector/data 
    return cStrVec.data();
}