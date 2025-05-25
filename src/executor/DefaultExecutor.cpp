/** \file DefaultExecutor.cpp
 *  \brief This file defines methods of DefaultExecutor class for shell to execute commands
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#include "../../include/executor/DefaultExecutor.h"

#include <cassert>
#include <fcntl.h>
#include <filesystem>
#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


enum class DefaultExecutor::BuiltInCommandType {
    exit,
    cd,
    path,
};

const std::unordered_map<std::string, DefaultExecutor::BuiltInCommandType> DefaultExecutor::strToBuiltInCommand_ {
    {"exit", BuiltInCommandType::exit},
    {"cd", BuiltInCommandType::cd},
    {"path", BuiltInCommandType::path},
};


bool DefaultExecutor::executeCommands(const std::vector<Command>& commands) {
    std::vector<pid_t> waiting_pids{};
    for (const auto& command: commands) {
        // According to tests: & or ; are valid commands.
        // Not the same in bash (result of & command): bash: syntax error near unexpected token `&'
        if (command.getCommand().empty()) {
            continue;
        }
        if (auto type = getBuiltInCommandType(command.getCommand()); type) {
            if (auto success = executeBuiltInCommand(*type, command); !success) {
                return false;
            }
            continue;
        }
        bool executed = false;
        for (const auto& path: paths_) {
            auto command_path = path + "/" + command.getCommand();
            if (isExecutableFile(command_path)) {
                auto pid = executePathCommand(command_path, command);
                assert(pid >= 0);
                executed = true;
                waiting_pids.push_back(pid);
                break;
            }
        }
        if (!executed) {
            return false;
        }
        // Start waiting only when ';' was reached. If current separator is & keep creating processes
        if (auto separator = command.getSeparator(); separator == Command::Separator::sequential) {
            waitChildren(waiting_pids);
        }
    }
    // Checks case where user ends their input with &:
    // cmd1 & cmd2 & cmd3 &
    // bash doesn't wait for the next process, it finishes the line
    // so start waiting for children even if line didn't end with ';'
    waitChildren(waiting_pids);
    return true;
};


pid_t DefaultExecutor::executePathCommand(const std::string& command_path, const Command& command) const {
    pid_t pid = fork();
    if (pid < 0) {
        // for all fork/wait/execv related errors I decided to exit
        // to avoid zombies creation, lack of resources etc.
        exit(1);
    }
    if (pid == 0) {
        if (auto redirection_file = command.getRedirectionFile(); redirection_file) {
            // Got this code from: https://stackoverflow.com/a/2605313
            int fd = open(redirection_file->c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
            dup2(fd, 1);   // make stdout go to file
            dup2(fd, 2);   // make stderr go to file
            close(fd);     // fd no longer needed - the dup'ed handles are sufficient
        }
        // Must initialize in the same scope with execv in order to keep lifetime of the returning ptr based on this vector.
        // Otherwise would have had to initialize array on heap. Check convertArgsToCStyle func
        std::vector<char*> cArgs(command.getArgs().size() + 1);
        execv(command_path.c_str(), convertArgsToCStyle(cArgs, command));
        // execv doesn't return during the normal execution
        exit(1);
    } 
    return pid;
}


void DefaultExecutor::waitChildren(std::vector<pid_t>& pids) const {
    int status;
    for (auto child_pid : pids) {
        auto wait_pid = waitpid(child_pid, &status, 0);
        if (wait_pid == -1) {
            // for all fork/wait/execv related errors I decided to exit
            // to avoid zombies creation, lack of resources etc.
            exit(1);
        }
        assert(wait_pid == child_pid);
    }
    pids.clear();
}


bool DefaultExecutor::isExecutableFile(const std::string& command_path) const {
    return access(command_path.c_str(), X_OK) == 0
       && std::filesystem::is_regular_file(command_path);
}


char *const * DefaultExecutor::convertArgsToCStyle(std::vector<char*>& cStrVec, const Command& command) const {
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


bool DefaultExecutor::executeBuiltInCommand(const BuiltInCommandType& commandType, const Command& command) {
    switch (commandType) {
        case BuiltInCommandType::exit:
            if (command.getArgs().size() != 1 + 0) {
                return false;
            }
            assert(command.getCommand() == "exit");
            builtInExit();
            break;
        case BuiltInCommandType::cd:
            if (command.getArgs().size() != 1 + 1) {
                return false;
            }
            assert(command.getCommand() == "cd");
            if (auto success = builtInCD(command.getArgs()[1]); !success) {
                return false;
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
    return true;
}


void DefaultExecutor::builtInExit() const {
    exit(0);
}


void DefaultExecutor::builtInPath(const std::vector<std::string>& args) {
    paths_ = args;
    // First arg is the command name: "path", followed by real arguments
    // It's okay as we already copy the vector for O(n)
    paths_.erase(paths_.begin());
}


bool DefaultExecutor::builtInCD(const std::string& dir) const {
    // chdir returns 0 for no error, -1 for error
    // To adapt to C++ style, convert !0 -> true - successfully finished
    // !(-1) -> false - fault
    return !chdir(dir.c_str());
}


std::optional<DefaultExecutor::BuiltInCommandType> DefaultExecutor::getBuiltInCommandType(const std::string& command) const {
    if (auto it = strToBuiltInCommand_.find(command); it != strToBuiltInCommand_.end()) {
        return it->second;
    }
    return std::nullopt;
}