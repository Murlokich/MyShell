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

bool DefaultExecutor::isExecutableFile(const std::string& command_path) const {
    return access(command_path.c_str(), X_OK) == 0
        && std::filesystem::is_regular_file(command_path);
}

int DefaultExecutor::executeCommands(const std::vector<Command>& commands) const {
    for (const auto& command: commands) {
        for (const auto& path: paths) {
            auto command_path = path + "/" + command.getCommand();
            if (isExecutableFile(command_path)) {
                auto res = executeCommand(command_path, command);
                if (res == -1) {
                    std::cout << "Failed to run the command" << std::endl;
                }
                return 0;
            } else {
                std::cout << "Unknown command" << std::endl;
            }
        }
    }
    return -1;
};

int DefaultExecutor::executeCommand(const std::string& command_path,const Command& command) const {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "failed to create child process (fork)";
        return -1;
    }
    if (pid == 0) {
        // Must initialize next to execv in order to keep lifetime of the returning ptr based on this vector.
        // Otherwise would have had to initialize array on heap. Check buildCArrArgs func
        std::vector<char*> cArgs(command.getArgs().size() + 1);
        execv(command_path.c_str(), buildCArrArgs(cArgs, command));
        std::cerr << "Failed to execv new process: " << command_path;
        return -1;
    } else {
        int status;
        auto wait_pid = waitpid(pid, &status, 0);
        if (wait_pid == -1) {
            std::cerr << "Failed to wait for the child, pid: "<< pid;
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