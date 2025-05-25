/** \file DefaultExecutor.h
 *  \brief Declares the DefaultExecutor class, which handles built-in shell commands and process management for external commands.
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


/** \class DefaultExecutor
 *  \brief Executes built-in shell commands and manages external command processes using a search path.
 *
 *  DefaultExecutor implements IExecutor to handle:
 *   - built-in commands such as exit, cd, and path,
 *   - external commands by forking and execv,
 *   - I/O redirection to files,
 *   - foreground and background execution.
 *
 *  It maintains a list of directories (`path_`) derived from the shell’s PATH,
*/
class DefaultExecutor: public IExecutor {
public:
    /** \brief Execute a sequence of commands.
     *  \param commands A vector of Command objects to be executed in order.
     *  \return True if all commands executed successfully; false if any command failed.
    */
    bool executeCommands(const std::vector<Command>& commands) final;

private:
    /** \enum BuiltInCommandType
     *  \brief Enum for the shell’s built-in command identifiers.
     *
     *  Represents each supported built-in command so that the executor
     *  can dispatch to the correct handler.
    */
    enum class BuiltInCommandType;
    std::vector<std::string> paths_ = {"/bin"};
    static const std::unordered_map<std::string, BuiltInCommandType> strToBuiltInCommand_;

    /** \brief Execute an external command using the shell’s search path.
     *  \param command_path The full path to the executable to run.
     *  \param command      The Command object containing arguments, redirection, and execution flags.
     *  \return The child process ID (pid) in the parent process; always positive.
     *  \note On fork failure or if the child’s execv fails, this function calls exit(1) and does not return.
    */
    int executePathCommand(const std::string& command_path, const Command& command) const;

    /** \brief Wait for a list of child processes to finish and clear the PID list.
     *  \param pids A vector of child process IDs to wait on; this vector is cleared upon successful completion.
     *  \note If any waitpid call fails, the function calls exit(1) and does not return.
    */
    void waitChildren(std::vector<pid_t>& pids) const;

    /** \brief Check if a path refers to an existing executable regular file.
     *  \param command_path The filesystem path to the file to check.
     *  \return True if the file exists, is a regular file, and has execute permissions for the current user; false otherwise.
    */
    bool isExecutableFile(const std::string& command_path) const;

    /** \brief Convert Command arguments to a C-style argv array for execv.
     *  \param cStrVec A pre-initialized vector<char*> that will be filled with C-string pointers.
     *  \param command The Command object whose arguments are to be converted.
     *  \return A null-terminated array of C-string pointers suitable for passing to execv.
    */
    char *const * convertArgsToCStyle(std::vector<char*>& cStrVec, const Command& command) const;

    /** \brief Execute a built-in shell command.
     *  \param commandType The BuiltInCommandType value identifying which built-in command to execute.
     *  \param command     The Command object containing any arguments for the built-in command.
     *  \return True if the built-in command executed successfully; false otherwise.
    */
    bool executeBuiltInCommand(const BuiltInCommandType& commandType, const Command& command);

    /** \brief Exit the shell immediately.
     *  \note This function does not return.
    */
    void builtInExit() const;

    /** \brief Update the shell’s search path.
     *  \param args A vector of directory paths to set as the new PATH.
    */
    void builtInPath(const std::vector<std::string>& args);

    /** \brief Change the current working directory.
     *  \param dir The target directory to switch to.
     *  \return True if the directory change succeeded; false otherwise.
    */
    bool builtInCD(const std::string& dir) const;

    /** \brief Determine if a command string corresponds to a built-in command.
     *  \param command The name of the command to check.
     *  \return An optional containing the BuiltInCommandType if the command is built-in; std::nullopt otherwise.
    */
    std::optional<BuiltInCommandType> getBuiltInCommandType(const std::string& command) const;
};

#endif // DEFAULT_EXECUTOR_H