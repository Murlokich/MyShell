/** \file Entities.h
 *  \brief This file declares entities structs that are used by parser/executor
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 19/05/2025
*/

#ifndef ENTITIES_H
#define ENTITIES_H

#include <optional>
#include <string>
#include <unordered_map>
#include <vector>


class Command {
public:
    enum class Separator {
        parallel = '&',
        sequential = ';',
    };

    const std::string& getCommand() const;
    const std::vector<std::string>& getArgs() const;
    const std::optional<std::string> getRedirectionFile() const;
    Separator getSeparator() const;
    void setSeparator(Separator separator);
    Command(const std::vector<std::string>& args, std::optional<std::string> redirection_file);
    Command();
private:
    std::vector<std::string> args_;
    Separator separator_ =  Separator::sequential;
    std::optional<std::string> redirection_file_ = std::nullopt;
};


#endif // ENTITIES_H