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

int DefaultExecutor::executeCommands(const std::vector<Command>& commands) {
    for (auto command: commands) {
        for (auto path: paths) {
            auto command_path = path + "/" + command.command_;
            if (std::filesystem::exists(command_path)) {
                auto res = executeCommand(command_path, command.args_);
                return 0;
            }
        }
    }
    return -1;
};

int DefaultExecutor::executeCommand(const std::string& command_path, const std::vector<std::string>& args) {
    pid_t pid = fork();
    if (pid < 0) {
        std::cerr << "failed to create child process (fork)";
        return -1;
    }
    if (pid == 0) {
        // Must initialize next to execv in order to keep lifetime of the returning ptr based on this vector.
        // Otherwise would have had to initialize array on heap. Check strVecToCharArr func
        std::vector<char*> cArgs(args.size() + 1);
        execv(command_path.c_str(), strVecToCharArr(cArgs, args));
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

char *const * DefaultExecutor::strVecToCharArr(std::vector<char*>& cStrVec, const std::vector<std::string>& strVec) {
    for (int i = 0; i < strVec.size(); i++) {
        // execv signature was implemented with using no const char*. const_cast is required for compatibility
        // https://stackoverflow.com/a/190208
        cStrVec[i] = const_cast<char*>(strVec[i].c_str());
    }
    // data doesn't finish array with NULL element, so must assign it manually
    cStrVec[cStrVec.size() - 1] = nullptr;
    // https://en.cppreference.com/w/cpp/container/vector/data 
    return cStrVec.data();
}