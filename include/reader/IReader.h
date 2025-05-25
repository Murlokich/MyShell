/** \file IReader.h
 *  \brief This file declares interface for the reader
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 25/04/2025
*/

#ifndef IREADER_H
#define IREADER_H

#include <optional>
#include <string>

/** \class IReader
 *  \brief Interface for input readers used by the shell.
 *
 *  IReader defines a uniform way to obtain lines of input,
 *  whether from a file or interactively from the user.
*/
class IReader {
public:
    /** \brief Read the next line of input.
     *  \return An optional containing the next input line if available; std::nullopt on EOF or error.
    */
    virtual std::optional<std::string> readLine() = 0;

    virtual ~IReader() = default;
};


#endif // IREADER_H