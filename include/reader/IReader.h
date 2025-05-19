/** \file IReader.h
 *  \brief This file declares interface for reader
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef IREADER_H
#define IREADER_H

#include <string>
#include <optional>

class IReader {
protected:
    inline static const std::string EXIT_COMMAND = "exit";
public:
    virtual std::optional<std::string> readLine() = 0;

    virtual ~IReader() = default;
};

#endif // IREADER_H