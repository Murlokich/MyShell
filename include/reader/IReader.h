/** \file IReader.h
 *  \brief This file declares interface for reader
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef IREADER_H
#define IREADER_H

#include <optional>
#include <string>

class IReader {
public:
    virtual std::optional<std::string> readLine() = 0;

    virtual ~IReader() = default;
};

#endif // IREADER_H