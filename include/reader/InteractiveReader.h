/** \file InteractiveReader.h
 *  \brief Declares the InteractiveReader class for shell interactive mode, implementing IReader.
 *  \author Konstantinos Trimikliniotis
 *  \version 0.0.1
 *  \date 26/04/2025
*/

#ifndef INTERACTIVE_READER_H
#define INTERACTIVE_READER_H

#include "IReader.h"

/** \class InteractiveReader
 *  \brief Reads input lines from standard input for interactive shell mode.
 *
 *  InteractiveReader prompts the user and returns each entered line
 *  via the `readLine()` method
*/
class InteractiveReader : public IReader {
public:
    /** \brief Read the next line from standard input.
     *  \return An optional containing the next line if available; std::nullopt on EOF or error.
    */
    std::optional<std::string> readLine() final;
};

#endif // INTERACTIVE_READER_H
