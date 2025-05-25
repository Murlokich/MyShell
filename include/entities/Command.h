/** \file Command.h
 *  \brief Declares the Command class, an abstraction representing a parsed shell command.
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 19/05/2025
 */

#ifndef COMMAND_H
#define COMMAND_H

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

/** \class Command
 *  \brief Abstraction for a shell command including its arguments, redirection, and separator.
 *
 *  The Command class stores:
 *   - a list of arguments (the first element is the command itself),
 *   - optional output redirection to a file,
 *   - and the separator that follows this command (either ';' for sequential execution or '&' for parallel).
 */
class Command {
public:
    /** \enum Separator
     *  \brief Enum for shell command separators (‘;’ or ‘&’).
    */
    enum class Separator {
        parallel = '&',
        sequential = ';',
    };

    /** \brief Get the command name.
     *  \return The name of the command.
    */
    const std::string& getCommand() const;

    /** \brief Get the list of arguments, including the command name as the first element.
     *  \return A const reference to the vector of argument strings.
    */
    const std::vector<std::string>& getArgs() const;

    /** \brief Get the optional output redirection filename.
     *  \return An optional containing the redirection filename if specified, or std::nullopt otherwise.
    */
    const std::optional<std::string> getRedirectionFile() const;

    /** \brief Get the command separator.
     *  \return The Separator enum value indicating sequential (‘;’) or parallel (‘&’) execution.
     */
    Separator getSeparator() const;

    /** \brief Set the command separator.
     *  \param separator The Separator value to use sequential (‘;’) or parallel (‘&’)
    */
    void setSeparator(Separator separator);

    /** \brief Construct a Command with arguments and optional redirection.
     *  \param args A vector of strings where the first element is the command name.
     *  \param redirection_file An optional filename for stdout/stderr redirection.
    */
    Command(const std::vector<std::string>& args, std::optional<std::string> redirection_file);

    /** \brief Default-construct a Command.
     *
     *  Creates an empty Command with no arguments, no redirection, and a default sequential separator.
    */
    Command();

private:
    std::vector<std::string> args_;
    Separator separator_ =  Separator::sequential;
    std::optional<std::string> redirection_file_ = std::nullopt;
};


#endif // COMMAND_H